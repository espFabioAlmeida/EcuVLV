# ECU VLV
Projeto Automasensor: ECU VLV
# Hardware
Alimentação +12V <br>
2 portas CAN <br>
4 portas RS485 <br>
6 entradas digitais <br>
Bluetooth <br>
RTC <br>
# Entradas Digitais
IN1: Velocidade - GPS ou sensor de pulsos <br>
IN2: Sensor de Levante <br>
IN3: Home do controle de altura da haste<br>
IN4: Fim de curso do controle de altura da haste <br>
IN5: Leitura de pulsos do controle de altura da haste<br>
IN6: Livre <br>
# Devices
Barramento CAN: <br>
Acelerômetro/Inclinômetro (por hora, não utiliza) <br>
Acionamento do controle de altura da haste, placa transmissor CAN Motor V3 <br>
Até 8 Módulos comportas <br>
Até 8 Módulos esteiras/válvulas <br>
<br>
RS845 1:
Sensor de acidez de Solo <br>


# Escopo
O sistema deve controlar a aplicação de materia, conforme programado. <br>
O sistema deve controlar 2 materiais de forma destinta. Nome padrão é Adubo e Sementes <br>
O setpoint é em kg/ha <br>
O sistema deve monitorar a velocidade da máquina com o objetivo de adequar a aplicação do produto, visando manter o setpoint informado. <br>
O sistema deve possuir as seguintes configurações: <br>
1. Largura da máquina (cm), para transformar o deslocamento linear em área <br>
2. Offset de velocidade, para calibração <br>
3. Tipo de sensor de velocidade, pulsos ou GPS <br>
4. Velocidade de contingência, velocidade considerada em caso de falha na leitura <br>
O sistema também deve possuir a calibração dos saídas de forma independente (adubo e setpoint). <br>
Na calibração, o operador deve acionar a máquina em: 10%, 40%, 70% ou 100%. E informar ao sistema quantos g/min foi gerado. <br>
O sistema também deve possuir uma calibração do sensor de velocidade (pulsos). Onde o operador deve andar com a máquina por 100m e o sistema conta quantos pulsos foram gerados nessa distância. <br>
O sistema também deve possuir um hectarímetro. <br>
<br>
Os módulos de acionamento, sejam eles esteira ou válvula, serão cadastrados como adubo ou semente e também receberão uma identificação de seção, que pode ser entre 1 e 4. Essa seção agrupa os módulos que poderão serem desligados momentaneamente com a máquina operando. Lembrando que o setpoint é calculado como se todos os módulos estivessem ligados. <br>
O operador seleciona o que está sendo acionado, entre VOLLVERINI, ADUBO e SEMENTE. Ele poderá selecionar 1, 2 ou as 3 opções juntas. <br>
O equipamento monitora a entrada de levante, e quando acionada executa a operação desejada (caso tenha pelo menos 1). <br>
A operação VOLLVERINI consiste na descida da haste até o valor estipulado nas configurações. <br>
O operador deve conseguir abrir/fechar comportas, de forma totalmente manual e independente. <br>
O sensor de acidez de solo é apenas para apresentação ao operador. <br>
O operador pode controlar manualmente a descida da haste. <br>
<br>
O sistema de controle da haste deve ser calibrado com a quantidade de pulsos da régua + 1(fim de curso). <br>
O operador deve informar o comprimento total da haste (Fundo de escala). <br>

