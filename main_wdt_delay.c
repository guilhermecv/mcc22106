#include <msp430.h> 
#include "lib/clock_system.h"
#include "wdt_delay/wdt_delay.h"


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	PM5CTL0 &= ~LOCKLPM5;
	
	init_clock_system();
	config_wd_as_timer();

	P1DIR |= BIT0;
	P6DIR |= BIT6;

	while(1)
	{
	    P1OUT ^= BIT0;
	    delay_wdt(100);
	    P6OUT ^= BIT6;
	}
}
