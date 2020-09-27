/**
 * motor.c
 */
#include <msp430.h>
#include "motor.h"

volatile uint16_t pwm_dt;

/**
 * @brief Configura o PWM utilizando o timer B3
 * @param none
 * @retval none
 */
void motor_init(void)
{
    TB3CTL = TBSSEL_2       // SMCLK como fonte de clock
            | ID_3          // prescale 8
            | MC_1;         // UP mode

    TB3CCR0 = PWM_PERIOD;   // Periodo do PWM

    /* PWM output mode: Reset/Set */
    TB3CCTL1 = OUTMOD_7;
    TB3CCTL2 = OUTMOD_7;
    TB3CCTL3 = OUTMOD_7;
    TB3CCTL4 = OUTMOD_7;

    TB3CCR1 = 0;
    TB3CCR2 = 0;
    TB3CCR3 = 0;
    TB3CCR4 = 0;

    P6DIR |= BIT0
           | BIT1
           | BIT2
           | BIT3;

    /* Função alternativa */
    P6SEL0 |= BIT0
            | BIT1
            | BIT2
            | BIT3;
}

/**
 * @brief 
 * @param dir: 
 * @retval none
 */
void set_motor_direction(motor_direction_t dir)
{
    switch (dir)
    {
    default:
    case STOP:
        TB3CCR1 = 0;            // PWM duty cycle -> TB0CCR1/TB0CCR0
        TB3CCR2 = 0;
        TB3CCR3 = 0;
        TB3CCR4 = 0;
        pwm_dt = 0;
        break;

    case FRONT:
        TB3CCR1 = pwm_dt;            // PWM duty cycle -> TB0CCR1/TB0CCR0
        TB3CCR2 = 0;
        TB3CCR3 = pwm_dt;
        TB3CCR4 = 0;
        break;

    case BACK:
        TB3CCR1 = 0;            // PWM duty cycle -> TB0CCR1/TB0CCR0
        TB3CCR2 = pwm_dt;
        TB3CCR3 = 0;
        TB3CCR4 = pwm_dt;
        break;

    case LEFT:
        TB3CCR1 = pwm_dt;            // PWM duty cycle -> TB0CCR1/TB0CCR0
        TB3CCR2 = 0;
        TB3CCR3 = 0;
        TB3CCR4 = 0;
        break;

    case RIGHT:
        TB3CCR1 = 0;            // PWM duty cycle -> TB0CCR1/TB0CCR0
        TB3CCR2 = 0;
        TB3CCR3 = pwm_dt;
        TB3CCR4 = 0;
        break;
    }
}

/**
 * @brief Define o duty cycle do PWM
 * @param dt: duty cycle desejado
 * @retval none
 */
void set_pwm_dt(uint16_t dt)
{
    if(dt <= PWM_PERIOD)
        pwm_dt = dt;
}

uint16_t get_pwm_dt(void)
{
    return pwm_dt;
}
