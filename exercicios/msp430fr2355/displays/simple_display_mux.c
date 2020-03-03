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
const uint8_t convTable[] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02,
        0x78, 0x00, 0x18, 0x08, 0x03, 0x46, 0x21, 0x06, 0x0E};
#endif


void display_mux_init() {

    /* Configuração de portas */
    DISPLAYS_DATA_PORT_DIR = 0xff;
    DISPLAYS_DATA_PORT_OUT = 0;

    DISPLAYS_MUX_PORT_DIR |= 0b00000011;
    DISPLAYS_MUX_PORT_OUT = 0;
}



void display_mux_write(uint8_t data){

    int8_t n = NUMBER_DISPLAYS;
//    data = data & 0xff;

    uint8_t byte_high, byte_low;

    byte_high = data>>4;
    byte_low = data&0x0F;

    for (n=NUMBER_DISPLAYS; n > 0; n--){
        /* Desliga todos os displays */
        DISPLAYS_MUX_PORT_OUT = 0;
        /* Escreve valor convertido do dígito 1 no GPIO */
        DISPLAYS_DATA_PORT_OUT = convTable[byte_high];
        /* Liga display 1 */
        DISPLAYS_MUX_PORT_OUT = 0x01;
        /* Mantém um tempo ligado:  */
        _delay_cycles(1000);

        /* Desliga display 1 */
        DISPLAYS_MUX_PORT_OUT = 0;
        /* Escreve valor convertido do dígito 2 no GPIO */
        DISPLAYS_DATA_PORT_OUT = convTable[byte_low];
        /* Liga display 2 */
        DISPLAYS_MUX_PORT_OUT = 0x02;
        /* Mantém um tempo ligado */
        _delay_cycles(1000);

        DISPLAYS_MUX_PORT_OUT = 0;
    }

}
