/*
 * ultrassonic.c
 *
 *  Created on: 28 de ago de 2020
 *      Author: Guilherme Camargo Valese
 */
#include <msp430.h>
#include "lib/bits.h"
#include "ultrassonic.h"
#include <limits.h>

#define ULTRASSONIC_TIMEOUT     30

/* Variï¿½veis globais */
volatile uint8_t overflow = 0;
volatile uint16_t rise_timestamp = 0;
volatile uint16_t fall_timestamp = 0;
volatile uint32_t interval = 0;


/**
 * @brief Fornece um pulso de 10us no trigger
 * @param none
 * @retval none
 */
void pulse(void)
{
    CLR_BIT(P2OUT, TRIGGER);
    SET_BIT(P2OUT, TRIGGER);

    //    Aproximadamente 10us
    _delay_cycles(240);

    CLR_BIT(P2OUT, TRIGGER);
}


/**
 * @brief Inicia a medicao
 *        Configura timer B em modo captura
 * @param none
 * @retval interval: intervalo de medicao
 */
uint32_t get_distance(void)
{
    TB1CTL = TBSSEL_2
            | MC_2
            | TBCLR
            | TBIE;

    TB1CCTL1 = CAP
            | CM_3
            | SCS
            | CCIS_0
            | CCIE;

    pulse();

    __bis_SR_register(LPM0_bits + GIE);

    interval = overflow * UINT_MAX + fall_timestamp - rise_timestamp;

    return interval;
}


/**
 * @brief Inicializa o sensor ultrassônico
 * @param none
 * @retval none
 */
void ultrassonic_init(void)
{
    // LED de debug
    P1DIR = BIT0;

    P2REN  |= BIT0;

    P2OUT  |= BIT0;

    P2DIR |= TRIGGER;

    P2SEL0  |= BIT0;
}


/* ISR1 do Timer B: executado toda a vez que o temporizador estoura, evento do comparador 1 ou evento do comparador 2 */
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = TIMER1_B1_VECTOR
__interrupt void TIMER1_B1_ISR (void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER1_B1_VECTOR))) TIMER1_B1_ISR (void)
#else
#error Compiler not supported!
#endif
{
    switch(__even_in_range(TB1IV,0x0e))
    {
    /* Vector  0:  No interrupt */
    case  TB1IV_NONE:
        break;

        /* Vector  2:  TBCCR1 CCIFG -> Comparaï¿½ï¿½o 1 -> Primeiro sensor*/
    case  TB1IV_TBCCR1:
        if(TB1CCTL1 & CCI)
        {
            /* Borda de subida do sinal */
            rise_timestamp = TB1CCR1;
            overflow = 0;
        }
        else
        {
            /* Borde de descida do sinal */
            P1OUT ^= BIT0;
            fall_timestamp = TB1CCR1;
            TB1CTL = TBCLR;
            __bic_SR_register_on_exit(LPM0_bits + GIE);
        }
        break;

        /* Vector  4:  TBCCR2 CCIFG -> Comparaï¿½ï¿½o 2 -> Segundo sensor*/
    case TB1IV_TBCCR2:
        break;

        /* Vector 14:  TBIFG -> Overflow do timer 1*/
    case TB1IV_TBIFG:
        if(overflow++ >= ULTRASSONIC_TIMEOUT)
            __bic_SR_register_on_exit(LPM0_bits + GIE);

        break;

    default:
        break;
    }
}
