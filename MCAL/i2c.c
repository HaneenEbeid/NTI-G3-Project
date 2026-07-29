#include "i2c.h"
#include <avr/io.h>

/* =========================================================================
 *                         Functions Implementation
 * ========================================================================= */

void I2C_init(const I2C_ConfigType *Config_Ptr) {
    /* Bit Rate Register Calculation for F_CPU = 8MHz, Prescaler = 1 */
    TWBR = (uint8_t)(((F_CPU / Config_Ptr->baud_rate) - 16) / 2);
    TWSR = 0; /* Prescaler = 1 */

    /* Assign Slave Address (Used if ATmega32 operates as Slave) */
    TWAR = (Config_Ptr->address << 1);

    /* Enable TWI/I2C peripheral */
    TWCR = (1 << TWEN);
}

void I2C_start(void) {
    /* Clear TWINT flag, Send START condition, Enable TWI */
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

    /* Wait for TWINT flag to be set (START condition transmitted) */
    while (!(TWCR & (1 << TWINT)));
}

void I2C_stop(void) {
    /* Clear TWINT flag, Send STOP condition, Enable TWI */
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void I2C_writeByte(uint8_t data) {
    /* Load data into TWDR register */
    TWDR = data;

    /* Clear TWINT flag to start transmission, Enable TWI */
    TWCR = (1 << TWINT) | (1 << TWEN);

    /* Wait for TWINT flag to be set (Data transmitted) */
    while (!(TWCR & (1 << TWINT)));
}

uint8_t I2C_readByteWithACK(void) {
    /* Clear TWINT flag, Enable TWI, Enable ACK generation */
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);

    /* Wait for TWINT flag to be set (Data received) */
    while (!(TWCR & (1 << TWINT)));

    return TWDR;
}

uint8_t I2C_readByteWithNACK(void) {
    /* Clear TWINT flag, Enable TWI (No ACK) */
    TWCR = (1 << TWINT) | (1 << TWEN);

    /* Wait for TWINT flag to be set (Data received) */
    while (!(TWCR & (1 << TWINT)));

    return TWDR;
}

uint8_t I2C_getStatus(void) {
    /* Mask out prescaler bits (TWPS0, TWPS1) to get status */
    return (TWSR & 0xF8);
}
