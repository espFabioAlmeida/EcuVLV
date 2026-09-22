///////////////////////////////////////////////////////////////////////////////
//ARQUIVO:    SubrotinasControle
//AUTOR:      Fábio Almeida
//CIRADO:     05/01/2024
//OBSERVAÇÕES:
////////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "global.h"
/*=============================================================================
CONSTANTES DO ARQUIVO
==============================================================================*/
#define ESCALA_PWM_100	4095
/*=============================================================================
CALCULA ESCALA PWM
==============================================================================*/
uint16_t calculaEscalaPWM(uint8_t percentual) {
	if(percentual > 100) {
		return 0;
	}

	return map(percentual, 0, 100, 0, ESCALA_PWM_100);
}
/*=============================================================================
CALCULA MATERIAL POR METRO
==============================================================================*/
void calculaMaterialPorMetro() {
	uint32_t setpointGramaPorHectareMaterial1 = 0, setpointGramaPorHectareMaterial2 = 0;
	setpointGramaPorHectareMaterial1 = setpointAdubo;
	setpointGramaPorHectareMaterial1 *= 1000;
	setpointGramaPorHectareMaterial2 = setpointSemente;
	setpointGramaPorHectareMaterial2 *= 1000;

	if(distanciaParaUmHectare) {
		materialPorMetroAdubo = setpointGramaPorHectareMaterial1 / distanciaParaUmHectare;
		materialPorMetroSemente = setpointGramaPorHectareMaterial2 / distanciaParaUmHectare;
		return;
	}

	materialPorMetroAdubo = 1;
	materialPorMetroSemente = 1;
}
/*==============================================================================
VELOCIDADE EM m/min
==============================================================================*/
uint32_t velocidadeMetrosPorMinuto(uint8_t velocidade) {
    uint32_t calculo = velocidade;
    calculo *= 1000;
    calculo /= 60;
    return calculo;
}
/*==============================================================================
CALCULO SETPOINT PWM
==============================================================================*/
uint16_t calculaSetpointPWM(uint32_t materialPorMinuto, uint8_t saida) {
	uint32_t calibracaoMaterial[QUANTIDADE_PONTOS_CALIBRACAO];
	uint16_t valorPWM[QUANTIDADE_PONTOS_CALIBRACAO];
	uint16_t valorPWMZero = 0;

	if(!materialPorMinuto) {
		return 0;
	}

	if(saida == SELECIONA_TODOS || saida >= ERRO_SELECAO_MATERIAL) {
		return 0;
	}

	if(saida == SELECIONA_ADUBO) {
		valorPWMZero = calculaEscalaPWM(calibracaoAduboPercentualZero);
	}
	else if(saida == SELECIONA_SEMENTE) {
		valorPWMZero = calculaEscalaPWM(calibracaoSementePercentualZero);
	}

	for(uint8_t i = 0; i < QUANTIDADE_PONTOS_CALIBRACAO; i ++) {
		if(saida == SELECIONA_ADUBO) {
			calibracaoMaterial[i] = calibracaoAduboMaterial[i];
			valorPWM[i] = calculaEscalaPWM(calibracaoAduboPercentual[i]);
		}
		else if(saida == SELECIONA_SEMENTE) {
			calibracaoMaterial[i] = calibracaoSementeMaterial[i];
			valorPWM[i] = calculaEscalaPWM(calibracaoSementePercentual[i]);
		}
	}

	if(materialPorMinuto <= calibracaoMaterial[0]) {
		return map(materialPorMinuto, 0, calibracaoMaterial[0], valorPWMZero, valorPWM[0]);
	}

	if(materialPorMinuto <= calibracaoMaterial[1]) {
		return map(materialPorMinuto, calibracaoMaterial[0], calibracaoMaterial[1], valorPWM[0], valorPWM[1]);
	}

	if(materialPorMinuto <= calibracaoMaterial[2]) {
		return map(materialPorMinuto, calibracaoMaterial[1], calibracaoMaterial[2], valorPWM[1], valorPWM[2]);
	}

	if(materialPorMinuto <= calibracaoMaterial[3]) {
		return map(materialPorMinuto, calibracaoMaterial[2], calibracaoMaterial[3], valorPWM[2], valorPWM[3]);
	}

	return valorPWM[3];
}
/*==============================================================================
BUSCAR VALOR MODULO
==============================================================================*/
uint16_t  buscarValorModulo(modulo) {
	if(flagOperacao) {

		//Verifica se o setor está ligado
		if(!flagAcionamentoS1 && setorModuloPotencia[modulo] == 1) {
			return 0;
		}

		if(!flagAcionamentoS2 && setorModuloPotencia[modulo] == 2) {
			return 0;
		}

		if(!flagAcionamentoS3 && setorModuloPotencia[modulo] == 3) {
			return 0;
		}

		if(!flagAcionamentoS4 && setorModuloPotencia[modulo] == 4) {
			return 0;
		}


		//Verifica qual o valor
		switch(configuracaoModuloPotencia[modulo]) {
			default:
			case MODULO_DESLIGADO: return 0;

			case MODULO_ADUBO:
				if(flagOperacaoAdubo) {
					return valorSaidaAdubo;
				}
				break;

			case MODULO_SEMENTE:
				if(flagOperacaoSemente) {
					return valorSaidaSemente;
				}
				break;
		}
	}

	if(flagCalibracaoAdubo && configuracaoModuloPotencia[modulo] == MODULO_ADUBO) {
		return valorSaidaAdubo;
	}

	if(flagCalibracaoSemente && configuracaoModuloPotencia[modulo] == MODULO_SEMENTE) {
		return valorSaidaSemente;
	}

	return 0;
}
/*==============================================================================
CALCULO SETPOINT RPM
==============================================================================*/
void calculaSetpoint() {
	uint32_t materialPorMinuto = materialPorMetroAdubo;
	uint32_t velocidadeMin = 0;

	if(flagOperacao) {
		if(flagMaquinaParada) {
			valorSaidaAdubo = 0;
			valorSaidaSemente = 0;
			return;
		}

		velocidadeMin = velocidadeMetrosPorMinuto(velocidade);
		materialPorMinuto *= velocidadeMin;
		valorSaidaAdubo = calculaSetpointPWM(materialPorMinuto, 1);

		materialPorMinuto = materialPorMetroSemente;
		materialPorMinuto *= velocidadeMin;
		valorSaidaSemente = calculaSetpointPWM(materialPorMinuto, 2);
		return;
	}

	if(flagCalibracaoAdubo) {
		valorSaidaSemente = 0;
		valorSaidaAdubo = calculaEscalaPWM(calibracaoMaterialPercentual);

		if(contadorCalibracaoMaterial >= TIMEOUT_CALIBRACAO_MATERIAL) {
			contadorCalibracaoMaterial = 0;
			valorSaidaAdubo = 0;
			flagCalibracaoAdubo = false;
		}
		return;
	}

	if(flagCalibracaoSemente) {
		valorSaidaAdubo = 0;
		valorSaidaSemente = calculaEscalaPWM(calibracaoMaterialPercentual);

		if(contadorCalibracaoMaterial >= TIMEOUT_CALIBRACAO_MATERIAL) {
			contadorCalibracaoMaterial = 0;
			valorSaidaSemente = 0;
			flagCalibracaoSemente = false;
		}
		return;
	}

	valorSaidaAdubo = 0;
	valorSaidaSemente = 0;
}
/*==============================================================================
VERIFICA OPERACAO
==============================================================================*/
void verificaOperacao() {
	static uint8_t ultimoVolverini = false;

	if(flagSensorLevante) {
		flagCalibracaoAdubo = false;
		flagCalibracaoSemente = false;
		calibracaoMaterialSelecao = SELECIONA_TODOS;
		calibracaoMaterialPercentual = 0;

		if(!operacao) {
			flagOperacao = false;
			ultimoVolverini = false;
			flagOperacaoVollverini = false;
			flagOperacaoAdubo = false;
			flagOperacaoSemente = false;
			return;
		}

		flagOperacao = true;
		flagOperacaoVollverini = bitRead(operacao, 0);
		flagOperacaoAdubo = bitRead(operacao, 1);
		flagOperacaoSemente = bitRead(operacao, 2);

		if(ultimoVolverini) {
			if(!flagOperacaoVollverini) {
				ultimoVolverini = false;
			}
		}
		else {
			if(flagOperacaoVollverini) { //Iniciando operação vollverini
				calculaAlturaZeroHaste();
				calculaQuantidadePulsosSetpointHaste(setpointHaste + alturaZeroHaste);
				ultimoVolverini = true;
			}
		}
		return;
	}

	flagOperacao = false;
	ultimoVolverini = false;
	flagOperacaoVollverini = false;
	flagOperacaoAdubo = false;
	flagOperacaoSemente = false;
}
/*=============================================================================
FIM DO ARQUIVO
==============================================================================*/
