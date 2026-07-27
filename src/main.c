#include "../Service/Bit_Math.h"
#include "../MCL/GPIO/gpio_interface.h"
#include "../MCL/GPIO/gpio_registers.h"
#include "../MCL/Interrupt/interrupt_interface.h"

/*
 * External interrupt test:
 *   - INT0 (pin PD2) is configured for a falling-edge trigger.
 *   - The LED on PORTA pin 2 (PA2) toggles every time the interrupt fires.
 *
 * Wiring: drive PD2 from a push button. With the internal pull-up enabled,
 * PD2 idles high and a button press pulls it low -> falling edge -> ISR.
 */

/* Callback executed from the INT0 ISR - keep it short. */
static void INT0_Handler(void)
{
    GPIO_PinToggle(GPIO_PORTA, GPIO_PIN2);
}

int main(void)
{
    EXTI_ConfigType int0Config = { EXTI_INT0, EXTI_SENSE_ANY_CHANGE };

    /* LED on PA2 as output, start off. */
    GPIO_SetPinDirection(GPIO_PORTA, GPIO_PIN2, GPIO_OUTPUT);
    GPIO_SetPinValue(GPIO_PORTA, GPIO_PIN2, 0);

    /* INT0 source pin PD2 as input with internal pull-up enabled. */
    GPIO_SetPinDirection(GPIO_PORTD, GPIO_PIN2, GPIO_INPUT);
    GPIO_SetPinValue(GPIO_PORTD, GPIO_PIN2, 1);   /* PORTD.2 = 1 -> pull-up */

    /* Register the handler, then configure + enable the line. */
    EXTI_SetCallBack(EXTI_INT0, INT0_Handler);
    EXTI_Init(&int0Config);

    /* Allow interrupts to be serviced. */
    EXTI_EnableGlobalInterrupt();

    while (1)
    {

    }

    return 0;
}
