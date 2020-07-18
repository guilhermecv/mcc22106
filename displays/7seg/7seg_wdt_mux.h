/*
 * simple_display_mux.h
 *
 *  Created on: Feb 27, 2020
 *      Author: Renan Augusto Starke
 *      Instituto Federal de Santa Catarina
 *
 *      Adaptado para o MSP430FR2355 em 14/07/2020
 *      Guilherme Camargo Valese
 */

#ifndef DISPLAYS_7SEG_7SEG_WDT_MUX_H_
#define DISPLAYS_7SEG_7SEG_WDT_MUX_H_

#include <stdint.h>

#define COM_ANODO
//#define COM_CATODO

#define DISPLAY_NUMBER              2
#define DISPLAYS_DATA_PORT          P1
#define DISPLAYS_MUX_PORT           P2

/**
  * @brief  Configura hardware.
  * @param  Nenhum
  *
  * @retval Nenhum.
  */
void display_init(void);

/**
  * @brief  Escrevre nos displays de 7 segmentos.
  * @param  data: valor sem decimal sem conversão. Dados
  *             são convertidos internamente. data
  *             deve ser maior caso mais de dois displays.
  *
  * @retval Nenhum.
  */
void display_write(uint16_t data);

#endif /* DISPLAYS_7SEG_7SEG_WDT_MUX_H_ */
