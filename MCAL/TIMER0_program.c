#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "TIMER0_config.h"
#include "TIMER0_interface.h"
#include "TIMER0_private.h"
#include "TIMER0_register.h"

void (*TIMER0_CallBackFn)(void);

void TIMER0_voidInit(void)
{
	//Select the timer mode
#if (TIMER0_MODE == NORMAL_MODE)
	CLR_BIT(TCCR0 , 3);
	CLR_BIT(TCCR0 , 6);
#elif (TIMER0_MODE == PHASE_PWM_MODE)
	CLR_BIT(TCCR0 , 3);
	SET_BIT(TCCR0 , 6);
#elif (TIMER0_MODE == CTC_MODE)
	SET_BIT(TCCR0 , 3);
	CLR_BIT(TCCR0 , 6);
#elif (TIMER0_MODE == FAST_MODE)
	SET_BIT(TCCR0 , 3);
	SET_BIT(TCCR0 , 6);
#endif

#if(COM0_MODE == Disconnected)
	{
		TCCR0 &= 0b11001111;
	}
#elif(COM0_MODE == Reserved)
	{
		TCCR0 &= 0b11001111;
	}
#elif(COM0_MODE == Clear_On_COM)
	{
		TCCR0 &= 0b11001111;
		TCCR0 |= Clear_COM0_Bits;
	}
#elif(COM0_MODE == Set_On_COM)
	{
		TCCR0 &= 0b11001111;
		TCCR0 |= Set_COM1A_Bits;
	}
#endif
	//Select the prescaler
	TCCR0 &=0b11111000;
	TCCR0 |= PRESCALER;


	//Interrupt enable
#if (TIMER0_MODE == NORMAL_MODE)
	SET_BIT(TIMSK , 0);
#elif (TIMER0_MODE == CTC_MODE)
	SET_BIT(TIMSK , 1);
#endif

}


void TIMER0_voidSetCompareValue(u8 Copy_u8CompareValue)
{
	OCR0 = Copy_u8CompareValue;
}

void TIMER0_voidSetCallBack(void (*Copy_pvCallBackFn)(void))
{
	TIMER0_CallBackFn = Copy_pvCallBackFn;
}

void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{
	TIMER0_CallBackFn();
}
