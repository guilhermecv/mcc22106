/*
 * 05_main_simple_wd_timer.c
 *
 *  Created on: Mar 27, 2020
 *      Author: Renan Augusto Starke
 *      Instituto Federal de Santa Catarina
 *
 *      Adaptado para o MSP430FR2355 em 13 de julho de 2020
 *      Guilherme Camargo Valese
 */
#include "wdt_delay.h"
#include <msp430.h>

volatile uint16_t counter;


/**
  * @brief  Configura temporizador watchdog.
  * @param  none
  * @retval none
  */
void config_wd_as_timer(void){
    /* Configura Watch dog como temporizador:
     *
     * WDT_ADLY_250 <= (WDTPW+WDTTMSEL+WDTCNTCL+WDTSSEL+WDTIS0)
     *
     * WDTPW -> "Senha" para alterar confgiuração.
     * WDTTMSEL -> Temporizador ao invés de reset.
     * WDTSSEL -> Fonte de clock de ACLK
     * WDTIS1+WDTIS0 -> Clock / 8192
     *
     * WDT is clocked by fACLK (assumed 32KHz)
     */
    WDTCTL = WDT_ADLY_1_9;
}


/**
 * @brief
 * @param ms: delay em ms
 * @retval nenhum
 */
void delay_wdt(uint16_t ms)
{
    /**
     Assumindo que o estouro do watchdog ocorre em aproximadamente 2ms,
     essa será a resolucao do delay.

     counter = ms >> 1;

     é equivalente a dividir por 2
     */
    counter = ms >> 1;
    SFRIE1 |= WDTIE;
    __bis_SR_register(LPM0_bits + GIE);
}


/* ISR do watchdog: executado toda a vez que o temporizador estoura */
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(WDT_VECTOR))) watchdog_timer (void)
#else
#error Compiler not supported!
#endif
{
    static uint16_t iter = 0;

    if(++iter == counter)
    {
        iter = counter = 0;
        __bic_SR_register_on_exit(LPM0_bits);
    }
}
