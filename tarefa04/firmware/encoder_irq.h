/*
 * encoder_irq.h
 *
 *  Created on: 27 de abr de 2020
 *      Author: Guilherme
 */

#ifndef ENCODER_IRQ_H_
#define ENCODER_IRQ_H_

/* O encoder utiliza o port 2 */
#define ENCODER         BIT0

void encoder_init(void);

#endif /* ENCODER_IRQ_H_ */
