#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "util/delay.h"


#include "DIO_interface.h"
#include "KPD_config.h"
#include "KPD_interface.h"
#include "KPD_private.h"


u8 Local_au8Shape[KPD_ROWS_NUMBER][KPD_COLS_NUMBER] = KPD_SHAPE;
u8 Local_au8Rows[KPD_ROWS_NUMBER] = {KPD_R1_PIN,KPD_R2_PIN,KPD_R3_PIN,KPD_R4_PIN};
u8 Local_au8Cols[KPD_COLS_NUMBER] = {KPD_C1_PIN,KPD_C2_PIN,KPD_C3_PIN,KPD_C4_PIN};





void KPD_voidInit(void)
{
	for(u8 i=0 ; i<KPD_ROWS_NUMBER ; i++)
	{
		DIO_voidSetPinDirection(KPD_PORT , Local_au8Rows[i] , DIO_u8INPUT);
		DIO_voidSetPinValue(KPD_PORT , Local_au8Rows[i] , DIO_u8HIGH);
	}
	for(u8 j=0 ; j<KPD_COLS_NUMBER ; j++)
	{
		DIO_voidSetPinDirection(KPD_PORT , Local_au8Cols[j] , DIO_u8OUTPUT);
		DIO_voidSetPinValue(KPD_PORT , Local_au8Cols[j] , DIO_u8HIGH);
	}
//	DIO_voidSetPortDirection(KPD_PORT , 0x0f);
//	DIO_voidSetPortValue(KPD_PORT , 0xff);
}


u8 KPD_u8GetPressedKey(void)
{
	u8 Local_u8BreakFlag = 0;
	u8 Local_u8PressedKey= NOT_PRESSED;

    for (u8 col=0 ; col< KPD_COLS_NUMBER; col++)
    {
        DIO_voidSetPinValue(KPD_PORT , Local_au8Cols[col] , DIO_u8LOW);

        for (u8 row=0 ; row<KPD_ROWS_NUMBER ; row++)
        {
            if (DIO_u8GetPinValue(KPD_PORT , Local_au8Rows[row]) == DIO_u8LOW)
            {
            	_delay_ms(50);
            	while(DIO_u8GetPinValue(KPD_PORT , Local_au8Rows[row]) == DIO_u8LOW)
            	{
            		DIO_u8GetPinValue(KPD_PORT , Local_au8Rows[row]);
            	}
            	Local_u8PressedKey = Local_au8Shape[row][col];
            	Local_u8BreakFlag = 1;
            	break;
            }
        }
        DIO_voidSetPinValue(KPD_PORT,Local_au8Cols[col],DIO_u8HIGH);
        if(Local_u8BreakFlag) break;
    }
    return Local_u8PressedKey;
}

//KPD Assignment
u8 KPD_u8GetPressedKey3x3(void)
{
	u8 Local_u8PressedKey = NOT_PRESSED;
	u8 Local_KeyArr[3][3]={
							{3,2,1},
							{9,8,7},
							{6,5,4},
						   };
	for(u8 col=0 ; col<3 ; col++)
	{
		DIO_voidSetPinValue(KPD_PORT , col , DIO_u8LOW);

		for(u8 row=0 ; row<3 ; row++)
		{
			if(DIO_u8GetPinValue(KPD_PORT , row+4) == DIO_u8LOW)
			{
				Local_u8PressedKey = Local_KeyArr[row][col];
				_delay_ms(2);

				while(DIO_u8GetPinValue(KPD_PORT , row+4) == DIO_u8LOW)
				{
					asm("NOP");
				}
			}
		}
		DIO_voidSetPinValue(KPD_PORT , col , DIO_u8HIGH);
	}
	return Local_u8PressedKey;
}

