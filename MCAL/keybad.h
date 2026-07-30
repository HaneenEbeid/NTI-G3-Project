#ifndef KEYPAD_H_
#define KEYPAD_H_

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

#define KEYPAD_PORT_DIR  DDRC
#define KEYPAD_PORT_OUT  PORTC
#define KEYPAD_PORT_IN   PINC

#define NUM_ROWS 4
#define NUM_COLS 3

#define KEYPAD_NO_KEY    0xFF 

void KEYPAD_init(void);
uint8_t KEYPAD_getKey(void);

#endif
