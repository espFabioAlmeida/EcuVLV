///////////////////////////////////////////////////////////////////////////////
//ARQUIVO:    Scheduler
//AUTOR:      Fábio Almeida
//CRIADO:     04/08/2023
//OBSERVAÇÕES:
////////////////////////////////////////////////////////////////////////////////
# include "main.h"
# include "global.h"
/*==============================================================================
TAREFAS 100us
==============================================================================*/
void tarefas100us() {

}
/*==============================================================================
TAREFAS 1ms
==============================================================================*/
void tarefas1ms() {

}
/*==============================================================================
TAREFAS 10ms
==============================================================================*/
void tarefas10ms() {

}
/*==============================================================================
TAREFAS 100ms
==============================================================================*/
void tarefas100ms() {
	static uint8_t conta500ms = 0;
	reiniciaWatchDog();

	if(flagLedCOM) {
		off(LED_COM1_GPIO_Port, LED_COM1_Pin);
		flagLedCOM = false;
	}
	else {
		on(LED_COM1_GPIO_Port, LED_COM1_Pin);
	}

	if(flagLedIHM) {
		off(LED_IHM_GPIO_Port, LED_IHM_Pin);
		flagLedIHM = false;
	}
	else {
		on(LED_IHM_GPIO_Port, LED_IHM_Pin);
	}

	if(contadorCalibracaoMaterial && contadorCalibracaoMaterial < TIMEOUT_CALIBRACAO_MATERIAL) {
		contadorCalibracaoMaterial ++;
	}

	conta500ms ++;
	if(conta500ms >= 5) {
		conta500ms = 0;

		flagEnviaPacoteCAN = true;
		flagCalculaSetpoint = true;
	}
}
/*==============================================================================
TAREFAS 1s
==============================================================================*/
void tarefas1s() {
	toggle(LED_CPU_GPIO_Port, LED_CPU_Pin);

	for(uint8_t i = 0; i < QUANTIDADE_MAXIMA_MODULOS; i ++) {
		if(contadorModuloOffline[i]) {
			contadorModuloOffline[i] --;
		}
	}
}
/*==============================================================================
SCHEDULER
==============================================================================*/
void schedulerEngine() {
	static uint8_t conta100us = 0, conta1ms = 0, conta10ms = 0, conta100ms = 0;
	//Essa rotina deve ser chamada através de um timer configurado em 100us

	tarefas100us();
	conta100us ++;

	if(conta100us >= 10) {
		conta100us = 0;
		tarefas1ms();
		conta1ms ++;

		if(conta1ms >= 10) {
			conta1ms = 0;
			tarefas10ms();
			conta10ms ++;

			if(conta10ms >= 10) {
				conta10ms = 0;
				tarefas100ms();
				conta100ms ++;

				if(conta100ms >= 10) {
					conta100ms = 0;
					tarefas1s();
				}
			}
		}
	}
}
/*==============================================================================
FIM DO ARQUIVO
==============================================================================*/
