/*
 * MCU_PIN_Headers.h
 *
 *  Created on: Jul 30, 2026
 *      Author: elwady
 */

#ifndef MCU_PIN_HEADERS_H_
#define MCU_PIN_HEADERS_H_


/* ===========================
 * PORT D
 * =========================== */
#define Hallway_Led_Port      DIO_u8PORTD
#define Hallway_Led_Pin       DIO_u8PIN7

#define Door_Sense_Port       DIO_u8PORTD
#define Door_Sense_Pin        DIO_u8PIN6

#define Motor_Port            DIO_u8PORTD
#define Motor_Pin             DIO_u8PIN5

#define PIR_Living_Port       DIO_u8PORTD
#define PIR_Living_Pin        DIO_u8PIN3

#define PIR_Hallway_Port      DIO_u8PORTD
#define PIR_Hallway_Pin       DIO_u8PIN2


/* ===========================
 * PORT C
 * =========================== */
#define Bedroom_Led_Port      DIO_u8PORTC
#define Bedroom_Led_Pin       DIO_u8PIN4

#define Buzzer_Port           DIO_u8PORTC
#define Buzzer_Pin            DIO_u8PIN3

#define Away_Led_Port         DIO_u8PORTC
#define Away_Led_Pin          DIO_u8PIN2

#define SDA_Port              DIO_u8PORTC
#define SDA_Pin               DIO_u8PIN1

#define SCL_Port              DIO_u8PORTC
#define SCL_Pin               DIO_u8PIN0


/* ===========================
 * PORT B
 * =========================== */
#define Keypad_R1_Port        DIO_u8PORTB




#define Keypad_R1_Pin         DIO_u8PIN4

#define Keypad_R2_Port        DIO_u8PORTB
#define Keypad_R2_Pin         DIO_u8PIN5

#define Keypad_R3_Port        DIO_u8PORTB
#define Keypad_R3_Pin         DIO_u8PIN6

#define Keypad_R4_Port        DIO_u8PORTB
#define Keypad_R4_Pin         DIO_u8PIN7

#define Keypad_C1_Port        DIO_u8PORTB
#define Keypad_C1_Pin         DIO_u8PIN0

#define Keypad_C2_Port        DIO_u8PORTB
#define Keypad_C2_Pin         DIO_u8PIN1

#define Keypad_C3_Port        DIO_u8PORTB
#define Keypad_C3_Pin         DIO_u8PIN2

#define Keypad_C4_Port        DIO_u8PORTB
#define Keypad_C4_Pin         DIO_u8PIN3


/* ===========================
 * PORT A
 * =========================== */
#define Door_Lock_Port        DIO_u8PORTA
#define Door_Lock_Pin         DIO_u8PIN7

#define Bathroom_Led_Port     DIO_u8PORTA
#define Bathroom_Led_Pin      DIO_u8PIN6

#define Kitchen_Led_Port      DIO_u8PORTA
#define Kitchen_Led_Pin       DIO_u8PIN5

#define Living_Led_Port       DIO_u8PORTA
#define Living_Led_Pin        DIO_u8PIN4

#define Humidity_Port         DIO_u8PORTA
#define Humidity_Pin          DIO_u8PIN3

#define Gas_Port              DIO_u8PORTA
#define Gas_Pin               DIO_u8PIN2

#define Temperature_Port      DIO_u8PORTA
#define Temperature_Pin       DIO_u8PIN1

#define LDR_Port              DIO_u8PORTA
#define LDR_Pin               DIO_u8PIN0

#endif /* MCU_PIN_HEADERS_H_ */
