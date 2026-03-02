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
#define MAXIMO_VALOR_CALIBRACAO			999999
#define MAXIMO_PULSOS_HASTE				99
#define MAXIMO_TAMANHO_HASTE			999

#define QUANTIDADE_MAXIMA_MODULOS		8
#define QUANTIDADE_SETOR_MODULOS		4

#define TIMEOUT_MODULO_POTENCIA			5
#define TIMEOUT_CALIBRACAO_MATERIAL		600

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
	RETORNO_HASTE, //comando gerado pelo firmware

	ERRO_HASTE
};

enum TIPO_SENSOR_VELOCIDADE {
	SENSOR_GPS,
	SENSOR_PULSOS,

	ERRO_TIPO_SENSOR_VELOCIDADE
};

enum COMANDO_CALIBRACAO_MATERIAL {
	CANCELAR_CALIBRACAO_MATERIAL,
	ACIONA_ADUBO_10,
	ACIONA_ADUBO_40,
	ACIONA_ADUBO_70,
	ACIONA_ADUBO_100,

	ACIONA_SEMENTE_10,
	ACIONA_SEMENTE_40,
	ACIONA_SEMENTE_70,
	ACIONA_SEMENTE_100,

	ERRO_COMANDO_CALIBRACAO_MATERIAL
};

enum COMANDO_CALIBRACAO_PULSOS {
	CANCELAR_CALIBRACAO_PULSOS,
	INICIAR_CALIBRACAO_PULSOS,
	FINALIZAR_CALIBRACAO_PULSOS,

	ERRO_COMANDO_CALIBRACAO_PULSOS
};

enum MODULO_POTENCIA {
	MODULO_DESLIGADO,
	MODULO_ADUBO,
	MODULO_SEMENTE,

	ERRO_MODULO_POTENCIA
};

typedef struct {
	uint32_t data;
	uint8_t offset;
	uint8_t erro;
} DTOBufferTypeDef;

extern CAN_HandleTypeDef hcan1;
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
	flagCalculaSetpoint,

	flagSalvaHectarimetro,
	flagSensorLevante,
	flagOperacao,
	flagOperacaoVollverini,
	flagOperacaoAdubo,
	flagOperacaoSemente,
	flagCalibracaoPulsosPor100m,
	flagCalibracaoAdubo,
	flagCalibracaoSemente,

	flagHomeHaste,
	flagFimCursoHaste,

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

	comandoCalibracaoMaterial,
	comandoCalibracaoPulsos,
	comandoComportas,
	comandoHaste,

	contadorBufferIHM,
	contadorBufferSensorAcidez;

extern char
	ihmDataIn,
	sensorAcidezDataIn;

extern uint16_t
	alturaHaste,
	alturaZeroHaste,
	setpointHaste,
	quantidadePulsosHaste,
	quantidadePulsosSetpointHaste,
	contadorPulsosHaste,
	tamanhoHaste,
	acidez,

	pulsosPor100m,
	contadorPulsosPor100m,

	valorSaidaAdubo,
	valorSaidaSemente,

	contadorCalibracaoMaterial;

extern uint32_t
	canTxMailbox,

	setpointAdubo,
	setpointSemente,
	larguraMaquina,
	hectarimetro,
	hodometroMetros,
	distanciaParaUmHectare,

	calibracaoAdubo10,
	calibracaoAdubo40,
	calibracaoAdubo70,
	calibracaoAdubo100,

	calibracaoSemente10,
	calibracaoSemente40,
	calibracaoSemente70,
	calibracaoSemente100,

	materialPorMetroAdubo,
	materialPorMetroSemente;

extern uint8_t
	canTxBuffer[8],
	canRxBuffer[8],

	configuracaoModuloPotencia[QUANTIDADE_MAXIMA_MODULOS],
	setorModuloPotencia[QUANTIDADE_MAXIMA_MODULOS],
	contadorModuloOffline[QUANTIDADE_MAXIMA_MODULOS];

extern char
	bufferIHM[TAMANHO_BUFFER_IHM],
	bufferEnviaIHM[TAMANHO_BUFFER_IHM],

	bufferSensorAvidez[TAMANHO_BUFFER_SENSOR_ACIDEZ];
#endif /* INC_GLOBAL_H_ */
