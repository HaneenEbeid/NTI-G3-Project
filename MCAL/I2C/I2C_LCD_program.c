/*
 * I2C_LCD_program.c
 *
 *  Created on: Jul 30, 2026
 *      Author: elwady
 */
#include "../../MCL/STD_TYPES.h"
#include "../../MCL/BIT_MATH.h"

#include "I2C_LCD_interface.h"
#include "I2C_LCD_registers.h"

void I2C_LCD_Init(void) {
    /*
     * Set I2C Bit Rate.
     * Based on the Datasheet formula for frequency.
     * This value depends on your crystal oscillator frequency (F_CPU).
     */
    TWBR_REG = 0x48;

    /* Enable the I2C (TWI) module */
    TWCR_REG = (1 << TWEN);
}

void I2C_LCD_Start(void) {
    /*
     * Send START condition by setting TWSTA bit,
     * clearing TWINT flag, and enabling the module via TWEN.
     */
    TWCR_REG = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

    /* Wait until the START condition is successfully transmitted (by polling TWINT flag) */
    while (!(TWCR_REG & (1 << TWINT)));
}

void I2C_LCD_Write(u8 data) {
    /* Load data or address into the TWDR data register */
    TWDR_REG = data;

    /*
     * Start transmission by clearing TWINT flag
     * and enabling the module again.
     */
    TWCR_REG = (1 << TWINT) | (1 << TWEN);

    /* Wait until data transmission is complete */
    while (!(TWCR_REG & (1 << TWINT)));
}

void I2C_LCD_Stop(void) {
    /*
     * Send STOP condition to terminate the communication by setting TWSTO bit,
     * clearing TWINT flag, and enabling the module.
     */
    TWCR_REG = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);

    /* No need to wait for TWINT here in case of a STOP condition according to the Datasheet */
}
