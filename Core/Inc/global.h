/*
 * global.h
 *
 *  Created on: Aug 23, 2023
 *      Author: User
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#define VERSAO_FIRMWARE 1

enum BOOL {
	false,
	true
};


extern CAN_HandleTypeDef hcan;
extern I2C_HandleTypeDef hi2c1;
extern RTC_HandleTypeDef hrtc;

extern CAN_TxHeaderTypeDef	canTxHeader;
extern CAN_RxHeaderTypeDef	canRxHeader;

extern uint8_t
	flagPacoteCAN,
	flagEnviaPacoteCAN,
	flagLedCOM;

extern uint32_t
	canTxMailbox;

extern uint8_t
	canTxBuffer[8],
	canRxBuffer[8];

#endif /* INC_GLOBAL_H_ */
