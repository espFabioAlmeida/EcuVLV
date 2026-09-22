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
		calibracaoMaterialSelecao = SELECIONA_TODOS;
		flagCalibracaoAdubo = false;
		flagCalibracaoSemente = false;
		calibracaoMaterialPercentual = 0;
		contadorCalibracaoMaterial = 0;
		return;
	}

	if(calibracaoMaterialSelecao == SELECIONA_TODOS) {
		flagCalibracaoAdubo = false;
		flagCalibracaoSemente = false;
		calibracaoMaterialPercentual = 0;
		contadorCalibracaoMaterial = 0;
		return;
	}

	if(calibracaoMaterialPercentual == 0) {
		contadorCalibracaoMaterial = 0;
		flagCalibracaoAdubo = false;
		flagCalibracaoSemente = false;
		return;
	}

	if(calibracaoMaterialSelecao == SELECIONA_ADUBO) {
		flagCalibracaoAdubo = true;
		flagCalibracaoSemente = false;
		contadorCalibracaoMaterial = 1;
		return;
	}

	if(calibracaoMaterialSelecao == SELECIONA_SEMENTE) {
		flagCalibracaoAdubo = false;
		flagCalibracaoSemente = true;
		contadorCalibracaoMaterial = 1;
	}
}
/*=============================================================================
FIM DO ARQUIVO
==============================================================================*/
