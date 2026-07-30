/*
 * I2C_LCD_interface.h
 *
 *  Created on: Jul 30, 2026
 *      Author: elwady
 */

#ifndef I2C_LCD_INTERFACE_H_
#define I2C_LCD_INTERFACE_H_


void I2C_LCD_Init(void);
void I2C_LCD_Start(void);
void I2C_LCD_Write(u8 data);
void I2C_LCD_Stop(void);


#endif /* I2C_LCD_INTERFACE_H_ */
