/*
 * 02_main_7seg_button.c
 *
 *  Incrementa o dígito no display cada vez que a chave S2 é pressionada
 *  Zera o contador se S1 for pressionado
 *
 *  Created on: 3 de mar de 2020
 *      Author: guilherme
 */

#include <msp430.h>
#include <stdint.h>
#include "displays/led_display.h"
#include "bit_utils.h"

#define SW2_IN      P2IN
#define SW2         BIT3
#define SW1_IN      P4IN
#define SW1         BIT1


void main(void)
{
    /* Para o watchdog timer
     * Necessário para código em depuração */
    WDTCTL = WDTPW | WDTHOLD;
    PM5CTL0 &= ~LOCKLPM5;

    P2REN |= SW2;
    P2OUT |= SW2;
    P4REN |= SW1;
    P4OUT |= SW1;

    uint8_t x = 0;
    uint8_t pressed = 0;

    display_init();

    display_write(0);

    while(1)
    {
        if(!tst_bit(SW2_IN, SW2))
        {
            if(!pressed)
            {
                pressed = 1;
                display_write(x);
                x++;
                x = x & 0xf;
            }
        }
        else
        {
            pressed = 0;
        }

        if(!tst_bit(SW1_IN, SW1))
        {
            x = 0;
            display_write(x);
        }

    }
}
