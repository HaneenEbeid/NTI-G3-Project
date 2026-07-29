#ifndef I2C_H_
#define I2C_H_

#include "../Service/std_types.h"

/* =========================================================================
 *                         Definitions & Types
 * ========================================================================= */

/* Common I2C Status Codes (TWSR) */
#define I2C_START         0x08 /* Start condition transmitted */
#define I2C_REP_START     0x10 /* Repeated start condition transmitted */
#define I2C_MT_SLA_ACK    0x18 /* Master transmit SLA+W ACK received */
#define I2C_MT_DATA_ACK   0x28 /* Master transmit Data ACK received */
#define I2C_MR_SLA_ACK    0x40 /* Master receive SLA+R ACK received */
#define I2C_MR_DATA_ACK   0x58 /* Master receive Data ACK returned */
#define I2C_MR_DATA_NACK  0x5C /* Master receive Data NACK returned */

typedef uint32_t I2C_BaudRateType;
typedef uint8_t  I2C_AddressType;

typedef struct {
    I2C_BaudRateType baud_rate;
    I2C_AddressType  address;
} I2C_ConfigType;

/* =========================================================================
 *                         Functions Prototypes
 * ========================================================================= */

/**
 * @brief Initializes the I2C module with given baud rate and slave address.
 */
void I2C_init(const I2C_ConfigType *Config_Ptr);

/**
 * @brief Transmits a START condition on the bus.
 */
void I2C_start(void);

/**
 * @brief Transmits a STOP condition on the bus.
 */
void I2C_stop(void);

/**
 * @brief Writes a byte of data/address to the I2C bus.
 */
void I2C_writeByte(uint8_t data);

/**
 * @brief Reads a byte of data from the bus and sends an ACK.
 */
uint8_t I2C_readByteWithACK(void);

/**
 * @brief Reads a byte of data from the bus and sends a NACK.
 */
uint8_t I2C_readByteWithNACK(void);

/**
 * @brief Returns the status of the I2C bus (TWSR status bits).
 */
uint8_t I2C_getStatus(void);

#endif /* I2C_H_ */
