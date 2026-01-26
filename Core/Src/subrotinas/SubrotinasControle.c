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
#define ESCALA_PWM_70	2866
#define ESCALA_PWM_40	1638
#define ESCALA_PWM_10	409
/*=============================================================================
CALCULA MATERIAL POR METRO
==============================================================================*/
void calculaMaterialPorMetro() {
	uint32_t setpointGramaPorHectareMaterial1 = 0, setpointGramaPorHectareMaterial2 = 0;
	setpointGramaPorHectareMaterial1 = setpointAdubo;
	setpointGramaPorHectareMaterial1 *= 1000;
	setpointGramaPorHectareMaterial2 = setpointSemente;
	setpointGramaPorHectareMaterial2 *= 1000;

	materialPorMetroAdubo = setpointGramaPorHectareMaterial1 / distanciaParaUmHectare;
	materialPorMetroSemente = setpointGramaPorHectareMaterial2 / distanciaParaUmHectare;
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
	uint32_t calibracaoMaterial10 = 0, calibracaoMaterial40 = 0, calibracaoMaterial70 = 0, calibracaoMaterial100 = 0;

	if(!materialPorMinuto) {
		return 0;
	}

	if(saida == 1) {
		calibracaoMaterial10 = calibracaoAdubo10;
		calibracaoMaterial40 = calibracaoAdubo40;
		calibracaoMaterial70 = calibracaoAdubo70;
		calibracaoMaterial100 = calibracaoAdubo100;
	}
	else if(saida == 2) {
		calibracaoMaterial10 = calibracaoSemente10;
		calibracaoMaterial40 = calibracaoSemente40;
		calibracaoMaterial70 = calibracaoSemente70;
		calibracaoMaterial100 = calibracaoSemente100;
	}
	else {
		return 0;
	}

	if(materialPorMinuto <= calibracaoMaterial10) {
		return map(materialPorMinuto, 0, calibracaoMaterial10, 0, ESCALA_PWM_10);
	}

	if(materialPorMinuto <= calibracaoMaterial40) {
		return map(materialPorMinuto, calibracaoMaterial10, calibracaoMaterial40, ESCALA_PWM_10, ESCALA_PWM_40);
	}

	if(materialPorMinuto <= calibracaoMaterial70) {
		return map(materialPorMinuto, calibracaoMaterial40, calibracaoMaterial70, ESCALA_PWM_40, ESCALA_PWM_70);
	}

	if(materialPorMinuto <= calibracaoMaterial100) {
		return map(materialPorMinuto, calibracaoMaterial70, calibracaoMaterial100, ESCALA_PWM_70, ESCALA_PWM_100);
	}

	return ESCALA_PWM_100;
}
/*==============================================================================
BUSCAR VALOR MODULO
==============================================================================*/
uint16_t  buscarValorModulo(modulo) {
	if(flagOperacao) {
		switch(configuracaoModuloPotencia[modulo]) {
			default:
			case MODULO_DESLIGADO: return 0;

			case MODULO_ADUBO: return valorSaidaAdubo;

			case MODULO_SEMENTE: return valorSaidaSemente;
		}
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
		velocidadeMin = velocidadeMetrosPorMinuto(velocidade);
		materialPorMinuto *= velocidadeMin;
		valorSaidaAdubo = calculaSetpointPWM(materialPorMinuto, 1);

		materialPorMinuto = materialPorMetroSemente;
		materialPorMinuto *= velocidadeMin;
		valorSaidaSemente = calculaSetpointPWM(materialPorMinuto, 2);
		return;
	}

	valorSaidaAdubo = 0;
	valorSaidaSemente = 0;
}
/*=============================================================================
FIM DO ARQUIVO
==============================================================================*/
