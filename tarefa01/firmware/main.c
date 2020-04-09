/**
 * @file main.c
 * @author Guilherme Camargo Valese
 */
#include <msp430.h>
#include <stdio.h>
#include "teclado.h"
#include "lcd.h"

/**
 *@brief Ações do teclado
 */
static inline void app_task(void)
{
    char key = keyboard_read();
    static uint8_t position = 0;

    // Se alguma tecla for pressionada, verifica qual ação tomar
    if (key != 0xFF)
    {
        if (key == 'D' | key == '#')
        {
            display_clear();
            position = 0;
            lcd_send_data(LCD_LINE_0, LCD_CMD);
        }
        else
        {
			if(position <= 30)
			{
				
				lcd_send_data(key, LCD_DATA);

				position++;

				if(position == 15)
				{
					lcd_send_data(LCD_LINE_1, LCD_CMD);
				}
			}
		}
    }
}

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;

#if defined (__MSP430FR2355__)
    PM5CTL0 &= ~LOCKLPM5;
#endif

    lcd_init_4bits();
    keyboard_init();

    while (1)
    {
        app_task();
    }
}
