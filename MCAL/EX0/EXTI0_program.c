#include "../../MCL/STD_TYPES.h"
#include "../../MCL/BIT_MATH.h"

#include "EXTI0_config.h"
#include "EXTI0_interface.h"
#include "EXTI0_private.h"
#include "EXTI0_register.h"

#include <stdlib.h>

static void (*EXTI0_CallBack)(void) = NULL;

void EXTI0_voidInit(void)
{
	switch(SENSE)
	{
	case LOW_LEVEL:
		CLR_BIT(MCUCR , 0);
		CLR_BIT(MCUCR , 1);
		break;
	case ANY_CHANGE:
		SET_BIT(MCUCR , 0);
		CLR_BIT(MCUCR , 1);
		break;
	case FALLING_EDGE:
		CLR_BIT(MCUCR , 0);
		SET_BIT(MCUCR , 1);
		break;
	case RISING_EDGE:
		SET_BIT(MCUCR , 0);
		SET_BIT(MCUCR , 1);
		break;
	}
}



void EXTI0_voidSetSenseControl(u8 Copy_u8Sense)
{
	switch(Copy_u8Sense)
	{
	case LOW_LEVEL:
		CLR_BIT(MCUCR , 0);
		CLR_BIT(MCUCR , 1);
		break;
	case ANY_CHANGE:
		SET_BIT(MCUCR , 0);
		CLR_BIT(MCUCR , 1);
		break;
	case FALLING_EDGE:
		CLR_BIT(MCUCR , 0);
		SET_BIT(MCUCR , 1);
		break;
	case RISING_EDGE:
		SET_BIT(MCUCR , 0);
		SET_BIT(MCUCR , 1);
		break;
	}

}


void EXTI0_voidEnable(void)
{
	SET_BIT(GICR , 6);
}



void EXTI0_voidDisable(void)
{
	CLR_BIT(GICR , 6);
}

void EXTI0_voidSetCallBack(void (*Copy_pFun)(void)) {
	if (Copy_pFun != NULL) {
		EXTI0_CallBack = Copy_pFun;
	}
}

void __vector_1(void) __attribute__((signal));
void __vector_1(void) {
	/* Check if the pointer is not NULL before calling to avoid crashing */
	EXTI0_CallBack();

}