# Protocolo IHM
Comando 1: Atualziação dos comandos e dados: $,01,OPERACAO,S1,S2,S3,S4,COMPORTAS,HASTE,\r\n <br>
OPERACAO: 0=SEM OPERAÇÃO, +1 VOLLVERINI ATIVADO, +2 ADUBO ATIVADO e +4 SEMENTES ATIVADO <br>
S1,S2,S3,4: 0=DESLIGADO e 1=LIGADO <br>
COMPORTAS: 0=PARADO, 1=FECHAR e 2=ABRIR <br>
HASTE: 0=PARADO, 1=SUBIR e 2=DESCER Obs: A haste só opera manualmente com o sensor de levante desligado<br>
Resposta: $,01,SP_ADUBO,SP_SEMENTE,VELOCIDADE,ALTURA,ACIDEZ,HECTARIMETRO,OPERACAO,S1,S2,S3,S4,COMPORTAS,HASTE,SENSOR_LEVANTE,\r\n <br>
SP_ADUBO: Setpoint Adubo em kg/ha <br>
SP_SEMENTE: Setpoint Sementes em kg/ha <br>
VELOCIDADE: Velocidade da máquina em km/h <br>
ALTURA: Altura da haste em cm <br>
ACIDEZ: Medição do sensor de acidez (verificar unidade) <br>
HECTARÍMETRO: Valor total aplicado em ha (número grande) <br>
OPERACAO: Feedback do valor recebido <br>
S1,S2,S3,S4: Feedback do valor recebido <br>
COMPORTAS: Feedback do valor recebido <br>
HASTE: Feedback do valor recebido <br>
SENSOR_LEVANTE: 0=standby e 1=operando <br>
<br>
Comando 2: Configurações: $,02,SP_ADUBO,SP_SEMENTE,LARGURA_MAQUINA,+OFFSET_VELOCIDADE,TIPO_SENSOR,VELOCIDADE_CONTINGENCIA,\r\n <br>
SP_ADUBO: Setpoint Adubo em kg/ha. Entre 0 e 9999<br>
SP_SEMENTE: Setpoint Sementes em kg/ha. Entre 0 e 9999 <br>
LARGURA_MAQUINA: Largura da máquina em cm. Entre  100cm e 999999cm <br>
OFFSET_VELOIDADE: Velocidade que será somada. Enviar '+' ou '-' antes do valor, exemplo +5. Entre -9 e +9 km/h <br>
TIPO_SENSOR: 0=SENSOR GPS ou 1=SENSOR DE PULSOS <br>
VELOCIDADE_CONTINGENCIA: Velocidade assumida em cada de erro de leitura de velocidade em km/h. Entre 0km/h e 20km/h <br>
Resposta: Retorna os mesmos dados enviados apenas para conferência <br>
<br>
Comando 3: Leitura Configurações: $,03,\r\n <br>
Resposta: Envia os mesmos dados, na mesma ordem, do comando 2. <br>
<br>
Comando 4: Acionamento Calibração: $,04,COMANDO_CALIBRACAO,\r\n <br>
COMANDO_CALIBRACAO: 0=SEM COMANDO OU CANCELAR CALIBRACAO, 1=ACIONA_10_ADUBO, 2=ACIONA_40_ADUBO, 3=ACIONA_70_ADUBO, 4=ACIONA_100_ADUBO, 5=ACIONA_10_SEMENTE, 6=ACIONA_40_SEMENTE, 7=ACIONA_70_SEMENTE e 8=ACIONA_100_SEMENTE <br>
Resposta: Retorna os mesmos dados enviados, apenas para conferência <br>
<br>
Comando 5: Enviar dados da calibração: $,05,ADUBO_10,ADUBO_40,ADUBO_70,ADUBO_100,SEMENTE_10,SEMENTE_40,SEMENTE_70,SEMENTE_100,\r\n <br>
ADUBO_10,ADUBO_40,ADUBO_70,ADUBO_100: Valores de calibração em g/min do adubo. Entre 0 e 999999g/min <br>
SEMENTE_10,SEMENTE_40,SEMENTE_70,SEMENTE_100: Valores de calibração em g/min da semente. Entre 0 e 999999g/min <br>
Resposta: Retorna os mesmos dados enviados, apenas para conferência <br>
<br>
Comando 6: Leitura de dados da calibração: $,06,\r\n <br>
Respsota: Envia os mesmos dados, na mesma ordem, do comando 5. <br>
<br>
Comando 7: Calibração do sensor de pulsos: $,07,CALIBRACAO_SENSOR_PULSOS,\r\n <br>
CALIBRACAO_SENSOR_PULSOS: 0=CANCELAR CALIBRACAO, 1=INICIAR CALIBRAÇÃO e 2=FINALIZAR CALIBRAÇÃO <br>
É importante informar ao usuário que ao iniciar a calibração ele deve andar com a máquina 100m. <br>
Resposta: Ao cancelar ou iniciar apenas retorna os mesmos dados enviados para conferência. Quando enviar o comando para finalizar a calibração. O sistema enviará: $,07,PULSOS,\r\n <br>
PULSOS: 0=erro ou nenhum pulso lido. >0= Quantidade de pulsos lidos para a calibração. <br>
<br>
Comando 8: Zerar o Hectarímetro: $,08,\r\n <br>
Resposta: Envia o mesmos dados. Confirmando a operação <br>
<br>

# Protocolo CAN
A ECU possui um endereço para cada tipo de pacote. <br>
Endereço ECU Pacote 1: 0x1BB81A01 <br>
Endereço ECU Pacote 2: 0x1BB81A02 <br>
<br>
Pacote 1: <br>
BYTE 0: LSB PWM MODULO POTÊNCIA 90 <br>
BYTE 1: MSB PWM MODULO POTÊNCIA 90 <br>
BYTE 2: LSB PWM MODULO POTÊNCIA 91 <br>
BYTE 3: MSB PWM MODULO POTÊNCIA 91 <br>
BYTE 4: LSB PWM MODULO POTÊNCIA 92 <br>
BYTE 5: MSB PWM MODULO POTÊNCIA 92 <br>
BYTE 6: LSB PWM MODULO POTÊNCIA 93 <br>
BYTE 7: MSB PWM MODULO POTÊNCIA 93 <br>
<br>
Pacote 2: <br>
BYTE 0: LSB PWM MODULO POTÊNCIA 94 <br>
BYTE 1: MSB PWM MODULO POTÊNCIA 94 <br>
BYTE 2: LSB PWM MODULO POTÊNCIA 95 <br>
BYTE 3: MSB PWM MODULO POTÊNCIA 95 <br>
BYTE 4: LSB PWM MODULO POTÊNCIA 96 <br>
BYTE 5: MSB PWM MODULO POTÊNCIA 96 <br>
BYTE 6: LSB PWM MODULO POTÊNCIA 97 <br>
BYTE 7: MSB PWM MODULO POTÊNCIA 97 <br>