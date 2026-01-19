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
