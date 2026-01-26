///////////////////////////////////////////////////////////////////////////////
//ARQUIVO:    SubrotinasCalibracaoPulsos
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
VERIFICA CALIBRACAO MATERIAL
==============================================================================*/
void verificaCalibracaoPulsos() {

	if(flagOperacao) {
		flagCalibracaoPulsosPor100m = false;
		contadorPulsosPor100m = 0;
		return;
	}

	if(comandoCalibracaoPulsos == CANCELAR_CALIBRACAO_PULSOS) {
		flagCalibracaoPulsosPor100m = false;
		contadorPulsosPor100m = 0;
		return;
	}

	switch(comandoCalibracaoPulsos) {
		case INICIAR_CALIBRACAO_PULSOS:
			flagCalibracaoPulsosPor100m = true;
			contadorPulsosPor100m = 0;
			return;

		case FINALIZAR_CALIBRACAO_PULSOS:
			flagCalibracaoPulsosPor100m = false;
			pulsosPor100m = contadorPulsosPor100m;
			contadorPulsosPor100m = 0;
			writeEepromPulsosPor100m();
			return;
	}
}
/*=============================================================================
FIM DO ARQUIVO
==============================================================================*/
