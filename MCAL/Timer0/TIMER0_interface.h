/*
 * TIMER0_interface.h
 *
 *  Created on: Oct 11, 2024
 *      Author: elwady
 */

#ifndef TIMER0_INTERFACE_H_
#define TIMER0_INTERFACE_H_

void TIMER0_voidInit(void);
void TIMER0_voidSetCompareValue(u8 Copy_u8CompareValue);
void TIMER0_voidSetCallBack(void (*Copy_pvCallBackFn)(void));

#define CTC_MODE			3
#define NORMAL_MODE			1
#define PHASE_PWM_MODE		2
#define FAST_MODE			4

#define Disconnected				1
#define Reserved               2
#define Clear_On_COM                3
#define Set_On_COM                  4

#define Clear_COM0_Bits					0b00100000
#define Set_COM0_Bits					0b00110000

#define DIVISION_BY_8		0b00000010

#endif /* TIMER0_INTERFACE_H_ */
