/*
 * KPD_interface.h
 *
 *  Created on: Sep 20, 2024
 *      Author: elwady
 */

#ifndef KPD_INTERFACE_H_
#define KPD_INTERFACE_H_

u8   KPD_u8GetPressedKey(void);
void KPD_voidInit(void);
u8 KPD_u8GetPressedKey3x3(void);

#define NOT_PRESSED		99
#define CLR_SCREAN		'C'

#endif /* KPD_INTERFACE_H_ */
