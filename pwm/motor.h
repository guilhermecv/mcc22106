/**
 * motor.h
 *
 */
#ifndef MOTOR_H
#define MOTOR_H

#include <stdint.h>

#define PWM_PERIOD      3000-1

typedef enum
{
    STOP,
    FRONT,
    BACK,
    RIGHT,
    LEFT,
}motor_direction_t;

void motor_init(void);

void set_pwm_dt(uint16_t dt);

void set_motor_direction(motor_direction_t dir);

uint16_t get_pwm_dt(void);

#endif
