///////////////////////////////////////////////////////////////////////////////
//ARQUIVO:    SubrotinasHectarimetro
//AUTOR:      Fábio Almeida
//CIRADO:     05/01/2024
//OBSERVAÇÕES:
////////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "global.h"
/*=============================================================================
CONSTANTES DO ARQUIVO
==============================================================================*/
#define TRANSFORMA_M2_EM_HA 10000
/*=============================================================================
CALCULA HECTARIMETRO
==============================================================================*/
void calculaHectarimetro() {
	uint32_t calculaArea = larguraMaquina / 10;//remove uma casa dos cm
	calculaArea *= hodometroMetros;
	calculaArea /= 10; //remove uma casa decimal do hodometro metros
	calculaArea /= 10; //transforma a largura em m
	calculaArea /= TRANSFORMA_M2_EM_HA;
	hectarimetro = calculaArea;
}
/*==============================================================================
CALCULA DISTANCIA PARA UM HECTARE
==============================================================================*/
void calculaDistanciaUmHectare() {
	distanciaParaUmHectare = TRANSFORMA_M2_EM_HA;
	distanciaParaUmHectare *= 100; //a largura da maquina esta em cm
	distanciaParaUmHectare /= larguraMaquina;
}
/*=============================================================================
FIM DO ARQUIVO
==============================================================================*/
