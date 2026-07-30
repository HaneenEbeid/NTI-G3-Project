/*
 * LCD_interface.h
 *
 *  Created on: Jul 30, 2026
 *      Author: elwady
 */

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_


/* LCD PCF8574 I2C Slave Address (Typically 0x27 or 0x4E) */
#define LCD_I2C_ADDRESS     0x40

/* Basic LCD Commands */
#define LCD_CLEAR_DISPLAY   0x01
#define LCD_RETURN_HOME     0x02

/* ------------------------------------------------------------------------- */
/*                             Core LCD Functions                            */
/* ------------------------------------------------------------------------- */

/* Initializes the LCD and sets I2C pins direction using DIO */
void LCD_voidInit(void);

/* Sends a command to the LCD */
void LCD_voidSendCommand(u8 Copy_u8Command);

/* Sends a single character to the LCD */
void LCD_voidSendData(u8 Copy_u8Data);

/* Sends a string to the LCD */
void LCD_voidSendString(u8* Copy_pu8String);

/* Clears the LCD display */
void LCD_voidClear(void);

/* Sets cursor position (X: 0->15, Y: 0->1) */
void LCD_voidGoToXY(u8 Copy_u8X, u8 Copy_u8Y);

/* Sends integer numbers to LCD */
void LCD_voidSendNumber(u32 Copy_u32Number);

/* ------------------------------------------------------------------------- */
/*                       Project-Specific LCD Functions                      */
/* ------------------------------------------------------------------------- */

/* Displays Idle Screen (Scene, Temp, Zones, Fan, Lock) per project specs */
void LCD_voidDisplayIdle(u8* Copy_pu8Scene, u8 Copy_u8Temp, u8* Copy_pu8ZoneStates, u8 Copy_u8FanLevel, u8 Copy_u8LockState);

/* Displays PIN entry masked with stars */
void LCD_voidDisplayPinEntry(u8 Copy_u8DigitsEntered);

/* Displays Lockout countdown */
void LCD_voidDisplayLockout(u8 Copy_u8SecondsLeft);

/* Displays Gas or Intrusion Alarm */
void LCD_voidDisplayAlarm(u8* Copy_pu8AlarmMsg);


#endif /* LCD_INTERFACE_H_ */
