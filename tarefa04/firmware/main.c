#include <msp430.h>
#include "timer_a_display_mux.h"
#include "encoder_irq.h"

#ifndef __MSP430G2553__
    #error "Example not tested with this device!"
#endif



/**
  * @brief  Configura sistema de clock para usar o Digitally Controlled Oscillator (DCO).
  *         Utililiza-se as calibra��es internas gravadas na flash.
  *         Exemplo baseado na documenta��o da Texas: msp430g2xxx3_dco_calib.c
  *         Configura ACLK para utilizar VLO = ~10KHz
  * @param  none
  *
  * @retval none
  */
void init_clock_system(){

    /* Configura��o do MCLK em 8MHz */

    /* Se calibra��o foi apagada, para aplica��o */
    if (CALBC1_8MHZ==0xFF)
        while(1);

    DCOCTL = 0;
    BCSCTL1 = CALBC1_8MHZ;  // Basic clock system control
    DCOCTL = CALDCO_8MHZ;   // DCO clock frequency control

    /* Configura ACLK para usar VLO: ~10kHZ */
    BCSCTL3 |= LFXT1S_2;
}


void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	init_clock_system();

	display_init();

	encoder_init();

	__bis_SR_register(LPM0_bits + GIE);
}
