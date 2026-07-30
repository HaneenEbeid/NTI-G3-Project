#include "../../MCL/STD_TYPES.h"
#include "../../MCL/BIT_MATH.h"

#include "EXTI1_config.h"
#include "EXTI1_register.h"
#include "EXTI1_interface.h"
#include "EXTI1_private.h"
#include <stdlib.h>

static void (*EXTI1_CallBack)(void) = NULL;

void EXTI1_voidInit(void)
{
	switch(SENSE)
	{
	case LOW_LEVEL:
		CLR_BIT(MCUCR , 2);
		CLR_BIT(MCUCR , 3);
		break;
	case ANY_CHANGE:
		CLR_BIT(MCUCR , 2);
		SET_BIT(MCUCR , 3);
		break;
	case FALLING_EDGE:
		SET_BIT(MCUCR , 2);
		CLR_BIT(MCUCR , 3);
		break;
	case RISING_EDGE:
		SET_BIT(MCUCR , 2);
		SET_BIT(MCUCR , 3);
		break;
	}
}


void EXTI1_voidSetSenseControl(u8 Copy_u8Sense)
{
	switch(Copy_u8Sense)
	{
	case LOW_LEVEL:
		CLR_BIT(MCUCR , 2);
		CLR_BIT(MCUCR , 3);
		break;
	case ANY_CHANGE:
		CLR_BIT(MCUCR , 2);
		SET_BIT(MCUCR , 3);
		break;
	case FALLING_EDGE:
		SET_BIT(MCUCR , 2);
		CLR_BIT(MCUCR , 3);
		break;
	case RISING_EDGE:
		SET_BIT(MCUCR , 2);
		SET_BIT(MCUCR , 3);
		break;
	}
}

void EXTI1_voidEnable(void)
{
	SET_BIT(GICR , 7);
}

void EXTI1_voidDisable(void)
{
	CLR_BIT(GICR , 7);
}


void EXTI1_voidSetCallBack(void (*Copy_pFun)(void)) {
    if (Copy_pFun != NULL) {
        EXTI1_CallBack = Copy_pFun;
    }
}


void __vector_2(void) __attribute__((signal));
void __vector_2(void) {
    /* Check if the pointer is not NULL before calling to avoid crashing */
    if (EXTI1_CallBack != NULL) {
        EXTI1_CallBack();
    }
}


