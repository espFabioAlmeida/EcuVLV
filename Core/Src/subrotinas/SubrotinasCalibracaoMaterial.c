///////////////////////////////////////////////////////////////////////////////
//ARQUIVO:    SubrotinasCalibracaoMaterial
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
void verificaCalibracaoMaterial() {

	if(flagOperacao) {
		comandoCalibracaoMaterial = CANCELAR_CALIBRACAO_MATERIAL;
		flagCalibracaoAdubo = false;
		flagCalibracaoSemente = false;
		contadorCalibracaoMaterial = 0;
		return;
	}

	if(comandoCalibracaoMaterial == CANCELAR_CALIBRACAO_MATERIAL) {
		flagCalibracaoAdubo = false;
		flagCalibracaoSemente = false;
		contadorCalibracaoMaterial = 0;
		return;
	}

	switch(comandoCalibracaoMaterial) {
		case ACIONA_ADUBO_10:
		case ACIONA_ADUBO_40:
		case ACIONA_ADUBO_70:
		case ACIONA_ADUBO_100:
			flagCalibracaoAdubo = true;
			flagCalibracaoSemente = false;
			contadorCalibracaoMaterial = 1;
			return;

		case ACIONA_SEMENTE_10:
		case ACIONA_SEMENTE_40:
		case ACIONA_SEMENTE_70:
		case ACIONA_SEMENTE_100:
			flagCalibracaoAdubo = false;
			flagCalibracaoSemente = true;
			contadorCalibracaoMaterial = 1;
			return;
	}
}
/*=============================================================================
FIM DO ARQUIVO
==============================================================================*/
