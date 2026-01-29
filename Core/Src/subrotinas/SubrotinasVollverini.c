///////////////////////////////////////////////////////////////////////////////
//ARQUIVO:    SubrotinasControle
//AUTOR:      Fábio Almeida
//CIRADO:     05/01/2024
//OBSERVAÇÕES:
////////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "global.h"
/*=============================================================================
CONSTANTES DO ARQUIVO
==============================================================================*/
/*=============================================================================
CALCULA QUANTIDADE DE PULSOS DO SETPOINT
==============================================================================*/
void calculaQuantidadePulsosSetpointHaste(uint32_t valorSetpoint) {
	valorSetpoint *= quantidadePulsosHaste;
	valorSetpoint /= tamanhoHaste;
	quantidadePulsosSetpointHaste = valorSetpoint;
}
/*=============================================================================
CALCULA A ALTURA DO ZERO DA HASTE
==============================================================================*/
void calculaAlturaZeroHaste() {
	uint32_t valor = contadorPulsosHaste;
	valor *= tamanhoHaste;
	valor /= quantidadePulsosHaste;

	alturaZeroHaste = valor;
}
/*=============================================================================
CALCULA A ALTURA PELA QUANTIDADE DE PULSOS
==============================================================================*/
void calculaAlturaHaste() {
	uint32_t valor = contadorPulsosHaste;
	valor *= tamanhoHaste;
	valor /= quantidadePulsosHaste; //valor da altura ABSOLUTA

	if(valor <= alturaZeroHaste) {
		valor = 0;
	}
	else {
		valor -= alturaZeroHaste; //tira o valor do zero da haste
	}

	alturaHaste = valor;
}
/*=============================================================================
CONTROLE HASTE
==============================================================================*/
void controleHaste() {

	if(flagOperacao) {
		if(flagOperacaoVollverini) {
			if(quantidadePulsosHaste < quantidadePulsosSetpointHaste) {
				comandoHaste = DESCER_HASTE;
			}
			else if(quantidadePulsosHaste > quantidadePulsosSetpointHaste) {
				comandoHaste = SUBIR_HASTE;
			}
			else {
				comandoHaste = PARAR_HASTE;
			}
		}
		else {
			comandoHaste = RETORNO_HASTE;
		}
	}

	//Verifica fim de curso
	switch(comandoHaste) {
		case RETORNO_HASTE:
		case SUBIR_HASTE:
			if(flagHomeHaste) {
				comandoHaste = PARAR_HASTE;
			}
			break;

		case DESCER_HASTE:
			if(flagFimCursoHaste) {
				comandoHaste = PARAR_HASTE;
			}
			break;
	}



}
/*=============================================================================
FIM DO ARQUIVO
==============================================================================*/
