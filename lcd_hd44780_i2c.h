#ifndef LCD_HD44780_H_
#define LCD_HD44780_H_

#include "../../Service/std_types.h"
#include "../../MCL/gpio.h"

/* =========================================================================
 *                         Configurations & HW Pins
 * ========================================================================= */
#define LCD_DATA_BITS_MODE          4   /* 4-bit mode */

#define LCD_RS_PORT_ID              PORTA_ID
#define LCD_RS_PIN_ID               PIN1_ID

#define LCD_E_PORT_ID               PORTA_ID
#define LCD_E_PIN_ID                PIN2_ID

#define LCD_DATA_PORT_ID            PORTA_ID

#if (LCD_DATA_BITS_MODE == 4)
#define LCD_DB4_PIN_ID              PIN3_ID
#define LCD_DB5_PIN_ID              PIN4_ID
#define LCD_DB6_PIN_ID              PIN5_ID
#define LCD_DB7_PIN_ID              PIN6_ID
#endif

/* Commands Definitions */
#define LCD_CLEAR_COMMAND                    0x01
#define LCD_GO_TO_HOME                       0x02
#define LCD_TWO_LINES_FOUR_BITS_MODE         0x28
#define LCD_TWO_LINES_EIGHT_BITS_MODE        0x38
#define LCD_CURSOR_OFF                       0x0C
#define LCD_CURSOR_ON                        0x0E

/* =========================================================================
 *                         Functions Prototypes
 * ========================================================================= */

void LCD_init(void);
void LCD_sendCommand(uint8_t command);
void LCD_displayCharacter(uint8_t data);
void LCD_displayString(const char *Str);
void LCD_moveCursor(uint8_t row, uint8_t col);
void LCD_clearScreen(void);

#endif /* LCD_HD44780_H_ */