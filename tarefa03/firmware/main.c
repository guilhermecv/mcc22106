/*
 * 05_main_simple_wd_timer.c
 *
 *  Created on: Mar 27, 2020
 *      Author: Renan Augusto Starke
 *      Instituto Federal de Santa Catarina
 */


#ifndef __MSP430G2553__
    #error "Clock system not supported for this device"
#endif

/* System includes */
#include <msp430.h>

/* Project includes */
#include "lib/gpio.h"
#include "delay_wdt.h"


#define LED         BIT0
#define LED_PORT    P2


int main(void)
{
    /* Desliga watchdog imediatamente */
    WDTCTL = WDTPW | WDTHOLD;

    /* Configurações de hardware */
    init_clock_system();

    config_wd_as_timer();

    PORT_DIR(LED_PORT) = BIT0 | BIT1;


    while(1)
    {
        delay_wdt(500);
//        PORT_OUT(LED_PORT, BIT0);
        P2OUT ^= BIT0;
    }
}



