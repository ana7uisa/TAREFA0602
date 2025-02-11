// Inclusão das bibliotecas necessárias para entrada/saída padrão e controle de PWM no Raspberry Pi Pico
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

// Definição dos pinos onde os dispositivos estão conectados
#define SERVO_PIN 22      // Pino usado para controlar o servo motor
#define LED_RED_PIN 12    // Pino onde o LED vermelho está conectado

// Configuração do PWM (Pulse Width Modulation - Modulação por Largura de Pulso)
#define PWM_CLOCK_DIVIDER 64.0    // Define a frequência do PWM, garantindo compatibilidade com servos
#define PWM_PERIOD_US 20000.0     // Período do sinal PWM (20ms), padrão para servos
#define PWM_TOP_VALUE 39063       // Valor máximo do contador do PWM, ajustado para a frequência desejada

// Variáveis que armazenam os identificadores dos canais de PWM usados
uint slice_servo;
uint slice_led;

// Converte um tempo de pulso (em microssegundos) para um valor de duty cycle compatível com o PWM
static uint16_t calcular_duty_cycle(float tempo_pulso_us) {
    return (uint16_t)((tempo_pulso_us / PWM_PERIOD_US) * PWM_TOP_VALUE);
}

// Define a largura do pulso PWM para um pino específico
static void definir_pwm(uint slice, uint gpio, float tempo_pulso_us) {
    uint16_t duty_cycle = calcular_duty_cycle(tempo_pulso_us);
    pwm_set_gpio_level(gpio, duty_cycle); // Configura o nível de saída PWM correspondente ao tempo de pulso desejado
}

// Configura um pino para operar no modo PWM
static void configurar_pwm(uint gpio, uint *slice_num) {
    gpio_set_function(gpio, GPIO_FUNC_PWM);  // Configura o pino como saída PWM
    *slice_num = pwm_gpio_to_slice_num(gpio); // Obtém o identificador do canal de PWM associado ao pino
    
    pwm_set_clkdiv(*slice_num, PWM_CLOCK_DIVIDER); // Define a divisão de clock para ajustar a frequência do PWM
    pwm_set_wrap(*slice_num, PWM_TOP_VALUE);       // Configura o valor máximo do contador PWM
    pwm_set_enabled(*slice_num, true);            // Ativa o PWM para o canal correspondente
}

int main() {
    stdio_init_all(); // Inicializa a comunicação padrão (caso seja necessário para depuração)

    // Configuração inicial dos pinos do servo motor e do LED para operar com PWM
    configurar_pwm(SERVO_PIN, &slice_servo);
    configurar_pwm(LED_RED_PIN, &slice_led);

    sleep_ms(2000);  // Aguarda um curto período antes de iniciar os movimentos

    // Movimentos iniciais do servo motor e variação do brilho do LED
    definir_pwm(slice_servo, SERVO_PIN, 2400); // Define o servo na posição máxima (~180°)
    definir_pwm(slice_led, LED_RED_PIN, 2400); // Define o brilho máximo do LED
    sleep_ms(5000); // Aguarda 5 segundos

    definir_pwm(slice_servo, SERVO_PIN, 1470); // Define o servo na posição central (~90°)
    definir_pwm(slice_led, LED_RED_PIN, 1470); // Ajusta o brilho do LED proporcionalmente
    sleep_ms(5000);

    definir_pwm(slice_servo, SERVO_PIN, 500);  // Define o servo na posição mínima (~0°)
    definir_pwm(slice_led, LED_RED_PIN, 500);  // Define o brilho mínimo do LED
    sleep_ms(5000);

    // Movimento contínuo e suave do servo e LED variando entre mínimo e máximo
    while (true) {
        // Movimenta do menor para o maior ângulo gradualmente
        for (float pulso = 500; pulso <= 2400; pulso += 5) {
            definir_pwm(slice_servo, SERVO_PIN, pulso);
            definir_pwm(slice_led, LED_RED_PIN, pulso);
            sleep_ms(10); // Pequeno atraso para criar um movimento suave
        }

        // Movimenta do maior para o menor ângulo gradualmente
        for (float pulso = 2400; pulso >= 500; pulso -= 5) {
            definir_pwm(slice_servo, SERVO_PIN, pulso);
            definir_pwm(slice_led, LED_RED_PIN, pulso);
            sleep_ms(10); // Pequeno atraso para manter um movimento fluido
        }
    }

    return 0;
}
