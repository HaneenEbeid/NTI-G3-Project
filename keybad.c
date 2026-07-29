#include "keypad.h"

static const uint8_t g_keypadMatrix[NUM_ROWS][NUM_COLS] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}
};

void KEYPAD_init(void)
{
    KEYPAD_PORT_DIR = (KEYPAD_PORT_DIR & 0x80) | 0x0F; 
    KEYPAD_PORT_OUT = (KEYPAD_PORT_OUT & 0x80) | 0x7F; 
}

uint8_t KEYPAD_getKey(void)
{
    uint8_t row, col;

    for (row = 0; row < NUM_ROWS; row++)
    {
        KEYPAD_PORT_OUT = (KEYPAD_PORT_OUT & 0xF0) | (~(1 << row) & 0x0F);
        _delay_us(10);

        for (col = 0; col < NUM_COLS; col++)
        {
            if (!(KEYPAD_PORT_IN & (1 << (col + 4))))
            {
                while (!(KEYPAD_PORT_IN & (1 << (col + 4))));
                return g_keypadMatrix[row][col];
            }
        }
    }

    return KEYPAD_NO_KEY;
}