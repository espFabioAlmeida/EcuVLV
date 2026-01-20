///////////////////////////////////////////////////////////////////////////////
//ARQUIVO:    UtilityUART
//AUTOR:      Fábio Almeida
//CRIADO:     03/01/2024
//OBSERVAÇÕES:
//USART3 - SENSOR ACIDEZ
//UART7 - IHM
//UART8 - DEBUGGER
////////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "global.h"
/*==============================================================================
CONSTANTES DO ARQUIVO
==============================================================================*/
/*==============================================================================
APAGA BUFFER SENSOR ACIDEZ
==============================================================================*/
void apagaBufferSensorAcidez() {
	contadorBufferSensorAcidez = 0;
	memset(bufferSensorAvidez, 0x00, TAMANHO_BUFFER_SENSOR_ACIDEZ);
}
/*==============================================================================
APAGA BUFFER IHM
==============================================================================*/
void apagaBufferIHM() {
	contadorBufferIHM = 0;
	memset(bufferIHM, 0x00, TAMANHO_BUFFER_IHM);
}
/*=============================================================================
SPRINTF IHM
==============================================================================*/
void getValueBufferIHM(uint8_t offset, char separador) {
	bufferIHMDTO.data = 0;
	bufferIHMDTO.erro = false;
	bufferIHMDTO.offset = offset;

	for(; bufferIHM[offset] != separador; bufferIHMDTO.offset ++) {
		if(bufferIHMDTO.offset  >= TAMANHO_BUFFER_IHM) {
			bufferIHMDTO.data = 0;
			bufferIHMDTO.erro = true;
			return;
		}

		bufferIHMDTO.data *= 10;
		bufferIHMDTO.data += charToByte(bufferIHM[bufferIHMDTO.offset ]);
	}
}
/*==============================================================================
APAGA BUFFER ENVIO IHM
==============================================================================*/
void apagaBufferEnvioIHM() {
	memset(bufferEnviaIHM, 0x00, TAMANHO_BUFFER_IHM);
}
/*=============================================================================
SPRINTF IHM
==============================================================================*/
void sprintfIHM(uint32_t valor, uint8_t qntdDig) {
	//Enviar 0 em qntdDig para ignorar "zeros" a esquerda
	char dataChar[10];
	sprintf(dataChar, "%u", valor);

	switch(qntdDig) {
		case 9:
			if(valor < 100000000) {
				strcat(bufferEnviaIHM, "0");
			}
		case 8:
			if(valor < 10000000) {
				strcat(bufferEnviaIHM, "0");
			}
		case 7:
			if(valor < 1000000) {
				strcat(bufferEnviaIHM, "0");
			}
		case 6:
			if(valor < 100000) {
				strcat(bufferEnviaIHM, "0");
			}
		case 5:
			if(valor < 10000) {
				strcat(bufferEnviaIHM, "0");
			}
		case 4:
			if(valor < 1000) {
				strcat(bufferEnviaIHM, "0");
			}
		case 3:
			if(valor < 100) {
				strcat(bufferEnviaIHM, "0");
			}
		case 2:
			if(valor < 10) {
				strcat(bufferEnviaIHM, "0");
			}
	}

	strcat(bufferEnviaIHM, dataChar);
}
/*==============================================================================
FIM DO ARQUIVO
==============================================================================*/
