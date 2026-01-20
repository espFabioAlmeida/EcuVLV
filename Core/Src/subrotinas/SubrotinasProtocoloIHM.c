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
			sprintfIHM(setpointAdubo, 0);
			strcat(bufferEnviaIHM, ",");
			sprintfIHM(setpointSemente, 0);
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
			break;

		case 2:
			sprintfIHM(setpointAdubo, 0);
			strcat(bufferEnviaIHM, ",");
			sprintfIHM(setpointSemente, 0);
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
			break;

		default: return;
	}


	strcat(bufferEnviaIHM, ",\r\n");

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

	//Validação dos dados
	if(setpointAdubo > MAXIMO_VALOR_SETPOINT) {
		setpointAdubo = 0;
	}
	if(setpointSemente > MAXIMO_VALOR_SETPOINT) {
		setpointSemente = 0;
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

	//TODO SALVAR EEPROM

	protocoloIHMEnviaResposta(2);
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
		uint8_t comando = charToByte(bufferIHM[offset + 2]) * 10 + charToByte(bufferEnviaIHM[offset + 3]);

		switch(comando) {
			case 1: protocoloIHMAtualizacaoDados(offset); break;
			case 2: protocoloIHMConfiguracoes(offset); break;
		}

	}

	flagPacoteIHM = false;
	apagaBufferIHM();
}
/*==============================================================================
FIM DO ARQUIVO
==============================================================================*/
