/*
 * teclado.h
 *
 *  Created on: 10 de mar de 2020
 *      Author: guilherme
 */

#ifndef TECLADO_MATRICIAL_TECLADO_H_
#define TECLADO_MATRICIAL_TECLADO_H_

#define KEYBOARD_LINE_IN    P1IN
#define KEYBOARD_LINE_DIR   P1DIR
#define KEYBOARD_LINE_OUT   P1OUT
#define KEYBOARD_LINE_REN   P1REN

void keyboard_init(void);
unsigned char keyboard_read(void);

#endif /* TECLADO_MATRICIAL_TECLADO_H_ */
