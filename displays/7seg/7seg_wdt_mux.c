/*
 * simple_display_mux.c
 *
 *  Created on: Feb 27, 2020
 *      Author: Renan Augusto Starke
 *      Instituto Federal de Santa Catarina
 *
 *      Adaptado para o MSP430FR2355 em 14/07/2020
 *      Guilherme Camargo Valese
 */
#include <displays/7seg/7seg_wdt_mux.h>
#include <msp430.h>
#include "../../lib/gpio.h"
#include "../../lib/bits.h"

#ifndef __MSP430FR2355__
#error "Example not tested with this device!"
#endif

/* Tabela de conversão em flash: Anodo comum */
#ifdef COM_ANODO
const uint8_t convTable[] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02,
                             0x78, 0x00, 0x18, 0x08, 0x03, 0x46, 0x21, 0x06, 0x0E};
#endif

#ifdef COM_CATODO
const uint8_t convTable[] = {0xBF, 0x86, 0xDB, 0xCF, 0xE6, 0xED, 0xFD,
        0x87, 0xFF, 0xE7, 0xF7, 0xFC, 0xB9, 0xDE, 0xF9, 0xF1};
#endif


volatile struct display_status_t {
    uint16_t current_data;
    uint8_t i;
} my_displays;


/**
 * @brief  Configura hardware.
 * @param  Nenhum
 *
 * @retval Nenhum.
 */
void display_init(void)
{
    /* Estado inicial */
    my_displays.current_data = 0;
    my_displays.i = 0;

    /* Configuração de portas */
    PORT_DIR(DISPLAYS_DATA_PORT) |= 0x7f;
    PORT_DIR(DISPLAYS_MUX_PORT) |= 0xf;

    /* Configura Watch dog como temporizador:
     *
     * WDT_ADLY_1_9 <= (WDTPW+WDTTMSEL+WDTCNTCL+WDTSSEL+WDTIS1+WDTIS0)
     *
     * WDTPW -> "Senha" para alterar confgiuração.
     * WDTTMSEL -> Temporizador ao invés de reset.
     * WDTSSEL -> Fonte de clock de ACLK
     * WDTIS1+WDTIS0 -> Clock / 64
     *
     */
    WDTCTL = WDT_ADLY_1_9;

    /* Ativa IRQ do Watchdog */
    SFRIE1 |= WDTIE;
}

/**
 * @brief  Escrevre nos displays de 7 segmentos.
 * @param  data: valor sem decimal sem conversão. Dados
 *             são convertidos internamente. data
 *             deve ser maior caso mais de dois displays.
 *
 * @retval Nenhum.
 */
void display_write(uint16_t data)
{
    my_displays.current_data = data;
}

/* ISR do watchdog: executado toda a vez que o temporizador estoura */
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(WDT_VECTOR))) watchdog_timer (void)
#else
#error Compiler not supported!
#endif
{
    /* Separa os nibles dos dados em função de i */
    uint8_t data = my_displays.current_data >> (my_displays.i * 4);

    /* Converte dados */
    data = data & 0xf;
    data = convTable[data];

    /* Desliga todos os displays e coloca dado convertido em DISPLAYS_DATA_PORT */
    PORT_OUT(DISPLAYS_MUX_PORT) &= ~(0x0f);
    PORT_OUT(DISPLAYS_DATA_PORT) = data;

    /* Liga cada display independentemente */
    SET_BIT(PORT_OUT(DISPLAYS_MUX_PORT), (1 << my_displays.i));

    /* Faz a variável i circular entre 0 e 3 */
    my_displays.i++;
    my_displays.i &= 0x03;
}
