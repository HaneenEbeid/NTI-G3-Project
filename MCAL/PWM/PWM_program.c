/*
 * TIMER1_program.c
 *
 *  Created on: Oct 12, 2024
 *      Author: elwady
 */
#include "../../MCL/STD_TYPES.h"
#include "../../MCL/BIT_MATH.h"

#include "PWM_config.h"
#include "PWM_interface.h"
#include "PWM_private.h"
#include "PWM_register.h"
void (*PWM_CallBackFun)(void);

void PWM_voidInit(void)
{
	//Set mode "fast PWM"
#if(MODE == Fast_PWM)
	{
		CLR_BIT(TCCR1A , 0);
		SET_BIT(TCCR1A , 1);
		SET_BIT(TCCR1B , 3);
		SET_BIT(TCCR1B , 4);
	}
#elif(MODE == Phase_Correct)
	{
		SET_BIT(TCCR1A , 0);
		SET_BIT(TCCR1A , 1);
		CLR_BIT(TCCR1B , 3);
		SET_BIT(TCCR1B , 4);
	}
#elif(MODE == CTC_Mode)
	{
		CLR_BIT(TCCR1A , 0);
		CLR_BIT(TCCR1A , 1);
		SET_BIT(TCCR1B , 3);
		SET_BIT(TCCR1B , 4);
	}
#elif(MODE == Normal_Mode)
	{
		CLR_BIT(TCCR1A , 0);
		CLR_BIT(TCCR1A , 1);
		CLR_BIT(TCCR1B , 3);
		CLR_BIT(TCCR1B , 4);
		TCNT1 = 0;
	}
#endif

	//set Compare output mode "1A"
#if(COM1A_MODE == Disconnected)
	{
		TCCR1A &= 0b00111111;
	}
#elif(COM1A_MODE == Toggle_On_COM)
	{
		TCCR1A &= 0b00111111;
		TCCR1A |= Toggle_COM1A_Bits;
	}
#elif(COM1A_MODE == Clear_On_COM)
	{
		TCCR1A &= 0b00111111;
		TCCR1A |= Clear_COM1A_Bits;
	}
#elif(COM1A_MODE == Set_On_COM)
	{
		TCCR1A &= 0b00111111;
		TCCR1A |= Set_COM1A_Bits;
	}
#endif

	//set Compare output mode "1B"
#if(COM1B_MODE == Disconnected)
	{
		TCCR1A &= 0b11001111;
	}
#elif(COM1B_MODE == Toggle_On_COM)
	{
		TCCR1A &= 0b11001111;
		TCCR1A |= Toggle_COM1B_Bits;
	}
#elif(COM1B_MODE == Clear_On_COM)
	{
		TCCR1A &= 0b11001111;
		TCCR1A |= Clear_COM1B_Bits;
	}
#elif(COM1B_MODE == Set_On_COM)
	{
		TCCR1A &= 0b11001111;
		TCCR1A |= Set_COM1B_Bits;
	}
#endif

	//Set Prescaler
	TCCR1B &= 0b11111000;
	TCCR1B |= PRESCALER;

}


void PWM_voidSetTopValue(u16 Copy_u16TopValue)
{
	ICR1 = Copy_u16TopValue;
}


void PWM_voidSetCompareValue(u16 Copy_u16COM1A_Value , u16 Copy_u16COM1B_Value)
{
	if(COM1B_MODE != Disconnected)
		{
		OCR1B = Copy_u16COM1B_Value;
		}
	if(COM1A_MODE != Disconnected)
		{
		OCR1A = Copy_u16COM1A_Value;
		}
}

void PWM_voidCallBackFunction(void (*Copy_pvCallBackFn)(void))
{
	PWM_CallBackFun = Copy_pvCallBackFn;
	SET_BIT(TIMSK , 3);
	SET_BIT(TIMSK , 4);
}

void __vector_8(void) __attribute__((signal));
void __vector_8(void)
{
	PWM_CallBackFun();
}

void __vector_9(void) __attribute__((signal));
void __vector_9(void)
{
	PWM_CallBackFun();
}

void PWM_voidDelaySecond(u16 Copy_u16Sec)
{
	u16 Count_Per_Sec = 7813;
	u16 overflow_counter = 0;

	while(Copy_u16Sec > 0)
	{
		TCNT1 = 0;

		while (TCNT1 < Count_Per_Sec);

		 overflow_counter++;  // Count how many times we waited

		if (overflow_counter == 1)  // 1 second passed
		{
			Copy_u16Sec--;  // Decrement the seconds remaining
			overflow_counter = 0;  // Reset overflow counter for the next second
		}

	}
}
















