///////////////////////////////////////////////////////////////////////////////
//ARQUIVO:    UtilityGPIO
//AUTOR:      Fábio Almeida
//CRIADO:     04/08/2023
//OBSERVAÇÕES:
////////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "global.h"
/*==============================================================================
DEBOUNCE
==============================================================================*/
uint8_t debounce(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
	#ifndef DEBOUNCE
		#define DEBOUNCE 120
	#endif

	if(!HAL_GPIO_ReadPin(GPIOx, GPIO_Pin)) {
		HAL_Delay(DEBOUNCE);
		if(!HAL_GPIO_ReadPin(GPIOx, GPIO_Pin)) {
			return true;
		}
	}

	return false;
}
/*==============================================================================
DEBOUNCE INVERSO
==============================================================================*/
uint8_t debounceInverso(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
	#ifndef DEBOUNCE
		#define DEBOUNCE 120
	#endif

	if(HAL_GPIO_ReadPin(GPIOx, GPIO_Pin)) {
		HAL_Delay(DEBOUNCE);
		if(HAL_GPIO_ReadPin(GPIOx, GPIO_Pin)) {
			return true;
		}
	}

	return false;
}
/*==============================================================================
LEITURA ENTRADA
==============================================================================*/
uint8_t input(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
	if(HAL_GPIO_ReadPin(GPIOx, GPIO_Pin)) {
		return true;
	}
	return false;
}
/*==============================================================================
ACIONA SAIDA
==============================================================================*/
void on(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, 1);
}
/*==============================================================================
DESACIONA SAIDA
==============================================================================*/
void off(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, 0);
}
/*==============================================================================
INVERTE SAIDA
==============================================================================*/
void toggle(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
	HAL_GPIO_TogglePin(GPIOx, GPIO_Pin);
}
/*==============================================================================
SETA SAIDA
==============================================================================*/
void setPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState) {
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, PinState);
}
/*==============================================================================
FIM DO ARQUIVO
==============================================================================*/
