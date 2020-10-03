/*
 * main_ultrassonic.c
 *
 *  Created on: 27 de ago de 2020
 *      Author: Guilherme Camargo Valese
 */
#include <msp430.h>
#include "lib/clock_system.h"
#include "ultrassonic.h"


#ifdef UART_ON
#include "lib/uart_fr2355.h"
#endif

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;

    P6DIR = BIT6;

    init_clock_system();
    
    ultrassonic_init();

    while(1)
    {
//        get_distance();

        __bic_SR_register(GIE);
    }
}



