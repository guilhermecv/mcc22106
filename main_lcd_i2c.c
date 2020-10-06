/*
 * main.c
 *
 *  Exemplo de uso do display LCD 16x2
 *
 *  Created on: 5 de out de 2020
 *      Author: Guilherme
 */
#include <msp430.h>
#include "lib/clock_system.h"
#include "displays/lcd_i2c.h"
#include "wdt_delay/wdt_delay.h"


int main(void)
{
    uint16_t i = 0;
    uint8_t counter = 0;
    uint8_t backlight = 0;

    WDTCTL = WDTPW | WDTHOLD;
    PM5CTL0 &= ~LOCKLPM5;

    init_clock_system();
    config_wd_as_timer();

    __bis_SR_register(GIE);

    lcd_i2c_init();
    lcd_set_backlight(1);

    lcd_write_string("mcc22106");
    lcd_set_line(LCD_LINE_1);
    lcd_write_string("IFSC 2020/1");

    delay_wdt(2000);

    lcd_clear();
    lcd_set_line(LCD_LINE_0);
    lcd_write_string("mcc22106 2020/1");

    for (;;)
    {
        lcd_set_line(LCD_LINE_1);
        lcd_write_uint(i++);

        delay_wdt(100);

        if(counter++ == 5)
        {
            counter = 0;
            backlight = !backlight;
            lcd_set_backlight(backlight);
        }

    }

}
