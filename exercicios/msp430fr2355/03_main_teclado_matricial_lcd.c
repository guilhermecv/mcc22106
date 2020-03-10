/**
 * @file main.c
 */
#include <msp430.h>
#include "teclado_matricial/teclado.h"
#include "displays/lcd.h"

/**
 * @brief Inicializa o hardware
 */
void init()
{
#if defined (__MSP430FR2355__)
    WDTCTL = WDTPW | WDTHOLD;
    PM5CTL0 &= ~LOCKLPM5;
#endif

    lcd_init_4bits();

    keyboard_init();
}

/**
 * @brief
 */
void keyboard_task()
{
    
}

void main()
{
    init();
    
    while(1)
    {
        keyboard_task();
        _delay_cycles(100);
    }
}
