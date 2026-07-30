
#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

void DIO_voidSetPinDirection(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Direction);
void DIO_voidSetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Value);
u8 	 DIO_u8GetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin);

void DIO_voidSetPortDirection(u8 Copy_u8Port, u8 Copy_u8Direction);
void DIO_voidSetPortValue(u8 Copy_u8Port, u8 Copy_u8Value);
u8 	 DIO_u8GetPortValue(u8 Copy_u8Port);


#define DIO_u8INPUT			0
#define DIO_u8OUTPUT		1

#define DIO_u8PORTINPUT			0x00
#define DIO_u8PORTOUTPUT		0xff

#define DIO_u8PORTA			0
#define DIO_u8PORTB			1
#define DIO_u8PORTC			2
#define DIO_u8PORTD			3

#define DIO_u8LOW           0
#define DIO_u8HIGH          1

#define DIO_u8PIN0          0
#define DIO_u8PIN1          1
#define DIO_u8PIN2          2
#define DIO_u8PIN3          3
#define DIO_u8PIN4          4
#define DIO_u8PIN5          5
#define DIO_u8PIN6          6
#define DIO_u8PIN7          7



#endif /* DIO_INTERFACE_H_ */
