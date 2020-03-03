/*
 * bit_utils.h
 *
 *  Created on: 21 de fev de 2020
 *      Author: Guilherme
 */

#ifndef BIT_UTILS_H_
#define BIT_UTILS_H_


#define set_bit(x,y)    (x |= y)
#define clr_bit(x,y)    (x &=~y)
#define cpl_bit(x,y)    (x ^= y)
#define tst_bit(x,y)    (x & y)

#define wait_until_bit_is_set(x,y)  do; while(x & y);

#endif /* BIT_UTILS_H_ */
