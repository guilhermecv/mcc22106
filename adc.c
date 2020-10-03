/*
 * 06_main_adc_isr_timer_fr2355.c
 *
 *  Created on: Oct 02, 2020
 *      Renan Augusto Starke
 *      Instituto Federal de Santa Catarina
 *
 *      Exemplo do conversor analógico digital.
 *      - Trigger do ADC pelo timer B1.1
 *      - Sequẽncia de canais A0->A1->A2
 *      - ISR do timer desnecessário pois usa-se o hardware
 *      do timer para iniciar uma nova conversão
 *
 *
 *                  MSP430FR2355
 *               -----------------
 *           /|\|              XIN|-
 *            | |                 |
 *            --|RST          XOUT|-
 *              |                 |
 *  LED    <--  | P1.6    P1.0 A0 | <--
 *              |         P1.1 A1 | <--
 *              |         P1.2 A2 | <--
 *              |                 |
 *
 *      Modificado por Guilherme em 02/10/20
 */
#include <msp430.h>
#include "adc.h"
#include "lib/bits.h"

volatile battery_voltage_t *battery;

/**
 * @brief Inicializa o ADC utilizando o Timer B como trigger
 * @param battery: Estrutura que receberá os dados
 * @retval none
 */
void adc_init(battery_voltage_t *battery_voltage)
{
    /* Contagem máxima do timer 1 */
    TB1CCR0 = 200 - 1;
    /* Habilita saída interna do do comparador 0: CCR1 reset/set */
    TB1CCTL1 = OUTMOD_7;
    /* Valor de comparação 1: deve ser menor que TB1CCR0 */
    TB1CCR1 = 100;
    /* Configura timerB1:
     * - TBSSEL_2: SMCLK como clock source
     * - MC_2: modo de contagem contínua
     * - TBCLR: limpa registrador de contagem
     */
    TB1CTL = TBSSEL_2 | MC_2 | TBCLR | ID_3;

    P1SEL0 |=  BIT1 + BIT2;
    P1SEL1 |=  BIT1 + BIT2;

    ADCCTL0 |= ADCSHT_2
            | ADCON;

    ADCCTL1 |= ADCSHP
            | ADCSHS_2
            | ADCCONSEQ_3;

    ADCCTL2 |= ADCRES_1; /* 12 bit */

//    /* A0~2(EoS); Vref=AVCCV */
    ADCMCTL0 |= ADCINCH_2;
//            | ADCSREF_0;

    ADCIE |= ADCIE0;

//    PMMCTL0_H = PMMPW_H;
//    PMMCTL2 |= INTREFEN;
//    __delay_cycles(400);

    ADCCTL0 |= ADCENC;
    TB1CTL |= TBCLR;

    P4DIR |= BIT4;

    battery = battery_voltage;
}


// ADC interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(ADC_VECTOR))) ADC_ISR (void)
#else
#error Compiler not supported!
#endif
{
    static uint8_t i = 0;

    switch (__even_in_range(ADCIV, ADCIV_ADCIFG))
    {
    case ADCIV_NONE:
        break;
    case ADCIV_ADCOVIFG:
        break;
    case ADCIV_ADCTOVIFG:
        break;
    case ADCIV_ADCHIIFG:
        break;
    case ADCIV_ADCLOIFG:
        break;
    case ADCIV_ADCINIFG:
        break;
    case ADCIV_ADCIFG:

        if (i == 0)
            i = 2;
        else
            i--;

        /* Obter amostras */
        if (i == 2)
            battery->cell_1 = ADCMEM0;
        else if (i == 1)
            battery->cell_0 = ADCMEM0;
        else
            ADCMEM0;

        P4OUT ^= BIT4;
        break;
    default:
        break;
    }
}
