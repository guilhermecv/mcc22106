/*
 * encoder_irq.c
 *
 *  Created on: 27 de abr de 2020
 *      Author: Guilherme
 */

#include <stdint.h>
#include "msp430.h"
#include "encoder_irq.h"
#include "timer_a_display_mux.h"

volatile uint16_t i = 0;

/**
 * @brief Inicializa o encoder
 * @param none
 * @return none
 */
void encoder_init(void)
{
    /* Pull up/down */
    P2REN = ENCODER;

    /* Pull up */
    P2OUT = ENCODER;

    /* Habilitação da IRQ apenas botão */
    P2IE =  ENCODER;

    /* Transição de nível alto para baixo */
    P2IES = ENCODER;

    /* Limpa alguma IRQ pendente */
    P2IFG &= ~ENCODER;
}


/* Port 2 ISR (interrupt service routine) */
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(PORT2_VECTOR))) Port_2 (void)
#else
#error Compiler not supported!
#endif
{
    /* Liga/desliga LED quando detectado borda no botão */
    display_write(i++);

    /* Limpa sinal de IRQ do botão 0 */
    P2IFG &= ~ENCODER;
}
