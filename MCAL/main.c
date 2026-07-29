#define F_CPU 8000000UL
#include <util/delay.h>
#include "gpio.h"
#include "keypad.h"
#include "lcd_hd44780.h"
#include "lcd_aip31068_i2c.h"
#include "i2c.h"
#include "timer0.h"
#include "scheduler.h"
#include "security.h"

int main(void) {
    gpio_init();
    i2c_init();
    lcd_hd44780_init();
    lcd_aip31068_init();
    keypad_init();
    timer0_init();
    security_init();
    scheduler_init();

    scheduler_start();

    while (1) {
        scheduler_dispatch();
    }
}
