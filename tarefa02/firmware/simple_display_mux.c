/*
 * simple_display_mux.c
 *
 *  Created on: Feb 27, 2020
 *      Author: Renan Augusto Starke
 *      Instituto Federal de Santa Catarina
 */
#include <msp430.h>
#include <stdint.h>
#include "simple_display_mux.h"

/* Tabela de conversão em flash: Anodo comum */
#ifdef COM_ANODO
const uint8_t convTable[] = { 0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78,
                              0x00, 0x18, 0x08, 0x03, 0x46, 0x21, 0x06, 0x0E };
#endif

/* Tabela de conversão em flash: Catodo comum */
#ifdef COM_CATODO
const uint8_t convTable[] = {0xBF, 0x86, 0xDB, 0xCF, 0xE6, 0xED, 0xFD,
        0x87, 0xFF, 0xE7, 0xF7, 0xFC, 0xB9, 0xDE, 0xF9, 0xF1};
#endif

void display_mux_init()
{
    /* Configuração de portas */
    DISPLAYS_DATA_PORT_DIR = 0xff;
    DISPLAYS_DATA_PORT_OUT = 0;

    DISPLAYS_MUX_PORT_DIR |= 0x07;
    DISPLAYS_MUX_PORT_OUT = 0;
}

void display_mux_write(uint16_t data)
{
    int8_t n = NUMBER_DISPLAYS;

    for (n = NUMBER_DISPLAYS; n > 0; n--)
    {
        /* Desliga todos os displays */
        DISPLAYS_MUX_PORT_OUT = 0;
        /* Escreve valor convertido do dígito 1 no GPIO */
        DISPLAYS_DATA_PORT_OUT = convTable[(data & 0x0F00) >> 8];
        /* Liga display 1 */
        DISPLAYS_MUX_PORT_OUT = 0x01;
        /* Mantém um tempo ligado:  */
        _delay_cycles(1000);

        /* Desliga display 1 */
        DISPLAYS_MUX_PORT_OUT = 0;
        /* Escreve valor convertido do dígito 2 no GPIO */
        DISPLAYS_DATA_PORT_OUT = convTable[(data & 0x00F0) >> 4];
        /* Liga display 2 */
        DISPLAYS_MUX_PORT_OUT = 0x02;
        /* Mantém um tempo ligado */
        _delay_cycles(1000);

        /* Desliga display 2 */
        DISPLAYS_MUX_PORT_OUT = 0;
        /* Escreve valor convertido do dígito 2 no GPIO */
        DISPLAYS_DATA_PORT_OUT = convTable[data & 0x000F];
        /* Liga display 3 */
        DISPLAYS_MUX_PORT_OUT = 0x04;
        /* Mantém um tempo ligado */
        _delay_cycles(1000);

        DISPLAYS_MUX_PORT_OUT = 0;
    }
}
