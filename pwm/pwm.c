/**
 * pwm.c
 *
 *  Author: Guilherme Camargo Valese
 *      Configura o PWM utilizando o Timer B3 no MSP430FR2355
 *        PWM0 -> P6.0
 *        PWM1 -> P6.1
 *
 *
 *      Adaptado de 05_main_simple_pwm.c (https://github.com/xtarke/msplibs/blob/master/05_main_simple_pwm.c)
 *      Author: Renan Augusto Xtarke
 */
#include <msp430.h>
#include <pwm.h>

/**
 * @brief Configura o PWM utilizando timer B3
 * @param none
 * @retval none
 */
void pwm_init(void)
{
    TB3CTL = TBSSEL_2       // SMCLK como fonte de clock
           | ID_3
           | MC_1;          // Timer mode: 1 - Up to CCR0

    TB3CCR0 = PWM_PERIOD;   // Periodo do PWM
    TB3CCTL1 = OUTMOD_7;    // PWM output mode: 7 - PWM reset/set - CCR1 reset/set                                                             */
    TB3CCTL2 = OUTMOD_7;

    TB3CCR1 = 0;            // PWM duty cycle -> TB0CCR1/TB0CCR0
    TB3CCR3 = 0;

    P6DIR = BIT0
          | BIT1;

    /* Função alternativa */
    P6SEL0 = BIT0
           | BIT1;
}


/**
 * @brief Altera o duty cycle do PWM
 * @param channel: canal do PWM
 * @param dt: duty cycle
 * @retval nenhum
 */
void set_pwm_dt(pwm_channel_t channel, uint16_t dt)
{
    switch (channel)
    {
    case PWM0:
        TB3CCR1 = dt;
        break;

    case PWM1:
        TB3CCR2 = dt;
        break;

    default:
        break;
    }
}
