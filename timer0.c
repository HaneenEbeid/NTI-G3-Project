#include "timer0.h"
#include <avr/io.h>
#include <avr/interrupt.h>
/* Global pointer to store the address of the callback function */
static volatile void (*g_callBackPtr)(void) = NULL;

/* =========================================================================
 *                         Interrupt Service Routines
 * ========================================================================= */

ISR(TIMER0_OVF_vect) {
    if (g_callBackPtr != NULL) {
        (*g_callBackPtr)();
    }
}

ISR(TIMER0_COMP_vect) {
    if (g_callBackPtr != NULL) {
        (*g_callBackPtr)();
    }
}

/* =========================================================================
 *                         Functions Implementation
 * ========================================================================= */

void Timer0_init(const Timer0_ConfigType *Config_Ptr) {
    /* Set initial counter value */
    TCNT0 = Config_Ptr->initial_value;

    if (Config_Ptr->mode == TIMER0_CTC_MODE) {
        /* Configure Compare Match mode (CTC) */
        OCR0 = Config_Ptr->compare_value;
        TCCR0 = (1 << FOC0) | (1 << WGM01);
        TIMSK |= (1 << OCIE0); /* Enable Compare Match Interrupt */
    } else {
        /* Normal Mode */
        TCCR0 = (1 << FOC0);
        TIMSK |= (1 << TOIE0);  /* Enable Overflow Interrupt */
    }

    /* Set prescaler (Starts the timer) */
    TCCR0 = (TCCR0 & 0xF8) | (Config_Ptr->prescaler & 0x07);
}

void Timer0_setCallBack(void (*a_ptr)(void)) {
    g_callBackPtr = a_ptr;
}

void Timer0_deInit(void) {
    /* Clear TCCR0 and reset counter to stop the timer */
    TCCR0 = 0;
    TCNT0 = 0;
    OCR0 = 0;
    TIMSK &= ~((1 << TOIE0) | (1 << OCIE0));
}