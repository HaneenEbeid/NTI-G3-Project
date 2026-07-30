/*
 * ADC_interface.h
 *
 *  Created on: Oct 4, 2024
 *      Author: elwady
 */

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

void ADC_voidInit(void);
u16 ADC_u16ReadChannel(u8 Copy_u8ChannelNumber);
u8 ADC_u8GetHumidity(void);
u16 ADC_u16GetGas(void);
u8 ADC_u8GetTemperature(void);
u8 ADC_u8GetLDR(void);

#endif /* ADC_INTERFACE_H_ */
