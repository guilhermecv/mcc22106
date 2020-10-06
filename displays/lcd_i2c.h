/*
 * lcd_i2c.h
 *
 *  Created on: 5 de out de 2020
 *      Author: Guilherme
 *
 *      Adaptado de lcd.c (https://github.com/xtarke/msplibs/blob/master/displays/lcd.c)
 *      Author: Renan Augusto Starke
 */
#ifndef LCD_I2C_H_
#define LCD_I2C_H_

#include <stdint.h>

#define LCD_ADDR                0x27

//#define BLINKING_CURSOR_ON


#define LCD_TURN_OFF            0x08
#define LCD_CLEAR               0x01

typedef enum
{
    LCD_LINE_0 = 0x80,
    LCD_LINE_1 = 0xC0
} lcd_line_t;

typedef enum
{
    LCD_CMD, LCD_DATA
} lcd_data_t;


void lcd_i2c_init();

void lcd_write_char(const char c);

void lcd_write_string(const char *c);

void lcd_write_uint(uint16_t num);

void lcd_clear(void);

void lcd_set_line(lcd_line_t line);

void lcd_set_backlight(uint8_t bl);


#endif /* LCD_I2C_H_ */
