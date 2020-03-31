/*
 * teclado.c
 *
 *  Created on: 10 de mar de 2020
 *      Author: Guilherme Camargo Valese
 *
 *      Adaptado de AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.
 *      Instituto Federal de Santa Catarina
 */

#include <msp430.h>
#include "teclado.h"
#include "bits.h"

/*
 * Mapeamento das teclas
 */
const unsigned char teclas  [4][4]={{'1', '6', '7', '*'},
                                    {'2', '5', '8', '0'},
                                    {'3', '4', '9', '#'},
                                    {'A', 'B', 'C', 'D'}};

const unsigned char bit_line[4]={BIT4, BIT5, BIT6, BIT7};

/**
 * @brief Inicializa os pinos de I/O do teclado
 */
void keyboard_init(void)
{
    KEYBOARD_DIR = 0x0F;
    KEYBOARD_REN = 0xF0;
    KEYBOARD_OUT = 0xFF;   // Habilita pull up
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
        CLR_BIT(KEYBOARD_OUT, (1 << n));
        for(i=0; i<4; i++)
        {
            if(!(KEYBOARD_LINE_IN & bit_line[i]))
            {
                tecla = teclas[n][i];
                while(!(KEYBOARD_LINE_IN & bit_line[i]));
            }
        }
        SET_BIT(KEYBOARD_OUT, (1 << n));
    }

    return tecla;
}
