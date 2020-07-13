/*
 * pwm.h
 *
 *  Created on: 29 de abr de 2020
 *      Author: Guilherme Camargo Valese
 */
#ifndef PWM_H_
#define PWM_H_

#include <stdint.h>

#define PWM_PERIOD   3000-1     // Para frequência de 1kHz , fonte de clock (SMCLK/8)

typedef enum
{
    PWM0,
    PWM1,
}pwm_channel_t;


void pwm_init(void);
void set_pwm_dt(pwm_channel_t channel, uint16_t dt);

#endif /* PWM_H_ */
