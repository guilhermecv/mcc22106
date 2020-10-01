/*
 * ultrassonic.h
 *
 *  Created on: 28 de ago de 2020
 *      Author: Guilherme
 */

#ifndef ULTRASSONIC_H_
#define ULTRASSONIC_H_

#include <stdint.h>

#define TRIGGER                 BIT2
#define ECHO                    BIT0
#define ULTRASSONIC_PORT        P2

void ultrassonic_init(void);

uint32_t get_distance(void);

#endif /* ULTRASSONIC_H_ */
