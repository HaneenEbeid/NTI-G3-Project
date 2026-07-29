#include "lcd_hd44780.h"
#include <util/delay.h>

void LCD_init(void) {
    /* Configure Control Pins as Output */
    GPIO_setupPinDirection(LCD_RS_PORT_ID, LCD_RS_PIN_ID, PIN_OUTPUT);
    GPIO_setupPinDirection(LCD_E_PORT_ID, LCD_E_PIN_ID, PIN_OUTPUT);

    _delay_ms(20); /* LCD Power ON delay */

#if (LCD_DATA_BITS_MODE == 4)
    /* Configure Data Pins as Output */
    GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, PIN_OUTPUT);
    GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, PIN_OUTPUT);
    GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, PIN_OUTPUT);
    GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, PIN_OUTPUT);

    /* Initialize LCD in 4-bit mode */
    LCD_sendCommand(LCD_GO_TO_HOME);
    LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);
#elif (LCD_DATA_BITS_MODE == 8)
    GPIO_setupPortDirection(LCD_DATA_PORT_ID, PORT_OUTPUT);
    LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);
#endif

    LCD_sendCommand(LCD_CURSOR_OFF);
    LCD_sendCommand(LCD_CLEAR_COMMAND);
}

void LCD_sendCommand(uint8_t command) {
    GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, 0); /* Instruction Mode */
    _delay_ms(1);
    GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, 1);    /* Enable High */
    _delay_ms(1);

#if (LCD_DATA_BITS_MODE == 4)
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, GET_BIT(command, 4));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, GET_BIT(command, 5));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, GET_BIT(command, 6));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, GET_BIT(command, 7));

    _delay_ms(1);
    GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, 0); /* Enable Low */
    _delay_ms(1);

    GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, 1); /* Enable High for lower nibble */
    _delay_ms(1);

    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, GET_BIT(command, 0));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, GET_BIT(command, 1));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, GET_BIT(command, 2));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, GET_BIT(command, 3));

    _delay_ms(1);
    GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, 0);
    _delay_ms(1);
#endif
}

void LCD_displayCharacter(uint8_t data) {
    GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, 1); /* Data Mode */
    _delay_ms(1);
    GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, 1);
    _delay_ms(1);

#if (LCD_DATA_BITS_MODE == 4)
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, GET_BIT(data, 4));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, GET_BIT(data, 5));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, GET_BIT(data, 6));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, GET_BIT(data, 7));

    _delay_ms(1);
    GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, 0);
    _delay_ms(1);

    GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, 1);
    _delay_ms(1);

    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, GET_BIT(data, 0));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, GET_BIT(data, 1));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, GET_BIT(data, 2));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, GET_BIT(data, 3));

    _delay_ms(1);
    GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, 0);
    _delay_ms(1);
#endif
}

void LCD_displayString(const char *Str) {
    uint8_t i = 0;
    while (Str[i] != '\0') {
        LCD_displayCharacter(Str[i]);
        i++;
    }
}

void LCD_clearScreen(void) {
    LCD_sendCommand(LCD_CLEAR_COMMAND);
}