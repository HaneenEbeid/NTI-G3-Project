#ifndef GPIO_H_
#define GPIO_H_

#include "std.h"

/* =========================================================================
 *                         Definitions & Types
 * ========================================================================= */
#define NUM_OF_PORTS           4
#define NUM_OF_PINS_PER_PORT   8

typedef enum {
    PORTA_ID,
    PORTB_ID,
    PORTC_ID,
    PORTD_ID
} GPIO_PortId;

typedef enum {
    PIN0_ID, PIN1_ID, PIN2_ID, PIN3_ID,
    PIN4_ID, PIN5_ID, PIN6_ID, PIN7_ID
} GPIO_PinId;

typedef enum {
    PIN_INPUT,
    PIN_OUTPUT
} GPIO_PinDirectionType;

typedef enum {
    PORT_INPUT,
    PORT_OUTPUT = 0xFF
} GPIO_PortDirectionType;

/* =========================================================================
 *                         Functions Prototypes
 * ========================================================================= */

/* التحكم على مستوى الـ Pin */
void GPIO_setupPinDirection(GPIO_PortId port_id, GPIO_PinId pin_id, GPIO_PinDirectionType direction);
void GPIO_writePin(GPIO_PortId port_id, GPIO_PinId pin_id, uint8_t value);
uint8_t GPIO_readPin(GPIO_PortId port_id, GPIO_PinId pin_id);

/* التحكم على مستوى الـ Port كامل */
void GPIO_setupPortDirection(GPIO_PortId port_id, GPIO_PortDirectionType direction);
void GPIO_writePort(GPIO_PortId port_id, uint8_t value);
uint8_t GPIO_readPort(GPIO_PortId port_id);

#endif /* GPIO_H_ */
