#include "lcd_aip31068_i2c.h"
#include <util/delay.h>

/* دالة مساعدة لبعث البايت عبر الـ I2C مع نبضة الـ Enable */
static void LCD_I2C_writeWriteNibble(uint8_t nibble, uint8_t mode) {
    uint8_t data_frame = (nibble & 0xF0) | mode | (1 << LCD_BACKLIGHT_BIT);

    /* بعث البيانات مع Enable High */
    I2C_start();
    I2C_writeByte((LCD_I2C_SLAVE_ADDRESS << 1) | 0); /* Write operation */
    I2C_writeByte(data_frame | (1 << LCD_EN_BIT));
    _delay_us(1);

    /* تنزيل الـ Enable للأسفل Pulse Low */
    I2C_writeByte(data_frame & ~(1 << LCD_EN_BIT));
    I2C_stop();
    _delay_us(50);
}

void LCD_I2C_init(void) {
    I2C_init(); /* تهيئة بروتوكول الـ I2C في المايكرو */
    _delay_ms(50);

    /* تهيئة الشاشة على وضع 4-Bit عبر الـ I2C */
    LCD_I2C_sendCommand(LCD_GO_TO_HOME);
    LCD_I2C_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);
    LCD_I2C_sendCommand(LCD_CURSOR_OFF);
    LCD_I2C_sendCommand(LCD_CLEAR_COMMAND);
}

void LCD_I2C_sendCommand(uint8_t command) {
    /* RS = 0 لإرسال أمر */
    LCD_I2C_writeWriteNibble(command & 0xF0, 0);        /* High Nibble */
    LCD_I2C_writeWriteNibble((command << 4) & 0xF0, 0); /* Low Nibble */
}

void LCD_I2C_displayCharacter(uint8_t data) {
    /* RS = 1 لإرسال بيانات/حرف */
    uint8_t mode = (1 << LCD_RS_BIT);
    LCD_I2C_writeWriteNibble(data & 0xF0, mode);        /* High Nibble */
    LCD_I2C_writeWriteNibble((data << 4) & 0xF0, mode); /* Low Nibble */
}

void LCD_I2C_displayString(const char *Str) {
    uint8_t i = 0;
    while (Str[i] != '\0') {
        LCD_I2C_displayCharacter(Str[i]);
        i++;
    }
}

void LCD_I2C_clearScreen(void) {
    LCD_I2C_sendCommand(LCD_CLEAR_COMMAND);
}