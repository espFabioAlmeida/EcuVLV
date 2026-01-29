///////////////////////////////////////////////////////////////////////////////
//ARQUIVO:    UtilityCAN
//AUTOR:      Fábio Almeida
//CRIADO:     04/08/2023
//OBSERVAÇÕES:
////////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "global.h"
/*==============================================================================
CONSTANTES
==============================================================================*/
const uint32_t ECU_VLV_ADDRESS_PACK1 = 0x1BB81A01;
const uint32_t ECU_VLV_ADDRESS_PACK2 = 0x1BB81A02;
const uint32_t ECU_VLV_ADDRESS_PACK3 = 0x1BB81A03;
/*==============================================================================
RECEBE PACOTE CAN
==============================================================================*/
void recebePacoteCAN() {
	if(flagPacoteCAN) { //Não há dados a serem recebidos
		flagPacoteCAN = false;
		flagLedCOM = true;
	}
}
/*==============================================================================
ENVIA PACOTE CAN
==============================================================================*/
void enviaPacoteCAN() {
	static uint8_t pacote = 0;
	uint16_t dado = 0;

	pacote ++;
	if(pacote > 3) {
		pacote = 1;
	}

	canTxHeader.RTR = CAN_RTR_DATA;
	canTxHeader.IDE = CAN_ID_EXT;
	canTxHeader.DLC = 8;
	canTxHeader.TransmitGlobalTime = DISABLE;

	if(pacote == 1) {
		canTxHeader.ExtId = ECU_VLV_ADDRESS_PACK1;

		dado = buscarValorModulo(0);
		canTxBuffer[0] = make8(dado, 0);
		canTxBuffer[1] = make8(dado, 1);

		dado = buscarValorModulo(1);
		canTxBuffer[2] = make8(dado, 0);
		canTxBuffer[3] = make8(dado, 1);

		dado = buscarValorModulo(2);
		canTxBuffer[4] = make8(dado, 0);
		canTxBuffer[5] = make8(dado, 1);

		dado = buscarValorModulo(3);
		canTxBuffer[6] = make8(dado, 0);
		canTxBuffer[7] = make8(dado, 1);

	}
	else if(pacote == 2) {
		canTxHeader.ExtId = ECU_VLV_ADDRESS_PACK2;

		dado = buscarValorModulo(4);
		canTxBuffer[0] = make8(dado, 0);
		canTxBuffer[1] = make8(dado, 1);

		dado = buscarValorModulo(5);
		canTxBuffer[2] = make8(dado, 0);
		canTxBuffer[3] = make8(dado, 1);

		dado = buscarValorModulo(6);
		canTxBuffer[4] = make8(dado, 0);
		canTxBuffer[5] = make8(dado, 1);

		dado = buscarValorModulo(7);
		canTxBuffer[6] = make8(dado, 0);
		canTxBuffer[7] = make8(dado, 1);
	}
	else if(pacote == 3) {
		canTxHeader.ExtId = ECU_VLV_ADDRESS_PACK3;
		canTxBuffer[0] = comandoHaste;
		canTxBuffer[1] = 0;
		canTxBuffer[2] = 0;
		canTxBuffer[3] = 0;
		canTxBuffer[4] = 0;
		canTxBuffer[5] = 0;
		canTxBuffer[6] = 0;
		canTxBuffer[7] = 0;
	}

	if(HAL_CAN_AddTxMessage(&hcan1, &canTxHeader, canTxBuffer, &canTxMailbox) != HAL_OK) {
	    Error_Handler();
	}

	while(HAL_CAN_GetTxMailboxesFreeLevel(&hcan1) != 3) {
		//Aguarda fim da transmissão
	}
}
/*==============================================================================
FIM DO ARQUIVO
==============================================================================*/
