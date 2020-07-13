/*
 * main.c
 *
 *  Created on: 13 de jul de 2020
 *      Author: guilherme
 */

#ifndef __MSP430FR2355__
#error "Clock system not supported for this device"
#endif

#include <msp430.h>
#include "wdt_delay.h"
#include "lib/gpio.h"

#define LEDPORT         P1
#define LED0            BIT0

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;

    /* Disable the GPIO power-on default high-impedance mode */
    PM5CTL0 &= ~LOCKLPM5;

    init_clock_system();
    config_wd_as_timer();

    PORT_DIR(LEDPORT) = LED0;

    for(;;)
    {
        delay_wdt(500);
        PORT_OUT(LEDPORT) ^= LED0;
    }
}
