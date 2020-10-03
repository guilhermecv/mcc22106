/*
 * adc.h
 *
 *  Created on: 2 de out de 2020
 *      Author: Guilherme
 */
#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

/* Considerando ADC de 12 bits */
//#define CELL_MIN_VOLTAGE            2556        /* 3,1V como tensão mínima */
//#define CELL_MAX_VOLTAGE            3475        /* 4,2V como tensão máxima */

/* Considerando ADC de 10 bits */
#define CELL_MIN_VOLTAGE            639
#define CELL_MAX_VOLTAGE            868


typedef struct battery_voltage
{
    uint16_t cell_0;
    uint16_t cell_1;
}battery_voltage_t;


void adc_init(battery_voltage_t *battery_voltage);

#endif /* ADC_H_ */
