#ifndef TIMER0_H_
#define TIMER0_H_

#include "../Service/std_types.h"

/* =========================================================================
 *                         Definitions & Types
 * ========================================================================= */

typedef enum {
    TIMER0_NORMAL_MODE,
    TIMER0_PWM_MODE,
    TIMER0_CTC_MODE,
    TIMER0_FAST_PWM_MODE
} Timer0_Mode;

typedef enum {
    TIMER0_NO_CLOCK,
    TIMER0_PRESCALER_1,
    TIMER0_PRESCALER_8,
    TIMER0_PRESCALER_64,
    TIMER0_PRESCALER_256,
    TIMER0_PRESCALER_1024
} Timer0_Prescaler;

typedef struct {
    Timer0_Mode mode;
    Timer0_Prescaler prescaler;
    uint8_t initial_value;
    uint8_t compare_value; /* Used in CTC mode */
} Timer0_ConfigType;

/* =========================================================================
 *                         Functions Prototypes
 * ========================================================================= */

/**
 * @brief Initializes Timer0 with the specified configuration.
 */
void Timer0_init(const Timer0_ConfigType *Config_Ptr);

/**
 * @brief Sets a callback function to be executed on Timer0 interrupt.
 */
void Timer0_setCallBack(void (*a_ptr)(void));

/**
 * @brief Stops Timer0 by clearing its clock source.
 */
void Timer0_deInit(void);

#endif /* TIMER0_H_ */