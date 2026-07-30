/*
 * EXTI1_interface.h
 *
 *  Created on: Oct 1, 2024
 *      Author: elwady
 */

#ifndef EXTI1_INTERFACE_H_
#define EXTI1_INTERFACE_H_

void EXTI1_voidInit(void);
void EXTI1_voidSetSenseControl(u8 Copy_u8Sense);
void EXTI1_voidEnable(void);
void EXTI1_voidDisable(void);
void EXTI1_voidSetCallBack(void (*Copy_pFun)(void));

#define LOW_LEVEL		1
#define ANY_CHANGE		2
#define FALLING_EDGE	3
#define RISING_EDGE		4

#endif /* EXTI1_INTERFACE_H_ */
