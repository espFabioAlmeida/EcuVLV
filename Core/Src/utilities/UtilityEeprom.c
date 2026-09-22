///////////////////////////////////////////////////////////////////////////////
//ARQUIVO:    UtilityEeprom
//AUTOR:      Fábio Almeida
//CRIADO:     03/01/2024
//OBSERVAÇÕES:
////////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "global.h"
/*==============================================================================
CONSTANTES
==============================================================================*/
enum TIPO_MEMORIA {
	MEMORIA_24LC256, //serve também para o 512
	MEMORIA_24LC08
};

#define	EEPROM_ADDR_0	0x50
#define EEPROM_ADDR_1   0x51
#define EEPROM_ADDR_2   0x52
#define EEPROM_ADDR_3   0x53
#define EEPROM_ADDR_4   0x54
#define EEPROM_ADDR_5   0x55
#define EEPROM_ADDR_6   0x56
#define EEPROM_ADDR_7   0x57

#define	EEPROM_INICIALIZADA		0x0A
const uint8_t MEMORIA = MEMORIA_24LC256;
/*==============================================================================
WRITE EXTERNAL EEPROM
==============================================================================*/
void writeExternalEeprom(uint8_t device, uint16_t address, uint8_t data) {
	uint8_t pData[3];
	uint8_t deviceHex = 0x00;
	uint8_t quantidadeDados = 0;
	if(MEMORIA == MEMORIA_24LC256) {
		pData[0] = make8(address, 1);
		pData[1] = make8(address, 0);
		pData[2] = data;
		quantidadeDados = 3;

		switch(device) {
			case 0:	deviceHex = EEPROM_ADDR_0; break;
			case 1:	deviceHex = EEPROM_ADDR_1; break;
			case 2:	deviceHex = EEPROM_ADDR_2; break;
			case 3:	deviceHex = EEPROM_ADDR_3; break;
			case 4:	deviceHex = EEPROM_ADDR_4; break;
			case 5:	deviceHex = EEPROM_ADDR_5; break;
			case 6:	deviceHex = EEPROM_ADDR_6; break;
			case 7:	deviceHex = EEPROM_ADDR_7; break;
			default: return;
		}
	}
	else if(MEMORIA == MEMORIA_24LC08) {
		uint8_t blocoMemoria = 0;
		if(device > 0) { //somente 1 é possivel ter no barramento
			return;
		}
		for(; address > 255; address -= 255) {
			blocoMemoria ++;
		}
		pData[0] = address;
		pData[1] = data;
		quantidadeDados = 2;

		switch(blocoMemoria) {
			case 0:	deviceHex = EEPROM_ADDR_0; break;
			case 1:	deviceHex = EEPROM_ADDR_1; break;
			case 2:	deviceHex = EEPROM_ADDR_2; break;
			case 3:	deviceHex = EEPROM_ADDR_3; break;
			default: return;
		}
	}


	deviceHex <<= 1;

	HAL_I2C_Master_Transmit(&hi2c1, deviceHex, &pData, quantidadeDados, 100);
	HAL_Delay(10);
}
/*==============================================================================
READ EXTERNAL EEPROM
==============================================================================*/
uint8_t readExternalEeprom(uint8_t device, uint16_t address) {
	uint8_t data = 0;
	uint8_t pData[2];
	uint8_t deviceHex = 0x00;
	uint8_t quantidadeDados = 0;

	if(MEMORIA == MEMORIA_24LC256) {
		pData[0] = make8(address, 1);
		pData[1] = make8(address, 0);
		quantidadeDados = 2;

		switch(device) {
			case 0:	deviceHex = EEPROM_ADDR_0; break;
			case 1:	deviceHex = EEPROM_ADDR_1; break;
			case 2:	deviceHex = EEPROM_ADDR_2; break;
			case 3:	deviceHex = EEPROM_ADDR_3; break;
			case 4:	deviceHex = EEPROM_ADDR_4; break;
			case 5:	deviceHex = EEPROM_ADDR_5; break;
			case 6:	deviceHex = EEPROM_ADDR_6; break;
			case 7:	deviceHex = EEPROM_ADDR_7; break;
			default: return;
		}
	}
	else if(MEMORIA == MEMORIA_24LC08) {
		uint8_t blocoMemoria = 0;
		if(device > 0) { //somente 1 é possivel ter no barramento
			return;
		}
		for(; address > 255; address -= 255) {
			blocoMemoria ++;
		}
		pData[0] = address;
		quantidadeDados = 1;

		switch(blocoMemoria) {
			case 0:	deviceHex = EEPROM_ADDR_0; break;
			case 1:	deviceHex = EEPROM_ADDR_1; break;
			case 2:	deviceHex = EEPROM_ADDR_2; break;
			case 3:	deviceHex = EEPROM_ADDR_3; break;
			default: return;
		}
	}

	deviceHex <<= 1;

	HAL_I2C_Master_Transmit(&hi2c1, deviceHex, &pData, quantidadeDados, 100);
	HAL_Delay(10);
	deviceHex ++;
	HAL_I2C_Master_Receive(&hi2c1, deviceHex, &data, 1, 100);
	HAL_Delay(10);

	return data;
}
/*==============================================================================
WRITE EEPROM CONFIGURACOES
==============================================================================*/
void writeEepromConfiguracoes() {
	writeExternalEeprom(0, 1, make8(setpointAdubo, 1));
	writeExternalEeprom(0, 2, make8(setpointAdubo, 0));
	writeExternalEeprom(0, 3, make8(setpointSemente, 1));
	writeExternalEeprom(0, 4, make8(setpointSemente, 0));
	writeExternalEeprom(0, 5, make8(larguraMaquina, 3));
	writeExternalEeprom(0, 6, make8(larguraMaquina, 2));
	writeExternalEeprom(0, 7, make8(larguraMaquina, 1));
	writeExternalEeprom(0, 8, make8(larguraMaquina, 0));
	writeExternalEeprom(0, 9, flagOffsetVelocidadeNegativo);
	writeExternalEeprom(0, 10, offsetVelocidade);
	writeExternalEeprom(0, 11, tipoSensorVelocidade);
	writeExternalEeprom(0, 12, velocidadeContingencia);
	writeExternalEeprom(0, 68, make8(setpointHaste, 1));
	writeExternalEeprom(0, 69, make8(setpointHaste, 0));
	writeExternalEeprom(0, 70, make8(tamanhoHaste, 1));
	writeExternalEeprom(0, 71, make8(tamanhoHaste, 0));
	writeExternalEeprom(0, 72, quantidadePulsosHaste);
}
/*==============================================================================
WRITE EEPROM CALIBRACAO
==============================================================================*/
void writeEepromCalibracao(uint8_t material) {

	if(material == SELECIONA_TODOS || material >= ERRO_SELECAO_MATERIAL) {
		return;
	}

	for(uint8_t i = 0; i < QUANTIDADE_PONTOS_CALIBRACAO; i ++) {

		if(material == SELECIONA_ADUBO) {
			writeExternalEeprom(0, 13 + i * 4, make8(calibracaoAduboMaterial[i], 3));
			writeExternalEeprom(0, 14 + i * 4, make8(calibracaoAduboMaterial[i], 2));
			writeExternalEeprom(0, 15 + i * 4, make8(calibracaoAduboMaterial[i], 1));
			writeExternalEeprom(0, 16 + i * 4, make8(calibracaoAduboMaterial[i], 0));

			writeExternalEeprom(0, 73 + i, calibracaoAduboPercentual[i]);
		}
		else if(material == SELECIONA_SEMENTE) {
			writeExternalEeprom(0, 29 + i * 4, make8(calibracaoSementeMaterial[i], 3));
			writeExternalEeprom(0, 30 + i * 4, make8(calibracaoSementeMaterial[i], 2));
			writeExternalEeprom(0, 31 + i * 4, make8(calibracaoSementeMaterial[i], 1));
			writeExternalEeprom(0, 32 + i * 4, make8(calibracaoSementeMaterial[i], 0));

			writeExternalEeprom(0, 77 + i, calibracaoSementePercentual[i]);
		}
	}

	if(material == SELECIONA_ADUBO) {
		writeExternalEeprom(0, 81, calibracaoAduboPercentualZero);
	}
	else if(material == SELECIONA_SEMENTE) {
		writeExternalEeprom(0, 82, calibracaoSementePercentualZero);
	}
}
/*==============================================================================
WRITE EEPROM HECTARIMETRO
==============================================================================*/
void writeEepromHectarimetro() {
	writeExternalEeprom(0, 45, make8(hodometroMetros, 3));
	writeExternalEeprom(0, 46, make8(hodometroMetros, 2));
	writeExternalEeprom(0, 47, make8(hodometroMetros, 1));
	writeExternalEeprom(0, 48, make8(hodometroMetros, 0));
}
/*==============================================================================
WRITE EEPROM CONFIGURACAO MODULOS
==============================================================================*/
void writeEepromConfiguracaoModulos() {
	for(uint8_t i = 0; i < QUANTIDADE_MAXIMA_MODULOS; i ++) {
		writeExternalEeprom(0, 49 + i, configuracaoModuloPotencia[i]);
		writeExternalEeprom(0, 57 + i, setorModuloPotencia[i]);
	}
}
/*==============================================================================
WRITE EEPROM PULSOS POR 100M
==============================================================================*/
void writeEepromPulsosPor100m() {
	writeExternalEeprom(0, 66, make8(pulsosPor100m, 1));
	writeExternalEeprom(0, 67, make8(pulsosPor100m, 0));
}
/*==============================================================================
WRITE ALL EEPROM
==============================================================================*/
void writeAllEeprom() {
	writeEepromConfiguracoes();
	writeEepromCalibracao(SELECIONA_ADUBO);
	writeEepromCalibracao(SELECIONA_SEMENTE);
	writeEepromHectarimetro();
	writeEepromConfiguracaoModulos();
	writeEepromPulsosPor100m();
}
/*==============================================================================
READ EEPROM
==============================================================================*/
void readEeprom() {
	if(HAL_I2C_IsDeviceReady(&hi2c1, EEPROM_ADDR_0 + 1, 10, 100)) {
		setpointAdubo = make16(readExternalEeprom(0, 1), readExternalEeprom(0, 2));
		setpointSemente = make16(readExternalEeprom(0, 3), readExternalEeprom(0, 4));
		larguraMaquina = make32(readExternalEeprom(0, 5), readExternalEeprom(0, 6), readExternalEeprom(0, 7), readExternalEeprom(0, 8));
		flagOffsetVelocidadeNegativo = readExternalEeprom(0, 9);
		offsetVelocidade = readExternalEeprom(0, 10);
		tipoSensorVelocidade = readExternalEeprom(0, 11);
		velocidadeContingencia = readExternalEeprom(0, 12);

		for(uint8_t i = 0; i < QUANTIDADE_PONTOS_CALIBRACAO; i ++) {
			calibracaoAduboMaterial[i] = make32(readExternalEeprom(0, 13 + i * 4),
					readExternalEeprom(0, 14 + i * 4),
					readExternalEeprom(0, 15 + i * 4),
					readExternalEeprom(0, 16 + i * 4));

			calibracaoAduboPercentual[i] = readExternalEeprom(0, 73 + i);

			calibracaoSementeMaterial[i] = make32(readExternalEeprom(0, 29 + i * 4),
					readExternalEeprom(0, 30 + i * 4),
					readExternalEeprom(0, 31 + i * 4),
					readExternalEeprom(0, 32 + i * 4));

			calibracaoSementePercentual[i] = readExternalEeprom(0, 77 + i);
		}

		hodometroMetros = make32(readExternalEeprom(0, 45), readExternalEeprom(0, 46), readExternalEeprom(0, 47), readExternalEeprom(0, 48));

		for(uint8_t i = 0; i < QUANTIDADE_MAXIMA_MODULOS; i ++) {
			configuracaoModuloPotencia[i] = readExternalEeprom(0, 49 + i);
			setorModuloPotencia[i] = readExternalEeprom(0, 57 + i);
		}

		pulsosPor100m = make16(readExternalEeprom(0, 66), readExternalEeprom(0, 67));
		setpointHaste = make16(readExternalEeprom(0, 68), readExternalEeprom(0, 69));
		tamanhoHaste = make16(readExternalEeprom(0, 70), readExternalEeprom(0, 71));
		quantidadePulsosHaste = readExternalEeprom(0, 72);
		//73 ao 80 ocupados (calibracao)

		calibracaoAduboPercentualZero = readExternalEeprom(0, 81);
		calibracaoSementePercentualZero = readExternalEeprom(0, 82);
	}
}
/*==============================================================================
APAGA EEPROM
==============================================================================*/
void apagaEeprom() {
	if(HAL_I2C_IsDeviceReady(&hi2c1, EEPROM_ADDR_0 + 1, 10, 100)) {
		setpointAdubo = 10;
		setpointSemente = 10;
		larguraMaquina = 100;
		flagOffsetVelocidadeNegativo = false;
		offsetVelocidade = 0;
		tipoSensorVelocidade = SENSOR_GPS;
		velocidadeContingencia = 8;

		calibracaoAduboMaterial[0] = 20;
		calibracaoAduboMaterial[1] = 40;
		calibracaoAduboMaterial[2] = 80;
		calibracaoAduboMaterial[4] = 100;

		calibracaoSementeMaterial[0] = 20;
		calibracaoSementeMaterial[1] = 40;
		calibracaoSementeMaterial[2] = 80;
		calibracaoSementeMaterial[4] = 100;

		calibracaoAduboPercentual[0] = 20;
		calibracaoAduboPercentual[1] = 40;
		calibracaoAduboPercentual[2] = 80;
		calibracaoAduboPercentual[3] = 100;

		calibracaoSementePercentual[0] = 20;
		calibracaoSementePercentual[1] = 40;
		calibracaoSementePercentual[2] = 80;
		calibracaoSementePercentual[3] = 100;

		calibracaoAduboPercentualZero = 0;
		calibracaoSementePercentualZero = 0;

		hectarimetro = 0;
		hodometroMetros = 0;

		for(uint8_t i = 0; i < QUANTIDADE_MAXIMA_MODULOS; i ++) {
			configuracaoModuloPotencia[i] = MODULO_DESLIGADO;
			setorModuloPotencia[i] = 1;
		}

		pulsosPor100m = 10;

		writeExternalEeprom(0, 0, EEPROM_INICIALIZADA);
		writeAllEeprom();
	}
}
/*==============================================================================
VERIFICA EEPROM
==============================================================================*/
void verificaEeprom() {
	if(HAL_I2C_IsDeviceReady(&hi2c1, EEPROM_ADDR_0 + 1, 10, 100)) {
		if(readExternalEeprom(0, 0) != EEPROM_INICIALIZADA) {
			apagaEeprom();
		}
	}
}
/*==============================================================================
FIM DO ARQUIVO
==============================================================================*/
