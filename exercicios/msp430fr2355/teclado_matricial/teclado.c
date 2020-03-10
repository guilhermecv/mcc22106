/*
 * teclado.c
 *
 *  Created on: 10 de mar de 2020
 *      Author: guilherme
 */
#include <msp430.h>
#include "teclado.h"

const unsigned char teclas  [4][4]={{'1', '2', '3', 'A'},
                                    {'4', '5', '6', 'B'},
                                    {'7', '8', '9', 'C'},
                                    {'D', '0', 'E', 'F'}};

/**
 * @brief Inicializa os pinos de I/O do teclado
 */
void keyboard_init(void)
{
    KEYBOARD_LINE_DIR = 0xF0;
    KEYBOARD_LINE_REN = 0x0F;
    KEYBOARD_LINE_OUT = 0x0F;
}

/**
 * @brief Verifica se alguma tecla foi pressionada
 * @return tecla: valor da tecla pressionada
 */
unsigned char keyboard_read(void)
{
    unsigned char n, i, tecla=0xFF;

    for(n=0; n<4; n++)
    {
        for(i=0; i<4; i++)
        {
            if(!(KEYBOARD_LINE_IN & i))
            {
                tecla = teclas[n][i];
            }
        }
    }

    return tecla;
}
