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

#define TAMANHO_BUFFER_IHM 				128
#define TAMANHO_BUFFER_SENSOR_ACIDEZ	32

#define MAXIMO_VALOR_SETPOINT			9999
#define MAXIMA_LARGURA_MAQUINA			999999
#define MINIMA_LARGURA_MAQUINA			100
#define MAXIMO_OFFSET_VELOCIDADE		9
#define MAXIMA_VELOCIDADE_CONTINGENCIA	20

enum COMANDO_COMPORTAS {
	PARAR_COMPORTAS,
	FECHAR_COMPORTAS,
	ABRIR_COMPORTAS,

	ERRO_COMPORTAS
};

enum COMANDO_HASTE {
	PARAR_HASTE,
	SUBIR_HASTE,
	DESCER_HASTE,

	ERRO_HASTE
};

enum TIPO_SENSOR_VELOCIDADE {
	SENSOR_GPS,
	SENSOR_PULSOS,

	ERRO_TIPO_SENSOR_VELOCIDADE
};

typedef struct {
	uint32_t data;
	uint8_t offset;
	uint8_t erro;
} DTOBufferTypeDef;

extern CAN_HandleTypeDef hcan;
extern I2C_HandleTypeDef hi2c1;
extern RTC_HandleTypeDef hrtc;
extern UART_HandleTypeDef huart7;
extern UART_HandleTypeDef huart8;
extern UART_HandleTypeDef huart3;

extern CAN_TxHeaderTypeDef	canTxHeader;
extern CAN_RxHeaderTypeDef	canRxHeader;

extern DTOBufferTypeDef
	bufferIHMDTO;

extern uint8_t
	flagPacoteCAN,
	flagEnviaPacoteCAN,
	flagPacoteIHM,
	flagLedCOM,
	flagLedIHM,

	flagAcionamentoS1,
	flagAcionamentoS2,
	flagAcionamentoS3,
	flagAcionamentoS4,

	flagOffsetVelocidadeNegativo;

extern uint8_t
	operacao,
	velocidade,
	offsetVelocidade,
	tipoSensorVelocidade,
	velocidadeContingencia,

	comandoComportas,
	comandoHaste,

	contadorBufferIHM,
	contadorBufferSensorAcidez;

extern char
	ihmDataIn,
	sensorAcidezDataIn;

extern uint16_t
	alturaHaste,
	acidez;

extern uint32_t
	canTxMailbox,

	setpointAdubo,
	setpointSemente,
	larguraMaquina,
	hectarimetro;

extern uint8_t
	canTxBuffer[8],
	canRxBuffer[8];

extern char
	bufferIHM[TAMANHO_BUFFER_IHM],
	bufferEnviaIHM[TAMANHO_BUFFER_IHM],

	bufferSensorAvidez[TAMANHO_BUFFER_SENSOR_ACIDEZ];
#endif /* INC_GLOBAL_H_ */
