/*
 * LCD_program.c
 *
 *  Created on: Jul 30, 2026
 *      Author: elwady
 */
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "util/delay.h"
#include "LCD_interface.h"
#include "I2C_LCD_interface.h" // I2C Driver built previously
#include "DIO_interface.h"  // Include your DIO driver here

/* Macros for DIO directions and values (Replace with your actual macro values if different) */
#define DIO_u8INPUT   0
#define DIO_u8OUTPUT  1
#define DIO_u8LOW     0
#define DIO_u8HIGH    1

/* External DIO Function Prototypes (As requested) */
extern void DIO_voidSetPinDirection(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Direction);
extern void DIO_voidSetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Value);

/* Helper function to send data/command via I2C to the PCF8574 expansion chip */
static void LCD_voidSendI2C(u8 Copy_u8Value, u8 Copy_u8Mode) {
    /*
     * PCF8574 mapping:
     * Bit 7-4: Data Bits (D7-D4)
     * Bit 3: Backlight (1 = ON)
     * Bit 2: Enable (E)
     * Bit 1: Read/Write (RW) -> 0 for Write
     * Bit 0: Register Select (RS) -> Mode (1 for Data, 0 for Command)
     */

    u8 Local_u8HighNibble = (Copy_u8Value & 0xF0) | (1 << 3) | (Copy_u8Mode);
    u8 Local_u8LowNibble  = ((Copy_u8Value << 4) & 0xF0) | (1 << 3) | (Copy_u8Mode);

    I2C_LCD_Start();
    I2C_LCD_Write(LCD_I2C_ADDRESS);

    /* Send High Nibble */
    I2C_LCD_Write(Local_u8HighNibble | (1 << 2)); /* Enable = 1 */
    I2C_LCD_Write(Local_u8HighNibble & ~(1 << 2)); /* Enable = 0 */

    /* Send Low Nibble */
    I2C_LCD_Write(Local_u8LowNibble | (1 << 2)); /* Enable = 1 */
    I2C_LCD_Write(Local_u8LowNibble & ~(1 << 2)); /* Enable = 0 */

    I2C_LCD_Stop();
}

void LCD_voidInit(void) {
    /* 1. Initialize I2C Pins (PC0 = SCL, PC1 = SDA) */
    /* Set pins as Input to avoid overriding I2C hardware */
    DIO_voidSetPinDirection(DIO_u8PORTC, DIO_u8PIN0, DIO_u8INPUT);
    DIO_voidSetPinDirection(DIO_u8PORTC, DIO_u8PIN1, DIO_u8INPUT);

    /* Enable internal pull-ups by writing HIGH to the PORT register */
    /* This satisfies the TWI requirement for pull-up resistors */
    DIO_voidSetPinValue(DIO_u8PORTC, DIO_u8PIN0, DIO_u8HIGH);
    DIO_voidSetPinValue(DIO_u8PORTC, DIO_u8PIN1, DIO_u8HIGH);

    /* 2. Initialize the I2C Hardware */
    I2C_LCD_Init();

    /* 3. LCD 4-bit Initialization Sequence */
    /* Wait for LCD to power up */
    u16 i; for(i = 0; i < 50000; i++);

    LCD_voidSendCommand(0x33);
    LCD_voidSendCommand(0x32); /* Set 4-bit mode */
    LCD_voidSendCommand(0x28); /* 2 Lines, 5x8 Matrix */
    LCD_voidSendCommand(0x0C); /* Display OFF */
    LCD_voidSendCommand(0x01); /* Clear Display */
    LCD_voidSendCommand(0x06); /* Shift Cursor Right */
    LCD_voidSendCommand(0x0C); /* Display ON, Cursor OFF */
}

void LCD_voidSendCommand(u8 Copy_u8Command) {
    /* Send with RS = 0 */
    LCD_voidSendI2C(Copy_u8Command, 0);
    _delay_ms(2);
}

void LCD_voidSendData(u8 Copy_u8Data) {
    /* Send with RS = 1 */
    LCD_voidSendI2C(Copy_u8Data, 1);
    _delay_ms(1);
}

