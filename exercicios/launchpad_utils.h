/*
 * launchpad_utils.h
 *
 *  Created on: 24 de fev de 2020
 *      Author: guilherme
 */

#ifndef LAUNCHPAD_UTILS_H_
#define LAUNCHPAD_UTILS_H_

#define SW1         BIT0
#define SW1_DIR     P4DIR
#define SW1_IN      P4IN
#define SW2         BIT3
#define SW2_DIR     P2DIR
#define SW2_IN      P2IN
#define LED1        BIT0
#define LED1_DIR    P1DIR
#define LED1_OUT    P1OUT
#define LED2        BIT6
#define LED2_DIR    P6DIR
#define LED2_OUT    P6OUT

#define set_led1()      (LED1_OUT |= LED1)
#define clr_led1()      (LED1_OUT &=~LED1)
#define cpl_led1()      (LED1_OUT |= LED1_OUT ^ LED1)
#define set_led2()      (LED2_OUT |= LED2)
#define clr_led2()      (LED2_OUT &=~LED2)
#define cpl_led2()      (LED2_OUT |= LED2_OUT ^ LED2)

#define led1_init()     (LED1_DIR |= LED1)
#define led2_init()     (LED2_DIR |= LED2)

#define sw1_init()      (SW1_DIR |= SW1)
#define sw2_init()      (SW2_DIR |= SW2)

#endif /* LAUNCHPAD_UTILS_H_ */
