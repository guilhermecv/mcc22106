/**
 * @file main.c
 *
 * @author Guilherme Camargo Valese
 */

#include <msp430.h> 
#include "bit_utils.h"

#define SW0     BIT1
#define SW0_IN  P4IN
#define SW1     BIT3
#define SW1_IN  P2IN
#define LED0    BIT0
#define LED1    BIT6

#define DELAY   500

void init()
{
    // Necessário para MSP430FR23555
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings
    // LEDs
    P1DIR |= LED0;
    P6DIR |= LED1;

    // chaves
    P4REN |= SW0;
    P4OUT |= SW0;
    P2REN |= SW1;
    P2OUT |= SW1;
}


void main(void) {
    char pressed = 0;

    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer

    init();

    for(;;) {
        if(!tst_bit(SW0_IN, SW0))
            P1OUT |= LED0;
        else
            P1OUT &=~LED0;

        if(!tst_bit(SW1_IN, SW1))
        {
            if(!pressed)
            {
                P6OUT |= P6OUT ^LED1;
                pressed = 1;
            }
        }
        else
            pressed = 0;
    }
}
