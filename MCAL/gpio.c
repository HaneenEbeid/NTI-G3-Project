#include "gpio.h"
#include <avr/io.h> /* Includes ATmega32 register definitions */

/* =========================================================================
 *                         Functions Implementation
 * ========================================================================= */

/**
 * @brief Sets the direction of a specific pin (Input or Output).
 */
void GPIO_setupPinDirection(GPIO_PortId port_id, GPIO_PinId pin_id, GPIO_PinDirectionType direction) {
    if ((pin_id >= NUM_OF_PINS_PER_PORT) || (port_id >= NUM_OF_PORTS)) {
        /* Do Nothing: Invalid input parameters */
    } else {
        switch (port_id) {
        case PORTA_ID:
            if (direction == PIN_OUTPUT) {
                DDRA |= (1 << pin_id);
            } else {
                DDRA &= ~(1 << pin_id);
            }
            break;
        case PORTB_ID:
            if (direction == PIN_OUTPUT) {
                DDRB |= (1 << pin_id);
            } else {
                DDRB &= ~(1 << pin_id);
            }
            break;
        case PORTC_ID:
            if (direction == PIN_OUTPUT) {
                DDRC |= (1 << pin_id);
            } else {
                DDRC &= ~(1 << pin_id);
            }
            break;
        case PORTD_ID:
            if (direction == PIN_OUTPUT) {
                DDRD |= (1 << pin_id);
            } else {
                DDRD &= ~(1 << pin_id);
            }
            break;
        }
    }
}

/**
 * @brief Writes a logic high (1) or low (0) value to a specific pin.
 */
void GPIO_writePin(GPIO_PortId port_id, GPIO_PinId pin_id, uint8_t value) {
    if ((pin_id >= NUM_OF_PINS_PER_PORT) || (port_id >= NUM_OF_PORTS)) {
        /* Do Nothing: Invalid input parameters */
    } else {
        switch (port_id) {
        case PORTA_ID:
            if (value == 1) {
                PORTA |= (1 << pin_id);
            } else {
                PORTA &= ~(1 << pin_id);
            }
            break;
        case PORTB_ID:
            if (value == 1) {
                PORTB |= (1 << pin_id);
            } else {
                PORTB &= ~(1 << pin_id);
            }
            break;
        case PORTC_ID:
            if (value == 1) {
                PORTC |= (1 << pin_id);
            } else {
                PORTC &= ~(1 << pin_id);
            }
            break;
        case PORTD_ID:
            if (value == 1) {
                PORTD |= (1 << pin_id);
            } else {
                PORTD &= ~(1 << pin_id);
            }
            break;
        }
    }
}

/**
 * @brief Reads and returns the value (0 or 1) of a specific pin.
 */
uint8_t GPIO_readPin(GPIO_PortId port_id, GPIO_PinId pin_id) {
    uint8_t pin_value = 0;
    if ((pin_id >= NUM_OF_PINS_PER_PORT) || (port_id >= NUM_OF_PORTS)) {
        /* Do Nothing: Invalid input parameters */
    } else {
        switch (port_id) {
        case PORTA_ID:
            if (PINA & (1 << pin_id)) pin_value = 1;
            break;
        case PORTB_ID:
            if (PINB & (1 << pin_id)) pin_value = 1;
            break;
        case PORTC_ID:
            if (PINC & (1 << pin_id)) pin_value = 1;
            break;
        case PORTD_ID:
            if (PIND & (1 << pin_id)) pin_value = 1;
            break;
        }
    }
    return pin_value;
}

/**
 * @brief Sets the direction of an entire port (Input or Output).
 */
void GPIO_setupPortDirection(GPIO_PortId port_id, GPIO_PortDirectionType direction) {
    if (port_id >= NUM_OF_PORTS) {
        /* Do Nothing: Invalid input parameters */
    } else {
        switch (port_id) {
        case PORTA_ID: DDRA = direction; break;
        case PORTB_ID: DDRB = direction; break;
        case PORTC_ID: DDRC = direction; break;
        case PORTD_ID: DDRD = direction; break;
        }
    }
}

/**
 * @brief Writes an 8-bit value to an entire port.
 */
void GPIO_writePort(GPIO_PortId port_id, uint8_t value) {
    if (port_id >= NUM_OF_PORTS) {
        /* Do Nothing: Invalid input parameters */
    } else {
        switch (port_id) {
        case PORTA_ID: PORTA = value; break;
        case PORTB_ID: PORTB = value; break;
        case PORTC_ID: PORTC = value; break;
        case PORTD_ID: PORTD = value; break;
        }
    }
}

/**
 * @brief Reads and returns the 8-bit value of an entire port.
 */
uint8_t GPIO_readPort(GPIO_PortId port_id) {
    uint8_t port_value = 0;
    if (port_id >= NUM_OF_PORTS) {
        /* Do Nothing: Invalid input parameters */
    } else {
        switch (port_id) {
        case PORTA_ID: port_value = PINA; break;
        case PORTB_ID: port_value = PINB; break;
        case PORTC_ID: port_value = PINC; break;
        case PORTD_ID: port_value = PIND; break;
        }
    }
    return port_value;
}
