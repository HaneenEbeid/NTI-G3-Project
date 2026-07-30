
#include "../../MCL/STD_TYPES.h"
#include "../../MCL/BIT_MATH.h"

#include "ADC_config.h"
#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_register.h"

void ADC_voidInit(void)
{
	//select votage efrence
	#if(REFRENCE_VOLTAGE == AREF)
		CLR_BIT(ADMUX , 7);
		CLR_BIT(ADMUX , 6);
	#elif (REFRENCE_VOLTAGE == AVCC)
		CLR_BIT(ADMUX , 7);
		SET_BIT(ADMUX , 6);
	#elif(REFRENCE_VOLTAGE == INTERNAL_VOLTAGE)
		SET_BIT(ADMUX , 7);
		SET_BIT(ADMUX , 6);
	#endif


	//select prescaler
	CLR_BIT(ADCSRA , 2);
	CLR_BIT(ADCSRA , 1);
	CLR_BIT(ADCSRA , 0);

	//enable ADC
	SET_BIT(ADCSRA , 7);
}


u16 ADC_u16ReadChannel(u8 Copy_u8ChannelNumber)
{
	//Select Channel
	ADMUX &= 0b11100000;
	ADMUX |= Copy_u8ChannelNumber;

	//Start Conversion
	SET_BIT(ADCSRA , 6);

	//Polling
	while((GET_BIT(ADCSRA , 4)) != 1)
	{
		asm("NOP");
	}

	//Clear the Flag
	SET_BIT(ADCSRA , 4);

	//Return Reading
	return ADC;
}

/* ========================================================================= */
/*                       Sensor Mapping Functions                            */
/* ========================================================================= */

/* Note: ADC resolution is 10-bit, so max value is 1023 */
#define ADC_MAX_VALUE  1023UL

/*
 * Function to read Ambient Light (LDR) from Channel 0
 * Maps ADC value (0-1023) to Percentage (0-100%)
 */

u8 ADC_u8GetLDR(void) {
    u16 Local_u16ADCValue = ADC_u16ReadChannel(0);

    /* Calculate mapped value: (ADC * 100) / 1023 */
    u8 Local_u8MappedValue = (u8)(((u32)Local_u16ADCValue * 100) / ADC_MAX_VALUE);

    return Local_u8MappedValue;
}

/*
 * Function to read Room Temperature from Channel 1
 * Maps ADC value (0-1023) to Temperature (0-50 C)
 */

u8 ADC_u8GetTemperature(void) {
    u16 Local_u16ADCValue = ADC_u16ReadChannel(1);

    /* Calculate mapped value: (ADC * 50) / 1023 */
    u8 Local_u8MappedValue = (u8)(((u32)Local_u16ADCValue * 100) / ADC_MAX_VALUE);

    return Local_u8MappedValue;
}

/*
 * Function to read Gas Sensor (MQ-2) from Channel 2
 * Maps ADC value (0-1023) to ppm (0-1000 ppm)
 * Note: Return type is u16 because max value (1000) exceeds u8 max (255)
 */

u16 ADC_u16GetGas(void) {
    u16 Local_u16ADCValue = ADC_u16ReadChannel(2);

    /* Calculate mapped value: (ADC * 1000) / 1023 */
    u16 Local_u16MappedValue = (u16)(((u32)Local_u16ADCValue * 1000) / ADC_MAX_VALUE);

    return Local_u16MappedValue;
}

/*
 * Function to read Humidity from Channel 3
 * Maps ADC value (0-1023) to Percentage (0-100%)
 */
u8 ADC_u8GetHumidity(void) {
    u16 Local_u16ADCValue = ADC_u16ReadChannel(3);

    /* Calculate mapped value: (ADC * 100) / 1023 */
    u8 Local_u8MappedValue = (u8)(((u32)Local_u16ADCValue * 100) / ADC_MAX_VALUE);

    return Local_u8MappedValue;
}

