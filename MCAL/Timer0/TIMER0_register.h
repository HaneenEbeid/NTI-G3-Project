/*
 * TIMER0_register.h
 *
 *  Created on: Oct 11, 2024
 *      Author: elwady
 */

#ifndef TIMER0_REGISTER_H_
#define TIMER0_REGISTER_H_

#define TCCR0				*((volatile u8*)(0X53))
#define TCNT0				*((volatile u8*)(0x52))
#define OCR0                *((volatile u8*)(0x5C))
#define TIFR                *((volatile u8*)(0x58))
#define TIMSK               *((volatile u8*)(0x59))

#endif /* TIMER0_REGISTER_H_ */
