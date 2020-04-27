/*
 * timer_a_display_mux.h
 *
 *  Created on: 27 de abr de 2020
 *      Author: Guilherme
 */

#ifndef TIMER_A_DISPLAY_MUX_H_
#define TIMER_A_DISPLAY_MUX_H_

#include <stdint.h>


#define COM_ANODO
//#define COM_CATODO

#define DISPLAYS_DATA_PORT P1
#define DISPLAYS_MUX_PORT P3


void display_init(void);
inline void display_write(uint16_t data);


#endif /* TIMER_A_DISPLAY_MUX_H_ */
