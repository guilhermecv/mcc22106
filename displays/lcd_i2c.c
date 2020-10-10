/*
 * lcd_i2c.c
 *
 *  Created on: 5 de out de 2020
 *      Author: Guilherme
 *
 *      Adaptado de lcd.c (https://github.com/xtarke/msplibs/blob/master/displays/lcd.c)
 *      Author: Renan Augusto Starke
 */
#include <msp430.h>
#include <stdio.h>
#include "lib/i2c_master_fr2355.h"
#include "lcd_i2c.h"

/* Pino do backlight no PCF8574 */
#define BL                   0x08

volatile uint8_t backlight = 0;

/**
 * @brief Envia um dado estático para o display: caractere ou comando.
 * @param data: valor do comando.
 * @param data_type: LCD_CMD para comando. LCD_DATA para caractere.
 *
 * @retval Nenhum
 */
void lcd_send_data(uint8_t data, lcd_data_t data_type)
{
    /**
     TODO:
        Otimizar a função
        Melhorar o controle do backlight
     */
    if (data_type == LCD_DATA)
    {
        if (backlight)
        {
            i2c_write_single_byte(LCD_ADDR, (0xF0 & data) | 0x0D | BL);
            __delay_cycles(24000);
            i2c_write_single_byte(LCD_ADDR, (0xF0 & data) | 0x09 | BL);
            __delay_cycles(24000);
            /* segunda parte dos dados */
            i2c_write_single_byte(LCD_ADDR, (0xF0 & (data << 4)) | 0x0D | BL);
            __delay_cycles(24000);
            i2c_write_single_byte(LCD_ADDR, (0xF0 & (data << 4)) | 0x09 | BL);
            __delay_cycles(24000);
        }
        else
        {
            i2c_write_single_byte(LCD_ADDR, ((0xF0 & data) | 0x0D)&~BL);
            __delay_cycles(24000);
            i2c_write_single_byte(LCD_ADDR, ((0xF0 & data) | 0x09)&~BL);
            __delay_cycles(24000);
            /* segunda parte dos dados */
            i2c_write_single_byte(LCD_ADDR, ((0xF0 & (data << 4)) | 0x0D)&~BL);
            __delay_cycles(24000);
            i2c_write_single_byte(LCD_ADDR, ((0xF0 & (data << 4)) | 0x09)&~BL);
            __delay_cycles(24000);
        }
    }
    else
    {
        if(backlight)
        {
            i2c_write_single_byte(LCD_ADDR, (0xF0 & data) | 0x04 | BL);
            __delay_cycles(24000);
            i2c_write_single_byte(LCD_ADDR, (0xF0 & data) | 0x00 | BL);
            __delay_cycles(24000);
            /* segunda parte do comando */
            i2c_write_single_byte(LCD_ADDR, (0xF0 & (data << 4)) | 0x04 | BL);
            __delay_cycles(24000);
            i2c_write_single_byte(LCD_ADDR, (0xF0 & (data << 4)) | 0x00 | BL);
            __delay_cycles(24000);
        }
        else
        {
            i2c_write_single_byte(LCD_ADDR, ((0xF0 & data) | 0x04)&~BL);
            __delay_cycles(24000);
            i2c_write_single_byte(LCD_ADDR, ((0xF0 & data) | 0x00)&~BL);
            __delay_cycles(24000);
            /* segunda parte do comando */
            i2c_write_single_byte(LCD_ADDR, ((0xF0 & (data << 4)) | 0x04)&~BL);
            __delay_cycles(24000);
            i2c_write_single_byte(LCD_ADDR, ((0xF0 & (data << 4)) | 0x00)&~BL);
            __delay_cycles(24000);
        }

    }
}

void lcd_i2c_init()
{
    init_i2c_master_mode();

    lcd_send_data(0x30, LCD_CMD);
    __delay_cycles(98400);
    lcd_send_data(0x30, LCD_CMD);
    __delay_cycles(2400);
    lcd_send_data(0x30, LCD_CMD);

    __delay_cycles(98400);  // 4,1 ms
    i2c_write_single_byte(LCD_ADDR, (0x20 | 0x04)); // 0x20 + Enable
    __delay_cycles(24000);  // 1 ms
    i2c_write_single_byte(LCD_ADDR, 0x20);
    __delay_cycles(24000);

    /* Interface de 4 bits 2 linhas
     * Mudar comando para displays maiores */
    lcd_send_data(0x28, LCD_CMD);
    lcd_send_data(LCD_TURN_OFF, LCD_CMD);
    lcd_send_data(LCD_CLEAR, LCD_CMD);

#ifdef BLINKING_CURSOR_ON
    /* cursor piscante */
    lcd_send_data(0x0F, LCD_CMD);
#else
    /* Mensagem aparente e cursor inativo não piscante
     * Outros modos podem ser consultados no datasheet */
    lcd_send_data(0x0C, LCD_CMD);
#endif

    lcd_send_data(LCD_LINE_0, LCD_CMD);
}

/**
 TODO:
    Possibilitar a escolha da posição de escrita no display
 */

/**
 * @brief Escreve um string estática no LCD.
 * @param c: ponteiro para a string em RAM
 *
 * @retval Nenhum
 */
void lcd_write_string(const char *c)
{
    for (; *c != '\0'; c++)
        lcd_send_data(*c, LCD_DATA);
}

/**
 * @brief  Escreve um caractere no display
 * @param  c: caractere
 * @retval None
 */
void lcd_write_char(const char c)
{
    lcd_send_data(c, LCD_DATA);
}

/**
 * @brief  Limpa o display e retorna o cursor para a posição inicial
 * @param  None
 * @retval None
 */
void lcd_clear(void)
{
    lcd_send_data(LCD_CLEAR, LCD_CMD);
}

/**
 * @brief
 * @param
 * @retval None
 */
void lcd_set_line(lcd_line_t line)
{
    lcd_send_data(line, LCD_CMD);
}


/**
    TODO:
        Validar a função testando no display
        Remover lcd_set_line()
*/

/**
 * @brief  Define a posição de escrita do display
 * @param  col: coluna do display
 * @param  row: linha do display
 *
 * @retval none
 */
void lcd_set_cursor(uint8_t col, uint8_t row)
{
    uint8_t row_offset[] = {0x00, 0x40};

    /* ref: https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library */
    lcd_send_data(0x80 | (col + row_offsets[row]), LCD_CMD);
}

/**
 * @brief  Escreve um número inteiro no display
 * @param  num: valor numérico
 * @retval None
 */
void lcd_write_uint(uint16_t num)
{
    char str[6];
    sprintf(str, "%d", num);
    lcd_write_string(str);
}

/**
 * @brief  Ativa ou desativa o backlight
 * @param  bl: 0 para desativar, >0 para ativar
 * @retval none
 */
void lcd_set_backlight(uint8_t bl)
{
    if(bl)
        backlight = 1;
    else
        backlight = 0;
}
