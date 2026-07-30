/*
 * EXTI1_register.h
 *
 *  Created on: Oct 1, 2024
 *      Author: elwady
 */

#ifndef EXTI1_REGISTER_H_
#define EXTI1_REGISTER_H_

#define MCUCR 		*(volatile u8*)(0x55)
#define MCUCSR 		*(volatile u8*)(0x54)
#define GICR 		*(volatile u8*)(0x5B)
#define GIFR 		*(volatile u8*)(0x5A)


#endif /* EXTI1_REGISTER_H_ */
