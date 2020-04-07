/*
 * 02_simple_display_mux.c
 *
 *  Created on: Feb 27, 2020
 *      Author: Renan Augusto Starke
 *      Instituto Federal de Santa Catarina
 */
#include <msp430.h>
#include "simple_display_mux.h"

/* Tipos uint16_t, uint8_t, ... */
#include <stdint.h>

#define ENCODER_INPUT           BIT3
#define LED_DEBUG               BIT0

volatile uint16_t pulses;

void encoder_init(void)
{
    P1DIR = LED_DEBUG;
    P2REN = ENCODER_INPUT;
    P2OUT = ENCODER_INPUT;
    P2IE = ENCODER_INPUT;
    P2IES = ENCODER_INPUT;
    P2IFG &= ~ENCODER_INPUT;
}

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;

#if defined (__MSP430FR2355__)
    /* Disable the GPIO power-on default high-impedance mode */
    PM5CTL0 &= ~LOCKLPM5;
#endif

    pulses = 0;

    display_mux_init();

    encoder_init();

    /* Habilita IRQs e desliga CPU */
    __bis_SR_register(LPM4_bits | GIE);

    while (1)
    {
		pulses = pulses & 0x0FFF;
        display_mux_write(pulses);
        __bis_SR_register(LPM4_bits);
    }
}

/* Port 2 ISR (interrupt service routine) */
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(PORT1_VECTOR))) Port_1 (void)
#else
#error Compiler not supported!
#endif
{
    /* Liga/desliga LED quando detectado borda no encoder */
    P1OUT ^= LED_DEBUG;

    /* Conta o número de pulsos */
    pulses++;

    /* Limpa sinal de IRQ do botão 0 */
    P2IFG &= ~ENCODER_INPUT;

    /* Essa linha deve ser descomentada para o main executar */
    __bic_SR_register_on_exit(LPM4_bits);
}
