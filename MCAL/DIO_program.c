#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "DIO_register.h"

void DIO_voidSetPinDirection(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Direction)
{
	if(Copy_u8Direction == DIO_u8INPUT)
	{
		switch(Copy_u8Port)
		{
		case DIO_u8PORTA : CLR_BIT(DDRA , Copy_u8Pin); break; 
		case DIO_u8PORTB : CLR_BIT(DDRB , Copy_u8Pin); break;
		case DIO_u8PORTC : CLR_BIT(DDRC , Copy_u8Pin); break;
		case DIO_u8PORTD : CLR_BIT(DDRD , Copy_u8Pin); break;
		}
	}
	else if(Copy_u8Direction == DIO_u8OUTPUT)
	{
		switch(Copy_u8Port)
		{
		case DIO_u8PORTA : SET_BIT(DDRA , Copy_u8Pin); break;
		case DIO_u8PORTB : SET_BIT(DDRB , Copy_u8Pin); break;
		case DIO_u8PORTC : SET_BIT(DDRC , Copy_u8Pin); break;
		case DIO_u8PORTD : SET_BIT(DDRD , Copy_u8Pin); break;
		}
	}
}

void DIO_voidSetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Value)
{
	if (Copy_u8Value == DIO_u8LOW)
	{
		switch (Copy_u8Port)
		{
		case DIO_u8PORTA : CLR_BIT(PORTA , Copy_u8Pin); break; 
		case DIO_u8PORTB : CLR_BIT(PORTB , Copy_u8Pin); break;
		case DIO_u8PORTC : CLR_BIT(PORTC , Copy_u8Pin); break;
		case DIO_u8PORTD : CLR_BIT(PORTD , Copy_u8Pin); break;
		}
	}
	else if (Copy_u8Value == DIO_u8HIGH)
	{				
		switch (Copy_u8Port)
		{
		case DIO_u8PORTA : SET_BIT(PORTA , Copy_u8Pin); break; 
		case DIO_u8PORTB : SET_BIT(PORTB , Copy_u8Pin); break;
		case DIO_u8PORTC : SET_BIT(PORTC , Copy_u8Pin); break;
		case DIO_u8PORTD : SET_BIT(PORTD , Copy_u8Pin); break;
		}
	}	
}

u8 	 DIO_u8GetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin)
{
	u8 pin_value=0;
	switch (Copy_u8Port)
	{
	case DIO_u8PORTA : pin_value = GET_BIT(PINA , Copy_u8Pin); break;
	case DIO_u8PORTB : pin_value = GET_BIT(PINB , Copy_u8Pin); break;
	case DIO_u8PORTC : pin_value = GET_BIT(PINC , Copy_u8Pin); break;
	case DIO_u8PORTD : pin_value = GET_BIT(PIND , Copy_u8Pin); break;
	}
	return pin_value;
}

void DIO_voidSetPortDirection(u8 Copy_u8Port, u8 Copy_u8Direction)
{
	switch(Copy_u8Port)
	{
	case DIO_u8PORTA : DDRA = Copy_u8Direction; break;
	case DIO_u8PORTB : DDRB = Copy_u8Direction; break;
	case DIO_u8PORTC : DDRC = Copy_u8Direction; break;
	case DIO_u8PORTD : DDRD = Copy_u8Direction; break;
	}
}

void DIO_voidSetPortValue(u8 Copy_u8Port, u8 Copy_u8Value)
{
	switch(Copy_u8Port)
	{
	case DIO_u8PORTA : PORTA = Copy_u8Value; break;
	case DIO_u8PORTB : PORTB = Copy_u8Value; break;
	case DIO_u8PORTC : PORTC = Copy_u8Value; break;
	case DIO_u8PORTD : PORTD = Copy_u8Value; break;
	}
}

u8 	 DIO_u8GetPortValue(u8 Copy_u8Port)
{
	u8 port_value;
	switch(Copy_u8Port)
	{
	case DIO_u8PORTA : port_value = PORTA; break;
	case DIO_u8PORTB : port_value = PORTB; break;
	case DIO_u8PORTC : port_value = PORTC; break;
	case DIO_u8PORTD : port_value = PORTD; break;
	}
	return port_value;
}

