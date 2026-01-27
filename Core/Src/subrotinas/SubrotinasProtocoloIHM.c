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
void protocoloIHMEnviaResposta(uint8_t comando) {
	apagaBufferEnvioIHM();
	strcat(bufferEnviaIHM, "$,");
	sprintfIHM(comando, 2);
	strcat(bufferEnviaIHM, ",");

	switch(comando) {
		case 1:
			calculaHectarimetro();

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
			sprintfIHM(comandoHaste, 0);
			strcat(bufferEnviaIHM, ",");
			sprintfIHM(flagSensorLevante, 0);
			strcat(bufferEnviaIHM, ",");

			for(uint8_t i = 0; i < QUANTIDADE_MAXIMA_MODULOS; i ++) {
				if(contadorModuloOffline[i]) {
					sprintfIHM("1,", 0);
				}
				else {
					sprintfIHM("0,", 0);
				}
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
			sprintfIHM(comandoCalibracaoMaterial, 0);
			strcat(bufferEnviaIHM, ",");
			break;

		case 5:
		case 6:
			sprintfIHM(calibracaoAdubo10, 0);
			strcat(bufferEnviaIHM, ",");
			sprintfIHM(calibracaoAdubo40, 0);
			strcat(bufferEnviaIHM, ",");
			sprintfIHM(calibracaoAdubo70, 0);
			strcat(bufferEnviaIHM, ",");
			sprintfIHM(calibracaoAdubo100, 0);
			strcat(bufferEnviaIHM, ",");
			sprintfIHM(calibracaoSemente10, 0);
			strcat(bufferEnviaIHM, ",");
			sprintfIHM(calibracaoSemente40, 0);
			strcat(bufferEnviaIHM, ",");
			sprintfIHM(calibracaoSemente70, 0);
			strcat(bufferEnviaIHM, ",");
			sprintfIHM(calibracaoSemente100, 0);
			strcat(bufferEnviaIHM, ",");
			break;

		case 7:
			sprintfIHM(comandoCalibracaoPulsos, 0);
			strcat(bufferEnviaIHM, ",");
			break;

		case 8:
			break;

		case 9:
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
	comandoHaste = charToByte(bufferIHM[offset + 17]);

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

	protocoloIHMEnviaResposta(1);
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

	protocoloIHMEnviaResposta(2);
}
/*==============================================================================
ACIONAMENTO CALIBRAÇÃO
==============================================================================*/
void protocoloIHMAcionamentoCalibracao(uint8_t offset) {
	comandoCalibracaoMaterial = charToByte(bufferIHM[offset + 5]);

	if(flagOperacao) {
		comandoCalibracaoMaterial = CANCELAR_CALIBRACAO_MATERIAL;
		flagCalibracaoAdubo = false;
		flagCalibracaoSemente = false;
	}

	if(comandoCalibracaoMaterial >= ERRO_COMANDO_CALIBRACAO_MATERIAL) {
		comandoCalibracaoMaterial = CANCELAR_CALIBRACAO_MATERIAL;
	}

	verificaCalibracaoMaterial();

	protocoloIHMEnviaResposta(4);
}
/*==============================================================================
VALORES DE CALIBRAÇÃO
==============================================================================*/
void protocoloIHMValoresCalibracao(uint8_t offset) {
	getValueBufferIHM(offset + 5, ',');
	if(bufferIHMDTO.erro) {
		return;
	}
	calibracaoAdubo10 = bufferIHMDTO.data;

	getValueBufferIHM(bufferIHMDTO.offset + 1, ',');
	if(bufferIHMDTO.erro) {
		return;
	}
	calibracaoAdubo40 = bufferIHMDTO.data;

	getValueBufferIHM(bufferIHMDTO.offset + 1, ',');
	if(bufferIHMDTO.erro) {
		return;
	}
	calibracaoAdubo70 = bufferIHMDTO.data;

	getValueBufferIHM(bufferIHMDTO.offset + 1, ',');
	if(bufferIHMDTO.erro) {
		return;
	}
	calibracaoAdubo100 = bufferIHMDTO.data;

	getValueBufferIHM(bufferIHMDTO.offset + 1, ',');
	if(bufferIHMDTO.erro) {
		return;
	}
	calibracaoSemente10 = bufferIHMDTO.data;

	getValueBufferIHM(bufferIHMDTO.offset + 1, ',');
	if(bufferIHMDTO.erro) {
		return;
	}
	calibracaoSemente40 = bufferIHMDTO.data;

	getValueBufferIHM(bufferIHMDTO.offset + 1, ',');
	if(bufferIHMDTO.erro) {
		return;
	}
	calibracaoSemente70 = bufferIHMDTO.data;

	getValueBufferIHM(bufferIHMDTO.offset + 1, ',');
	if(bufferIHMDTO.erro) {
		return;
	}
	calibracaoSemente100 = bufferIHMDTO.data;

	//Validação dos valores
	if(calibracaoAdubo10 > MAXIMO_VALOR_CALIBRACAO) {
		calibracaoAdubo10 = MAXIMO_VALOR_CALIBRACAO;
	}
	if(calibracaoAdubo40 > MAXIMO_VALOR_CALIBRACAO) {
		calibracaoAdubo40 = MAXIMO_VALOR_CALIBRACAO;
	}
	if(calibracaoAdubo70 > MAXIMO_VALOR_CALIBRACAO) {
		calibracaoAdubo70 = MAXIMO_VALOR_CALIBRACAO;
	}
	if(calibracaoAdubo100 > MAXIMO_VALOR_CALIBRACAO) {
		calibracaoAdubo100 = MAXIMO_VALOR_CALIBRACAO;
	}
	if(calibracaoSemente10 > MAXIMO_VALOR_CALIBRACAO) {
		calibracaoSemente10 = MAXIMO_VALOR_CALIBRACAO;
	}
	if(calibracaoSemente40 > MAXIMO_VALOR_CALIBRACAO) {
		calibracaoSemente40 = MAXIMO_VALOR_CALIBRACAO;
	}
	if(calibracaoSemente70 > MAXIMO_VALOR_CALIBRACAO) {
		calibracaoSemente70 = MAXIMO_VALOR_CALIBRACAO;
	}
	if(calibracaoSemente100 > MAXIMO_VALOR_CALIBRACAO) {
		calibracaoSemente100 = MAXIMO_VALOR_CALIBRACAO;
	}

	writeEepromCalibracao();

	protocoloIHMEnviaResposta(5);
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
	protocoloIHMEnviaResposta(7);
}
/*==============================================================================
ZERAR HECTARIMETRO
==============================================================================*/
void protocoloIHMZerarHectarimetro(uint8_t offset) {
	hectarimetro = 0;
	writeEepromHectarimetro();
	protocoloIHMEnviaResposta(8);
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
	protocoloIHMEnviaResposta(9);
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
			case 1: protocoloIHMAtualizacaoDados(offset); break;
			case 2: protocoloIHMConfiguracoes(offset); break;
			case 3: protocoloIHMEnviaResposta(3); break;
			case 4: protocoloIHMAcionamentoCalibracao(offset); break;
			case 5: protocoloIHMValoresCalibracao(offset); break;
			case 6: protocoloIHMEnviaResposta(6); break;
			case 7: protocoloIHMCalibracaoPulsos(offset); break;
			case 8: protocoloIHMZerarHectarimetro(offset); break;
			case 9: protocoloIHMConfiguracaoModuloPotencia(offset); break;
		}

	}

	flagPacoteIHM = false;
	apagaBufferIHM();
}
/*==============================================================================
FIM DO ARQUIVO
==============================================================================*/
