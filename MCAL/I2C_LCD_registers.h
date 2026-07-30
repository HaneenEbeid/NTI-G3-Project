/*
 * I2C_LCD_registers.h
 *
 *  Created on: Jul 30, 2026
 *      Author: elwady
 */

#ifndef I2C_LCD_REGISTERS_H_
#define I2C_LCD_REGISTERS_H_




/* TWI/I2C Registers Definition */
#define TWBR_REG   (*(volatile u8*)0x20) /* TWI Bit Rate Register [6] */
#define TWSR_REG   (*(volatile u8*)0x21) /* TWI Status Register [7] */
#define TWAR_REG   (*(volatile u8*)0x22) /* TWI Address Register [8] */
#define TWDR_REG   (*(volatile u8*)0x23) /* TWI Data Register [8] */
#define TWCR_REG   (*(volatile u8*)0x56) /* TWI Control Register [4] */

/* TWCR Register Bits [9, 10] */
#define TWIE    0
#define TWEN    2  /* TWI Enable Bit */
#define TWWC    3
#define TWSTO   4  /* TWI STOP Condition Bit */
#define TWSTA   5  /* TWI START Condition Bit */
#define TWEA    6
#define TWINT   7  /* TWI Interrupt Flag */


#endif /* I2C_LCD_REGISTERS_H_ */
