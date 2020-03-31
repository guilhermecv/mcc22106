/*
 * teclado.h
 *
 *  Created on: 10 de mar de 2020
 *      Author: Guilherme Camargo Valese
 *
 *      Adaptado de AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.
 *      Instituto Federal de Santa Catarina
 */
#ifndef TECLADO_H
#define TECLADO_H

#define KEYBOARD_LINE_IN    P3IN
#define KEYBOARD_DIR        P3DIR
#define KEYBOARD_OUT        P3OUT
#define KEYBOARD_REN        P3REN


void keyboard_init(void);

unsigned char keyboard_read(void);

#endif /* TECLADO_H */
