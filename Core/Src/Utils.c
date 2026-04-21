///////////////////////////////////////////////////////////////////////////////
//ARQUIVO:    Utils
//AUTOR:      Fábio Almeida
//CRIADO:     04/08/2023
//OBSERVAÇÕES:
////////////////////////////////////////////////////////////////////////////////
# include "main.h"
# include "global.h"
/*==============================================================================
INCREMENTA
==============================================================================*/
uint16_t incrementaDecrementa(uint16_t valor, uint16_t minimo, uint16_t maximo, uint8_t incrementa) {
	if(incrementa) {
		valor ++;
		if(valor > maximo) {
			return minimo;
		}
		if(valor < minimo) {
			return minimo;
		}
		return valor;
	}

	valor --;
	if(valor < minimo) {
		return maximo;
	}
	if(valor > maximo) {
		return  maximo;
	}

	return valor;
}
/*==============================================================================
C++ INDEX OF
==============================================================================*/
signed int indexOf(char stringIn[], char stringComparacao[]) {
	uint8_t encontrado = false;
	for(uint16_t i = 0; i < strlen(stringIn); i ++) {
		if(stringIn[i] == stringComparacao[0]) {
			encontrado = true;
			for(uint16_t j = 0; j < strlen(stringComparacao); j ++) {
				if(stringIn[i + j] != stringComparacao[j]) {
					encontrado = false;
				}
			}
			if(encontrado) {
				return i;
			}
		}
	}
	return -1;
}
/*===========================================================================
FUNÇÃO PARA TRANSFORMAR UM DADO INT EM UM CHAR
===========================================================================*/
char serializer(uint8_t var) {
    switch(var) {
        case 0:
            return '0';
            break;
        case 1:
            return '1';
            break;
        case 2:
            return '2';
            break;
        case 3:
            return '3';
            break;
        case 4:
            return '4';
            break;
        case 5:
            return '5';
            break;
        case 6:
            return '6';
            break;
        case 7:
            return '7';
            break;
        case 8:
            return '8';
            break;
        case 9:
            return '9';
            break;
		//hexadecimais
		case 0x0A:
			return 'A';
			break;
		case 0x0B:
			return 'B';
			break;
		case 0x0C:
			return 'C';
			break;
		case 0x0D:
			return 'D';
			break;
		case 0x0E:
			return 'E';
			break;
		case 0x0F:
			return 'F';
			break;

		default:
			return ' ';
			break;
    }
}
/*===========================================================================
FUNÇÃO PARA TRANSFORMAR UM DADO CHAR EM UM INT
===========================================================================*/
uint8_t charToByte(char var) {
	switch(var) {
		case '0': return 0;
		case '1': return 1;
		case '2': return 2;
		case '3': return 3;
		case '4': return 4;
		case '5': return 5;
		case '6': return 6;
		case '7': return 7;
		case '8': return 8;
		case '9': return 9;

		case 'A': return 0x0A;
		case 'B': return 0x0B;
		case 'C': return 0x0C;
		case 'D': return 0x0D;
		case 'E': return 0x0E;
		case 'F': return 0x0F;
	}

	return 0;
}
/*===========================================================================
FUNÇÃO PARA TRANSFORMAR UM DADO CHAR EM BOOL
===========================================================================*/
uint8_t charToBool(char var) {
	if(var == '0') {
		return false;
	}
	return true;
}
/*==============================================================================
MAP (REGRA DE 3 COMPOSTA)
==============================================================================*/
uint32_t map(uint32_t valor, uint32_t inMin, uint32_t inMax, uint32_t outMin, uint32_t outMax) {
	return ((valor - inMin) * (outMax - outMin)) / (inMax - inMin) + outMin;
}
/*==============================================================================
MAKE 8
==============================================================================*/
uint8_t make8(uint32_t valor, uint8_t offset) {
	uint8_t retorno = 0;

	if(offset == 0) {
		valor &= 0x000000FF;
		retorno = valor;
	}
	else if(offset == 1) {
		valor &= 0x0000FF00;
		valor >>= 8;
		retorno = valor;
	}
	else if(offset == 2) {
		valor &= 0x00FF0000;
		valor >>= 16;
		retorno = valor;
	}
	else if(offset == 3) {
		valor &= 0xFF000000;
		valor >>= 24;
		retorno = valor;
	}

	return retorno;
}
/*==============================================================================
MAKE 16
==============================================================================*/
uint16_t make16(uint8_t hi, uint8_t lo) {
	uint16_t retorno = hi;
	retorno <<= 8;
	retorno |= lo;
	return retorno;
}
/*==============================================================================
MAKE 32 - 4x int8
==============================================================================*/
uint32_t make32(uint8_t hihi, uint8_t hilo, uint8_t lohi, uint8_t lolo) {
	uint32_t retorno = hihi;
	uint32_t shift = hilo;
	retorno <<= 24;

	shift <<= 16;
	retorno |= shift;

	shift = lohi;
	shift <<= 8;
	retorno |= shift;

	retorno |= lolo;
	return retorno;
}
/*==============================================================================
READ BIT
==============================================================================*/
uint8_t bitRead(uint32_t valor, uint8_t offset) {
	uint32_t comparador = 0;
	comparador |= 1 << offset;
	comparador &= valor;

	if(comparador > 0) {
		return true;
	}
	return false;
}
/*==============================================================================
WRITE BIT
==============================================================================*/
uint32_t bitWrite(uint32_t valor, uint8_t offset, uint8_t valorBit) {

	if(valorBit == true) {
		valor |= 1 << offset;

	} else if(valorBit == false) {
		valor &= ~(1 << offset);
	}

	return valor;
}
/*==============================================================================
SET BIT
==============================================================================*/
uint32_t bitSet(uint32_t valor, uint8_t offset) {
	return bitWrite(valor, offset, true);
}
/*==============================================================================
RESET BIT
==============================================================================*/
uint32_t bitReset(uint32_t valor, uint8_t offset) {
	return bitWrite(valor, offset, false);
}
/*==============================================================================
FIM DO ARQUIVO
==============================================================================*/