void LCD_voidSendString(u8* Copy_pu8String) {
    u8 i = 0;
    while (Copy_pu8String[i] != '\0') {
        LCD_voidSendData(Copy_pu8String[i]);
        i++;
    }
}

void LCD_voidClear(void) {
    LCD_voidSendCommand(LCD_CLEAR_DISPLAY);
}

void LCD_voidGoToXY(u8 Copy_u8X, u8 Copy_u8Y) {
    u8 Local_u8Address;
    if (Copy_u8Y == 0) {
        Local_u8Address = Copy_u8X;
    } else {
        Local_u8Address = Copy_u8X + 0x40;
    }
    LCD_voidSendCommand(Local_u8Address | 0x80);
}

void LCD_voidSendNumber(u32 Copy_u32Number) {
    /* CRITICAL FIX: Buffer size increased to hold up to 10 digits */
    u8 Local_u8Buffer[10];
    s8 i = 0;

    if (Copy_u32Number == 0) {
        LCD_voidSendData('0');
        return;
    }

    while (Copy_u32Number != 0) {
        Local_u8Buffer[i++] = (Copy_u32Number % 10) + '0';
        Copy_u32Number /= 10;
    }

    i--;
    while (i >= 0) {
        LCD_voidSendData(Local_u8Buffer[i--]);
    }
}

/* ========================================================================= */
/*                       Project-Specific Implementations                    */
/* ========================================================================= */

void LCD_voidDisplayIdle(u8* Copy_pu8Scene, u8 Copy_u8Temp, u8* Copy_pu8ZoneStates, u8 Copy_u8FanLevel, u8 Copy_u8LockState) {
    LCD_voidClear();

    /* Line 1: Scene and Temperature (e.g., "HOME         25C") */
    LCD_voidGoToXY(0, 0);
    LCD_voidSendString(Copy_pu8Scene);
    LCD_voidGoToXY(13, 0);
    LCD_voidSendNumber(Copy_u8Temp);
    LCD_voidSendData('C');

    /* Line 2: Zone States, Fan Level, and Lock Status */
    /* Example format per README: ". 0 * F 0 L K" */
    LCD_voidGoToXY(0, 1);
    LCD_voidSendString(Copy_pu8ZoneStates);

    LCD_voidGoToXY(10, 1);
    LCD_voidSendData('F');
    LCD_voidSendNumber(Copy_u8FanLevel);

    LCD_voidGoToXY(14, 1);
    if(Copy_u8LockState == 1) {
        LCD_voidSendString((u8*)"UN"); /* Unlocked */
    } else {
        LCD_voidSendString((u8*)"LK"); /* Locked */
    }
}

void LCD_voidDisplayPinEntry(u8 Copy_u8DigitsEntered) {
    LCD_voidClear();
    LCD_voidGoToXY(0, 0);
    LCD_voidSendString((u8*)"ENTER PIN:");

    LCD_voidGoToXY(0, 1);
    for (u8 i = 0; i < Copy_u8DigitsEntered; i++) {
        LCD_voidSendData('*'); /* Print '*' to mask digits */
    }
}

void LCD_voidDisplayLockout(u8 Copy_u8SecondsLeft) {
    LCD_voidClear();
    LCD_voidGoToXY(0, 0);
    LCD_voidSendString((u8*)"LOCKED OUT!");
    LCD_voidGoToXY(0, 1);
    LCD_voidSendString((u8*)"WAIT: ");
    LCD_voidSendNumber(Copy_u8SecondsLeft);
    LCD_voidSendString((u8*)" s");
}

void LCD_voidDisplayAlarm(u8* Copy_pu8AlarmMsg) {
    LCD_voidClear();
    LCD_voidGoToXY(0, 0);
    LCD_voidSendString((u8*)"!!! ALARM !!!");
    LCD_voidGoToXY(0, 1);
    LCD_voidSendString(Copy_pu8AlarmMsg); /* Pass "GAS" or "INTRUSION" */
}
