#ifndef LCD_AIP31068_I2C_H_
#define LCD_AIP31068_I2C_H_

#include "../../Service/std_types.h"
#include "../../MCL/i2c.h" /* أو twi.h حسب اسم ملف الـ I2C عندك في الـ MCAL */

/* =========================================================================
 *                         I2C Slave Address & Commands
 * ========================================================================= */
/* العنوان الافتراضي لشريحة الـ I2C PCF8574/Aip31068 هو 0x27 أو 0x3F */
#define LCD_I2C_SLAVE_ADDRESS                0x27

/* Bits Mask for Control */
#define LCD_RS_BIT                           0 /* Bit 0: Register Select (0: Cmd, 1: Data) */
#define LCD_RW_BIT                           1 /* Bit 1: Read/Write */
#define LCD_EN_BIT                           2 /* Bit 2: Enable */
#define LCD_BACKLIGHT_BIT                    3 /* Bit 3: Backlight control */

/* Commands Definitions */
#define LCD_CLEAR_COMMAND                    0x01
#define LCD_GO_TO_HOME                       0x02
#define LCD_TWO_LINES_FOUR_BITS_MODE         0x28
#define LCD_CURSOR_OFF                       0x0C

/* =========================================================================
 *                         Functions Prototypes
 * ========================================================================= */

void LCD_I2C_init(void);
void LCD_I2C_sendCommand(uint8_t command);
void LCD_I2C_displayCharacter(uint8_t data);
void LCD_I2C_displayString(const char *Str);
void LCD_I2C_clearScreen(void);

#endif /* LCD_AIP31068_I2C_H_ */