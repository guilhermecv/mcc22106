/*
 * timer_a_display_mux.c
 *
 *  Created on: 27 de abr de 2020
 *      Author: Guilherme
 *
 *      Adaptado de simple_display_mux.c
 *          Author: Renan Augusto Starke
 *          Instituto Federal de Santa Catarina
 */
#include "msp430.h"
#include "timer_a_display_mux.h"
#include "lib/bits.h"
#include "lib/gpio.h"

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

volatile struct display_status_t {
    uint16_t current_data;
    uint8_t i;

} my_displays;


/**
 * @brief Inicializa o display
 * @param none
 * @return none
 */
void display_init(void)
{
    TA1CTL = TASSEL_2       // Clock de SMCLK (Subsystem master clock)
           | MC_2           // Contagem crescente
           | ID_1           // prescaler 8
           | TAIE;          // habilita interrupção

    TA1CCTL0 = CCIE;        // IRQ por comparação

    TA1CCR1  = 50;          // Valor de comparação

    /* Estado inicial */
    my_displays.current_data = 0;
    my_displays.i = 0;

    /* ConfiguraÃ§Ã£o de portas */
    PORT_DIR(DISPLAYS_DATA_PORT) |= 0x7f;
    PORT_DIR(DISPLAYS_MUX_PORT) |= 0xf;
}

inline void display_write(uint16_t data)
{
    my_displays.current_data = data;
}

/* ISR0 do Timer A: executado no evento de comparação  comparador 0 (TACCR0) */
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER1_A0_ISR (void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER0_A0_VECTOR))) Timer_A (void)
#else
#error Compiler not supported!
#endif
{
    /* Separa os nibles dos dados em função de i */
    uint8_t data = my_displays.current_data >> (my_displays.i * 4);

    /* Converte dados */
    data = data & 0x0f;
    data = convTable[data];

    /* Desliga todos os displays e coloca dado convertido em DISPLAYS_DATA_PORT */
    PORT_OUT(DISPLAYS_MUX_PORT) &= ~(0x0f);
    PORT_OUT(DISPLAYS_DATA_PORT) = data;

    /* Liga cada display independentemente */
    SET_BIT(PORT_OUT(DISPLAYS_MUX_PORT), (1 << my_displays.i));

    /* Faz a variÃ¡vel i circular entre 0 e 3 */
    my_displays.i++;
    my_displays.i &= 0x03;
}


/* ISR1 do Timer A: executado toda a vez que o temporizador estoura, evento do comparador 1 ou evento do comparador 2 */
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = TIMER1_A1_VECTOR
__interrupt void TIMER1_A1_ISR (void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER0_A1_VECTOR))) TIMER0_A1_ISR (void)
#else
#error Compiler not supported!
#endif
{
  switch(__even_in_range(TA1IV,0x0A))
  {
      /* Vector  0:  No interrupt */
      case  TA1IV_NONE:
          break;

      /* Vector  2:  TACCR1 CCIFG -> Comparação 1*/
      case  TA1IV_TACCR1:

          break;
      /* Vector  4:  TACCR2 CCIFG -> Comparação 2*/
      case TA1IV_TACCR2:
          break;

      /* Vector  6:  Reserved  */
      case TA1IV_6:
          break;
      /* Vector  8:  Reserved  */
      case TA1IV_8:
          break;

      /* Vector 10:  TAIFG -> Overflow do timer 0*/
      case TA1IV_TAIFG:

          break;
      default:
          break;
  }
}
