# Simulação de Controle de Servomotor com PWM no Raspberry Pi Pico W

## Descrição do Projeto
Este projeto utiliza o módulo PWM (Pulse Width Modulation) do microcontrolador RP2040 para simular o controle de um servomotor micro servo padrão, utilizando o simulador online Wokwi. A implementação foi realizada em C, empregando o Pico SDK, e busca atender aos requisitos propostos.

## Requisitos do Sistema
Para a correta execução da simulação, foram considerados os seguintes componentes:
- **Microcontrolador Raspberry Pi Pico W**
- **Servomotor – Motor Micro Servo Padrão – Wokwi**
- **Ferramenta Educacional BitDogLab para experimentos adicionais**

## Configurações Implementadas
1. **Configuração da GPIO 22 com PWM de 50Hz**: O PWM foi configurado com um período de 20ms (frequência de aproximadamente 50Hz), conforme especificado.
2. **Posicionamento do Servomotor em 180°**: Para alcançar essa posição, o ciclo ativo do PWM foi ajustado para 2.400µs (0,12% duty cycle). O sistema aguarda 5 segundos nesta posição.
3. **Posicionamento do Servomotor em 90°**: O ciclo ativo do PWM foi ajustado para 1.470µs (0,0735% duty cycle), aguardando 5 segundos.
4. **Posicionamento do Servomotor em 0°**: O ciclo ativo do PWM foi ajustado para 500µs (0,025% duty cycle), aguardando 5 segundos.
5. **Movimentação suave e contínua do servomotor**: Foi implementada uma rotina que move o servo entre 0° e 180° de forma gradual, incrementando o duty cycle em ±5µs a cada 10ms.
6. **Teste com LED RGB na GPIO 12**: O comportamento do LED foi analisado ao sincronizar sua iluminação com os ajustes do PWM do servomotor.

## Desenvolvimento e Simulação
- O código foi desenvolvido no **Visual Studio Code**
- A linguagem utilizada foi **C**, empregando o **Pico SDK**
- O simulador **Wokwi** foi integrado ao ambiente para validação do comportamento do servomotor

## Observações e Conclusão
Durante os testes utilizando a ferramenta **BitDogLab**, foi observado que a iluminação do LED RGB na GPIO 12 variou de acordo com os ajustes do PWM do servomotor. Isso ocorre porque o mesmo sinal PWM foi aplicado ao LED, resultando em uma variação de brilho sincronizada com a movimentação do servo.

Este projeto demonstrou a utilização do PWM no Raspberry Pi Pico W para controle preciso de um servomotor, permitindo entender na prática a relação entre duty cycle e ângulo de posicionamento.

## Vídeo
https://drive.google.com/file/d/1WEsdxfXrZa9Xtw2_fHTVtjZPim_prrBQ/view?usp=sharing
