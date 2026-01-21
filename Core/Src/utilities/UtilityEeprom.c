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
	writeExternalEeprom(0, 1, make8(setpointAdubo, 0));
	writeExternalEeprom(0, 2, make8(setpointAdubo, 1));
	writeExternalEeprom(0, 3, make8(setpointSemente, 0));
	writeExternalEeprom(0, 4, make8(setpointSemente, 1));
	writeExternalEeprom(0, 5, make8(larguraMaquina, 0));
	writeExternalEeprom(0, 6, make8(larguraMaquina, 1));
	writeExternalEeprom(0, 7, make8(larguraMaquina, 2));
	writeExternalEeprom(0, 8, make8(larguraMaquina, 3));
	writeExternalEeprom(0, 9, flagOffsetVelocidadeNegativo);
	writeExternalEeprom(0, 10, offsetVelocidade);
	writeExternalEeprom(0, 11, tipoSensorVelocidade);
	writeExternalEeprom(0, 12, velocidadeContingencia);
}
/*==============================================================================
WRITE EEPROM CALIBRACAO
==============================================================================*/
void writeEepromCalibracao() {
	writeExternalEeprom(0, 13, make8(calibracaoAdubo10, 0));
	writeExternalEeprom(0, 14, make8(calibracaoAdubo10, 1));
	writeExternalEeprom(0, 15, make8(calibracaoAdubo10, 2));
	writeExternalEeprom(0, 16, make8(calibracaoAdubo10, 3));

	writeExternalEeprom(0, 17, make8(calibracaoAdubo40, 0));
	writeExternalEeprom(0, 18, make8(calibracaoAdubo40, 1));
	writeExternalEeprom(0, 19, make8(calibracaoAdubo40, 2));
	writeExternalEeprom(0, 20, make8(calibracaoAdubo40, 3));

	writeExternalEeprom(0, 21, make8(calibracaoAdubo70, 0));
	writeExternalEeprom(0, 22, make8(calibracaoAdubo70, 1));
	writeExternalEeprom(0, 23, make8(calibracaoAdubo70, 2));
	writeExternalEeprom(0, 24, make8(calibracaoAdubo70, 3));

	writeExternalEeprom(0, 25, make8(calibracaoAdubo100, 0));
	writeExternalEeprom(0, 26, make8(calibracaoAdubo100, 1));
	writeExternalEeprom(0, 27, make8(calibracaoAdubo100, 2));
	writeExternalEeprom(0, 28, make8(calibracaoAdubo100, 3));

	writeExternalEeprom(0, 29, make8(calibracaoSemente10, 0));
	writeExternalEeprom(0, 30, make8(calibracaoSemente10, 1));
	writeExternalEeprom(0, 31, make8(calibracaoSemente10, 2));
	writeExternalEeprom(0, 32, make8(calibracaoSemente10, 3));

	writeExternalEeprom(0, 33, make8(calibracaoSemente40, 0));
	writeExternalEeprom(0, 34, make8(calibracaoSemente40, 1));
	writeExternalEeprom(0, 35, make8(calibracaoSemente40, 2));
	writeExternalEeprom(0, 36, make8(calibracaoSemente40, 3));

	writeExternalEeprom(0, 37, make8(calibracaoSemente70, 0));
	writeExternalEeprom(0, 38, make8(calibracaoSemente70, 1));
	writeExternalEeprom(0, 39, make8(calibracaoSemente70, 2));
	writeExternalEeprom(0, 40, make8(calibracaoSemente70, 3));

	writeExternalEeprom(0, 41, make8(calibracaoSemente100, 0));
	writeExternalEeprom(0, 42, make8(calibracaoSemente100, 1));
	writeExternalEeprom(0, 43, make8(calibracaoSemente100, 2));
	writeExternalEeprom(0, 44, make8(calibracaoSemente100, 3));
}
/*==============================================================================
WRITE EEPROM HECTARIMETRO
==============================================================================*/
void writeEepromHectarimetro() {
	writeExternalEeprom(0, 45, make8(hectarimetro, 0));
	writeExternalEeprom(0, 46, make8(hectarimetro, 1));
	writeExternalEeprom(0, 47, make8(hectarimetro, 2));
	writeExternalEeprom(0, 48, make8(hectarimetro, 3));
}
/*==============================================================================
WRITE ALL EEPROM
==============================================================================*/
void writeAllEeprom() {
	writeEepromConfiguracoes();
	writeEepromCalibracao();
	writeEepromHectarimetro();
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

		calibracaoAdubo10 = make32(readExternalEeprom(0, 13), readExternalEeprom(0, 14), readExternalEeprom(0, 15), readExternalEeprom(0, 16));
		calibracaoAdubo40 = make32(readExternalEeprom(0, 17), readExternalEeprom(0, 18), readExternalEeprom(0, 19), readExternalEeprom(0, 20));
		calibracaoAdubo70 = make32(readExternalEeprom(0, 21), readExternalEeprom(0, 22), readExternalEeprom(0, 23), readExternalEeprom(0, 24));
		calibracaoAdubo100 = make32(readExternalEeprom(0, 25), readExternalEeprom(0, 26), readExternalEeprom(0, 27), readExternalEeprom(0, 28));

		calibracaoSemente10 = make32(readExternalEeprom(0, 29), readExternalEeprom(0, 30), readExternalEeprom(0, 31), readExternalEeprom(0, 32));
		calibracaoSemente40 = make32(readExternalEeprom(0, 33), readExternalEeprom(0, 34), readExternalEeprom(0, 35), readExternalEeprom(0, 36));
		calibracaoSemente70 = make32(readExternalEeprom(0, 37), readExternalEeprom(0, 38), readExternalEeprom(0, 39), readExternalEeprom(0, 40));
		calibracaoSemente100 = make32(readExternalEeprom(0, 41), readExternalEeprom(0, 42), readExternalEeprom(0, 43), readExternalEeprom(0, 44));

		hectarimetro = make32(readExternalEeprom(0, 45), readExternalEeprom(0, 46), readExternalEeprom(0, 47), readExternalEeprom(0, 48));
	}
}
/*==============================================================================
APAGA EEPROM
==============================================================================*/
void apagaEeprom() {
	if(HAL_I2C_IsDeviceReady(&hi2c1, EEPROM_ADDR_0 + 1, 10, 100)) {


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
