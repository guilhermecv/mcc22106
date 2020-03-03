/*
 * 02_simple_display_mux.c
 *
 *  Created on: Feb 27, 2020
 *      Author: Renan Augusto Starke
 *      Instituto Federal de Santa Catarina
 */

#include <msp430.h>

/* Tipos uint16_t, uint8_t, ... */
#include <stdint.h>

#include "displays/simple_display_mux.h"

void main(void)
{
    /* Para o watchdog timer
     * Necessário para código em depuração */
    WDTCTL = WDTPW | WDTHOLD;
    PM5CTL0 &= ~LOCKLPM5;

    volatile uint16_t i;
    uint8_t x = 0;

    /* Inicializa displays */
    display_mux_init();

    while(1)
    {
        display_mux_write(x);

        /* Delay */
        for(i=10000; i>0; i--);

        /* Incrementa e limita valor de x até 0x0f */
        x++;
    }
}
