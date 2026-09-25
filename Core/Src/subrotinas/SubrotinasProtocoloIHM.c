///////////////////////////////////////////////////////////////////////////////
//ARQUIVO:    SubrotinasProtocoloIHM
//AUTOR:      Fábio Almeida
//CRIADO:     20/01/2026
//OBSERVAÇÕES:
////////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "global.h"
/*==============================================================================
CONSTANTES DO ARQUIVO
==============================================================================*/
/*==============================================================================
RESPONDE A SOLICITAÇÃO
==============================================================================*/
void protocoloIHMEnviaResposta(uint8_t comando, uint8_t selecao) {
	apagaBufferEnvioIHM();
	strcat(bufferEnviaIHM, "$,");
	sprintfIHM(comando, 2);
	strcat(bufferEnviaIHM, ",");

	switch(comando) {
		case 0:
			sprintfIHM(VERSAO_FIRMWARE, 0);
			strcat(bufferEnviaIHM, ".");
			sprintfIHM(SUBVERSAO_FIRMWARE, 0);
			break;

		case 1:
			calculaHectarimetro();
			calculaAlturaHaste();

			sprintfIHM(setpointAdubo, 0);
			strcat(bufferEnviaIHM, ",");
			sprintfIHM(setpointSemente, 0);
			strcat(bufferEnviaIHM, ",");
			sprintfIHM(setpointHaste, 0);
			strcat(bufferEnviaIHM, ",");
			sprintfIHM(velocidade, 0);
			strcat(bufferEnviaIHM, ",");
			sprintfIHM(alturaHaste, 0);
			strcat(bufferEnviaIHM, ",");
			sprintfIHM(acidez, 0);
			strcat(bufferEnviaIHM, ",");
			sprintfIHM(hectarimetro, 0);
			strcat(bufferEnviaIHM, ",");
			sprintfIHM(operacao, 0);
			strcat(bufferEnviaIHM, ",");
			sprintfIHM(flagAcionamentoS1, 0);
			strcat(bufferEnviaIHM, ",");
			sprintfIHM(flagAcionamentoS2, 0);
			strcat(bufferEnviaIHM, ",");
			sprintfIHM(flagAcionamentoS3, 0);
			strcat(bufferEnviaIHM, ",");
			sprintfIHM(flagAcionamentoS4, 0);
			strcat(bufferEnviaIHM, ",");
			sprintfIHM(comandoComportas, 0);
			strcat(bufferEnviaIHM, ",");
			if(comandoHaste ==  RETORNO_HASTE) {
				sprintfIHM(SUBIR_HASTE, 0);
			}
			else {
				sprintfIHM(comandoHaste, 0);
			}
			strcat(bufferEnviaIHM, ",");
			sprintfIHM(flagSensorLevante, 0);
			strcat(bufferEnviaIHM, ",");
			sprintfIHM(flagMaquinaParada, 0);
			strcat(bufferEnviaIHM, ",");
			sprintfIHM(flagContingenciaAcionada, 0);
			strcat(bufferEnviaIHM, ",");

			if(contadorFalhaEsteira >= TIMEOUT_FALHA_ESTEIRA) {
				strcat(bufferEnviaIHM, "0,");
			}
			else {
				strcat(bufferEnviaIHM, "1,");
			}

			for(uint8_t i = 0; i < QUANTIDADE_MAXIMA_MODULOS; i ++) {
				if(contadorModuloOffline[i]) {
					strcat(bufferEnviaIHM, "1,");
				}
				else {
					strcat(bufferEnviaIHM, "0,");
				}
			}
			for(uint8_t i = 0; i < QUANTIDADE_MAXIMA_MODULOS; i ++) {
				sprintfIHM(frequenciaModulo[i], 0);
				strcat(bufferEnviaIHM, ",");
			}
			break;

		case 2:
		case 3:
			sprintfIHM(setpointAdubo, 0);
			strcat(bufferEnviaIHM, ",");
			sprintfIHM(setpointSemente, 0);
			strcat(bufferEnviaIHM, ",");
			sprintfIHM(setpointHaste, 0);
			strcat(bufferEnviaIHM, ",");
			sprintfIHM(larguraMaquina, 0);
			strcat(bufferEnviaIHM, ",");
			if(flagOffsetVelocidadeNegativo) {
				strcat(bufferEnviaIHM, "-");
			}
			else {
				strcat(bufferEnviaIHM, "+");
			}
			sprintfIHM(offsetVelocidade, 0);
			strcat(bufferEnviaIHM, ",");
			sprintfIHM(tipoSensorVelocidade, 0);
			strcat(bufferEnviaIHM, ",");
			sprintfIHM(velocidadeContingencia, 0);
			strcat(bufferEnviaIHM, ",");
			sprintfIHM(quantidadePulsosHaste, 0);
			strcat(bufferEnviaIHM, ",");
			sprintfIHM(tamanhoHaste, 0);
			strcat(bufferEnviaIHM, ",");
			break;

		case 4:
			sprintfIHM(calibracaoMaterialSelecao, 0);
			strcat(bufferEnviaIHM, ",");
			sprintfIHM(calibracaoMaterialPercentual, 0);
			strcat(bufferEnviaIHM, ",");
			break;

		case 5:
		case 6:
			sprintfIHM(selecao, 0);
			strcat(bufferEnviaIHM, ",");
			if(selecao == SELECIONA_ADUBO) {
				sprintfIHM(calibracaoAduboPercentualZero, 0);
				strcat(bufferEnviaIHM, ",");
				for(uint8_t i = 0; i < QUANTIDADE_PONTOS_CALIBRACAO; i ++) {
					sprintfIHM(calibracaoAduboPercentual[i], 0);
					strcat(bufferEnviaIHM, ",");
					sprintfIHM(calibracaoAduboMaterial[i], 0);
					strcat(bufferEnviaIHM, ",");
				}
			}
			else if(selecao == SELECIONA_SEMENTE) {
				sprintfIHM(calibracaoSementePercentualZero, 0);
				strcat(bufferEnviaIHM, ",");
				for(uint8_t i = 0; i < QUANTIDADE_PONTOS_CALIBRACAO; i ++) {
					sprintfIHM(calibracaoSementePercentual[i], 0);
					strcat(bufferEnviaIHM, ",");
					sprintfIHM(calibracaoSementeMaterial[i], 0);
					strcat(bufferEnviaIHM, ",");
				}
			}
			break;

		case 7:
			sprintfIHM(comandoCalibracaoPulsos, 0);
			strcat(bufferEnviaIHM, ",");
			if(flagEnviaValorCalibracao100m) {
				sprintfIHM(pulsosPor100m, 0);
				strcat(bufferEnviaIHM, ",");
			}
			flagEnviaValorCalibracao100m = false;
			break;

		case 8:
			break;

		case 9:
		case 10:
			for(uint8_t i = 0; i < QUANTIDADE_MAXIMA_MODULOS; i ++) {
				sprintfIHM(configuracaoModuloPotencia[i], 0);
				strcat(bufferEnviaIHM, ",");
			}
			for(uint8_t i = 0; i < QUANTIDADE_MAXIMA_MODULOS; i ++) {
				sprintfIHM(setorModuloPotencia[i], 0);
				strcat(bufferEnviaIHM, ",");
			}
			break;

		default: return;
	}


	strcat(bufferEnviaIHM, "\r\n");

	HAL_UART_Transmit(&huart7, &bufferEnviaIHM, strlen(bufferEnviaIHM), 200);
}
/*==============================================================================
ATUALIZAÇÃO DOS DADOS
==============================================================================*/
void protocoloIHMAtualizacaoDados(uint8_t offset) {
	operacao = charToByte(bufferIHM[offset + 5]);
	flagAcionamentoS1 = charToBool(bufferIHM[offset + 7]);
	flagAcionamentoS2 = charToBool(bufferIHM[offset + 9]);
	flagAcionamentoS3 = charToBool(bufferIHM[offset + 11]);
	flagAcionamentoS4 = charToBool(bufferIHM[offset + 13]);
	comandoComportas = charToByte(bufferIHM[offset + 15]);

	if(!flagOperacao && comandoHaste != RETORNO_HASTE) {
		comandoHaste = charToByte(bufferIHM[offset + 17]);
	}

	flagAcionaContingencia = charToBool(bufferIHM[offset + 19]);

	//Validação dos dados
	if(operacao > 7) { //todas as opções ligadas
		operacao = 0;
	}

	if(comandoComportas >= ERRO_COMPORTAS) {
		comandoComportas = PARAR_COMPORTAS;
	}

	if(comandoHaste >= ERRO_HASTE) {
		comandoHaste = ERRO_HASTE;
	}

	protocoloIHMEnviaResposta(1, 0);
}
/*==============================================================================
CONFIGURAÇÕES
==============================================================================*/
void protocoloIHMConfiguracoes(uint8_t offset) {
	getValueBufferIHM(offset + 5, ',');
	if(bufferIHMDTO.erro) {
		return;
	}
	setpointAdubo = bufferIHMDTO.data;

	getValueBufferIHM(bufferIHMDTO.offset + 1, ',');
	if(bufferIHMDTO.erro) {
		return;
	}
	setpointSemente = bufferIHMDTO.data;

	getValueBufferIHM(bufferIHMDTO.offset + 1, ',');
	if(bufferIHMDTO.erro) {
		return;
	}
	setpointHaste = bufferIHMDTO.data;

	getValueBufferIHM(bufferIHMDTO.offset + 1, ',');
	if(bufferIHMDTO.erro) {
		return;
	}
	larguraMaquina = bufferIHMDTO.data;

	bufferIHMDTO.offset ++;
	if(bufferIHM[bufferIHMDTO.offset] == '-') {
		flagOffsetVelocidadeNegativo = true;
	}
	else {
		flagOffsetVelocidadeNegativo = false;
	}

	getValueBufferIHM(bufferIHMDTO.offset + 1, ',');
	if(bufferIHMDTO.erro) {
		return;
	}
	offsetVelocidade = bufferIHMDTO.data;

	getValueBufferIHM(bufferIHMDTO.offset + 1, ',');
	if(bufferIHMDTO.erro) {
		return;
	}
	tipoSensorVelocidade = bufferIHMDTO.data;

	getValueBufferIHM(bufferIHMDTO.offset + 1, ',');
	if(bufferIHMDTO.erro) {
		return;
	}
	velocidadeContingencia = bufferIHMDTO.data;

	getValueBufferIHM(bufferIHMDTO.offset + 1, ',');
	if(bufferIHMDTO.erro) {
		return;
	}
	quantidadePulsosHaste = bufferIHMDTO.data;

	getValueBufferIHM(bufferIHMDTO.offset + 1, ',');
	if(bufferIHMDTO.erro) {
		return;
	}
	tamanhoHaste = bufferIHMDTO.data;

	//Validação dos dados
	if(setpointAdubo > MAXIMO_VALOR_SETPOINT) {
		setpointAdubo = 0;
	}
	if(setpointSemente > MAXIMO_VALOR_SETPOINT) {
		setpointSemente = 0;
	}
	if(setpointHaste > MAXIMO_TAMANHO_HASTE) {
		setpointHaste = 0;
	}
	if(larguraMaquina > MAXIMA_LARGURA_MAQUINA ||
			larguraMaquina < MINIMA_LARGURA_MAQUINA) {
		larguraMaquina = MINIMA_LARGURA_MAQUINA;
	}
	if(offsetVelocidade > MAXIMO_OFFSET_VELOCIDADE) {
		offsetVelocidade = 0;
	}
	if(tipoSensorVelocidade >= ERRO_TIPO_SENSOR_VELOCIDADE) {
		tipoSensorVelocidade = SENSOR_GPS;
	}
	if(velocidadeContingencia > MAXIMA_VELOCIDADE_CONTINGENCIA) {
		velocidadeContingencia = 0;
	}
	if(!quantidadePulsosHaste ||
			quantidadePulsosHaste > MAXIMO_PULSOS_HASTE) {
		quantidadePulsosHaste = 1;
	}
	if(!tamanhoHaste ||
			tamanhoHaste > MAXIMO_TAMANHO_HASTE) {
		tamanhoHaste = MAXIMO_TAMANHO_HASTE;
	}

	writeEepromConfiguracoes();
	calculaDistanciaUmHectare();
	calculaMaterialPorMetro();
	calculaQuantidadePulsosSetpointHaste(setpointHaste);

	protocoloIHMEnviaResposta(2, 0);
}
/*==============================================================================
ACIONAMENTO CALIBRAÇÃO
==============================================================================*/
void protocoloIHMAcionamentoCalibracao(uint8_t offset) {
	calibracaoMaterialSelecao = charToByte(bufferIHM[offset + 5]);

	if(calibracaoMaterialSelecao == SELECIONA_TODOS || calibracaoMaterialSelecao >= ERRO_SELECAO_MATERIAL) {
		calibracaoMaterialSelecao = SELECIONA_TODOS;
		calibracaoMaterialPercentual = 0;
	}
	else {
		calibracaoMaterialPercentual = 0;
		for(uint16_t i = offset + 7; isNumber(bufferIHM[i]); i ++) {
			calibracaoMaterialPercentual *= 10;
			calibracaoMaterialPercentual += charToByte(bufferIHM[i]);
		}

		if(calibracaoMaterialPercentual > 100) {
			calibracaoMaterialPercentual = 0;
		}
	}

	if(flagOperacao) {
		calibracaoMaterialSelecao = SELECIONA_TODOS;
		calibracaoMaterialPercentual = 0;
		flagCalibracaoAdubo = false;
		flagCalibracaoSemente = false;
	}

	verificaCalibracaoMaterial();

	protocoloIHMEnviaResposta(4, 0);
}
/*==============================================================================
VALORES DE CALIBRAÇÃO
==============================================================================*/
void protocoloIHMValoresCalibracao(uint8_t offset) {
	uint32_t valorCalibracao[QUANTIDADE_PONTOS_CALIBRACAO];
	uint8_t percentualCalibracao[QUANTIDADE_PONTOS_CALIBRACAO];
	uint8_t percentualZero = 0;
	uint8_t selecaoMaterial = SELECIONA_TODOS;

	getValueBufferIHM(offset + 5, ',');
	if(bufferIHMDTO.erro) {
		return;
	}
	selecaoMaterial = bufferIHMDTO.data;
	if(selecaoMaterial == SELECIONA_TODOS || selecaoMaterial >= ERRO_SELECAO_MATERIAL) {
		return;
	}

	getValueBufferIHM(bufferIHMDTO.offset + 1, ',');
	if(bufferIHMDTO.erro) {
		return;
	}
	percentualZero= bufferIHMDTO.data;

	for(uint8_t i = 0; i < QUANTIDADE_PONTOS_CALIBRACAO; i ++) {
		getValueBufferIHM(bufferIHMDTO.offset + 1, ',');
		if(bufferIHMDTO.erro) {
			return;
		}
		percentualCalibracao[i] = bufferIHMDTO.data;

		getValueBufferIHM(bufferIHMDTO.offset + 1, ',');
		if(bufferIHMDTO.erro) {
			return;
		}
		valorCalibracao[i] = bufferIHMDTO.data;

		//validacao
		if(percentualCalibracao[i] > 100) {
			percentualCalibracao[i] = 100;
		}
		if(valorCalibracao[i] > MAXIMO_VALOR_CALIBRACAO) {
			valorCalibracao[i] = MAXIMO_VALOR_CALIBRACAO;
		}
	}


	for(uint8_t i = 0; i < QUANTIDADE_PONTOS_CALIBRACAO; i ++) {
		if(selecaoMaterial == SELECIONA_ADUBO) {
			calibracaoAduboPercentualZero = percentualZero;
			calibracaoAduboPercentual[i] = percentualCalibracao[i];
			calibracaoAduboMaterial[i] = valorCalibracao[i];
		}
		else if(selecaoMaterial == SELECIONA_SEMENTE) {
			calibracaoSementePercentualZero = percentualZero;
			calibracaoSementePercentual[i] = percentualCalibracao[i];
			calibracaoSementeMaterial[i] = valorCalibracao[i];
		}
	}

	writeEepromCalibracao(selecaoMaterial);
	protocoloIHMEnviaResposta(5, selecaoMaterial);
}
/*==============================================================================
LEITURA VALORES DE CALIBRAÇÃO
==============================================================================*/
void protocoloIHMleituraValoresCalibracao(uint8_t offset) {
	uint8_t selecaoMaterial = SELECIONA_TODOS;

	getValueBufferIHM(offset + 5, ',');
	if(bufferIHMDTO.erro) {
		return;
	}
	selecaoMaterial = bufferIHMDTO.data;
	if(selecaoMaterial == SELECIONA_TODOS || selecaoMaterial >= ERRO_SELECAO_MATERIAL) {
		return;
	}

	protocoloIHMEnviaResposta(6, selecaoMaterial);
}
/*==============================================================================
CALIBRAÇÃO PULSOS
==============================================================================*/
void protocoloIHMCalibracaoPulsos(uint8_t offset) {
	comandoCalibracaoPulsos = charToByte(bufferIHM[offset + 5]);

	if(comandoCalibracaoPulsos > ERRO_COMANDO_CALIBRACAO_PULSOS) {
		comandoCalibracaoPulsos = CANCELAR_CALIBRACAO_PULSOS;
	}

	verificaCalibracaoPulsos();
	protocoloIHMEnviaResposta(7, 0);
}
/*==============================================================================
ZERAR HECTARIMETRO
==============================================================================*/
void protocoloIHMZerarHectarimetro(uint8_t offset) {
	hodometroMetros = 0;
	writeEepromHectarimetro();
	protocoloIHMEnviaResposta(8, 0);
}
/*==============================================================================
CONFIGURAÇÃO MÓDULO POTENCIA
==============================================================================*/
void protocoloIHMConfiguracaoModuloPotencia(uint8_t offset) {

	for(uint8_t i = 0; i < QUANTIDADE_MAXIMA_MODULOS; i ++) {
		configuracaoModuloPotencia[i] = charToByte(bufferIHM[offset + 5 + i *2]);
		setorModuloPotencia[i] = charToByte(bufferIHM[offset + 21 + i * 2]);

		//Validação
		if(configuracaoModuloPotencia[i] >= ERRO_MODULO_POTENCIA) {
			configuracaoModuloPotencia[i] = MODULO_DESLIGADO;
		}
		if(setorModuloPotencia[i] > QUANTIDADE_SETOR_MODULOS) {
			setorModuloPotencia[i] = 1;
		}
	}

	writeEepromConfiguracaoModulos();
	protocoloIHMEnviaResposta(9, 0);
}
/*==============================================================================
PROTOCOLO IHM
==============================================================================*/
void protocoloIHM() {
	signed int offset;
	if(!flagPacoteIHM) {
		return;
	}

	offset = indexOf(bufferIHM, "$,");

	if(offset >= 0) {
		uint8_t comando = charToByte(bufferIHM[offset + 2]) * 10 + charToByte(bufferIHM[offset + 3]);

		switch(comando) {
			case 0: protocoloIHMEnviaResposta(comando, 0); break;
			case 1: protocoloIHMAtualizacaoDados(offset); break;
			case 2: protocoloIHMConfiguracoes(offset); break;
			case 3: protocoloIHMEnviaResposta(3, 0); break;
			case 4: protocoloIHMAcionamentoCalibracao(offset); break;
			case 5: protocoloIHMValoresCalibracao(offset); break;
			case 6: protocoloIHMleituraValoresCalibracao(offset); break;
			case 7: protocoloIHMCalibracaoPulsos(offset); break;
			case 8: protocoloIHMZerarHectarimetro(offset); break;
			case 9: protocoloIHMConfiguracaoModuloPotencia(offset); break;
			case 10: protocoloIHMEnviaResposta(10, 0); break;
		}

		if(comando <= 9) {
			flagLedIHM = true;
		}
	}

	flagPacoteIHM = false;
	apagaBufferIHM();
}
/*==============================================================================
FIM DO ARQUIVO
==============================================================================*/
