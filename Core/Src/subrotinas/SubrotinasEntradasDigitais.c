///////////////////////////////////////////////////////////////////////////////
//ARQUIVO:    SubrotinasEntradasDigitais
//AUTOR:      Fábio Almeida
//CIRADO:     05/01/2024
//OBSERVAÇÕES:
////////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "global.h"
/*=============================================================================
CONSTANATES DO ARQUIVO
==============================================================================*/
#define TRANSFORMA_MS_EM_KMH 36
#define PULSOS_METRO_GPS 60
#define VELOCIDADE_MINIMA 2
#define ESTOURO_HODOMETRO_EM_M 14316557
/*=============================================================================
CALCULA VELOCIDADE EM M/S
==============================================================================*/
uint32_t calculaVelocidadeMetrosSegundo(uint32_t valor) {
	valor *= 10000; //empresta 5 digitos
	valor /= TRANSFORMA_MS_EM_KMH; //transofmra novamente em m/s, removendo 1 casa decimal
	return valor;
}
/*=============================================================================
LEITURA SENSOR DE VELOCIDADE
==============================================================================*/
void leituraSensorVelocidade() {
	static uint8_t sensorAcionado = false;
	static uint16_t contadorVelocidade = 0, contador1s = 0;
	uint8_t flagContingencia = false;
	uint32_t velocidadeMetrosSegundo = 0;

	if(sensorAcionado) {
		if(input(IN1_GPIO_Port, IN1_Pin)) {
			sensorAcionado = false;
		}
	}
	else {
		if(!input(IN1_GPIO_Port, IN1_Pin)) {
			sensorAcionado = true;
			contadorVelocidade ++;
			if(flagCalibracaoPulsosPor100m) {
				contadorPulsosPor100m ++;
			}
		}
	}

	contador1s ++;
	if(contador1s >= 1000) {
		uint32_t valor = contadorVelocidade;

		if(tipoSensorVelocidade == SENSOR_PULSOS) {
			valor *= 100000; //regra de 3 com a calibração de 100m e empresta mais 4 dígitos (100m * 1000)
			valor /= pulsosPor100m;
		}
		else { //GPS
			valor *= 1000; //empresta 4 digitos para precisão nos calculos
			valor /= PULSOS_METRO_GPS;
		}
		velocidadeMetrosSegundo = valor; //guarda o valor para o hectarimetro
		valor *= TRANSFORMA_MS_EM_KMH; //transforma em km/h (3,6) emprestando mais uma casa decimal (36)
		valor /= 10000; //devolve os 5 dígitos emprestados

		velocidade = valor;
		if(velocidade < VELOCIDADE_MINIMA) { //assume a contingencia
			if(flagOperacao) {
				velocidade = velocidadeContingencia;
				valor = velocidade;
				valor *= 10000; //empresta 5 digitos
				valor /= TRANSFORMA_MS_EM_KMH; //transofmra novamente em m/s, removendo 1 casa decimal
				velocidadeMetrosSegundo = valor; //atribui novo valor ao hectarimetro
				flagContingencia = true;
			}
			else {
				velocidade = 0;
			}
		}

		if(velocidade && !flagContingencia) { //aplica o offset da velocidade apenas se fora da contingencia
			uint8_t velocidadeAnterior = velocidade;
			if(flagOffsetVelocidadeNegativo) {
				if(velocidade > offsetVelocidade) {
					velocidade -= offsetVelocidade;
				}
				else {
					velocidade = 0;
				}
			}
			else {
				velocidade += offsetVelocidade;
			}

			if(velocidadeAnterior != velocidade) {
				valor = velocidade;
				valor *= 10000; //empresta 5 digitos
				valor /= TRANSFORMA_MS_EM_KMH; //transofmra novamente em m/s, removendo 1 casa decimal
				velocidadeMetrosSegundo = valor; //atribui novo valor ao hectarimetro
			}
		}

		if(flagOperacao) { //hectarimetro
			velocidadeMetrosSegundo /= 100; //remove 3 casas decimais
			hodometroMetros += velocidadeMetrosSegundo;
			if(hodometroMetros >= ESTOURO_HODOMETRO_EM_M) {
				hodometroMetros = 0;
			}
			flagSalvaHectarimetro = true;
		}

		contador1s = 0;
		contadorVelocidade = 0;
	}
}
/*=============================================================================
LEITURA ENTRADAS DIGITAIS
==============================================================================*/
void leituraEntradasDigitais() {


}
/*=============================================================================
FIM DO ARQUIVO
==============================================================================*/
