#include "../../Service/STD_Types.h"
#include "../../Service/Bit_Math.h"
#include "adc_registers.h"
#include "adc_interface.h"

/*
 * =====================================================================================
 *  STUDENT TEMPLATE
 *  Every function below only has its signature and a numbered comment "recipe".
 *  Follow the steps IN ORDER and turn each one into a real line (or few lines) of C,
 *  using the register/bit names defined in adc_registers.h and ONLY the macros
 *  provided by Bit_Math.h:
 *      SET_BIT(REG, BIT)   set  one bit
 *      CLR_BIT(REG, BIT)   clear one bit
 *      TOG_BIT(REG, BIT)   toggle one bit
 *      GET_BIT(REG, BIT)   read  one bit (returns 0 or 1)
 *  (see GPIO/gpio.c for examples of the same coding style used in this project).
 *
 *  Bit_Math.h only works one bit at a time - there is no macro to write a whole
 *  multi-bit field in one shot. So whenever a step needs to set a multi-bit field
 *  (e.g. the 2-bit voltage reference, or the 3-bit prescaler), the pattern is
 *  always the same:
 *    1) CLR_BIT every bit that belongs to the field, one call per bit.
 *    2) For each of those bits, use GET_BIT on the source value to check whether
 *       that bit should be a 1, and if so SET_BIT the matching register bit.
 * =====================================================================================
 */

/*
 * Initializes the ADC peripheral: selects the voltage reference, selects the
 * clock prescaler, and enables the module.
 */
STD_ReturnType ADC_Init(const ADC_ConfigType *addConfig)
{
    /* Step 1: Declare a local variable "local_Status" of type STD_ReturnType and
     *         initialize it to E_OK. This is what you will return at the end. */

    /* Step 2: Check if addConfig is NULL (the caller passed an invalid pointer).
     *         If it is NULL, set local_Status = E_NOK and do nothing else
     *         (skip straight to returning local_Status). */

    /* Step 3: Otherwise (addConfig is a valid pointer), configure the reference
     *         voltage. REFS1:REFS0 is a 2-bit field (REFS0 = bit 6, REFS1 = bit 7),
     *         so clear both bits first, then set only the ones the config asks for:
     *   3.1 CLR_BIT(ADC_ADMUX_REG, ADC_REFS0_BIT)
     *   3.2 CLR_BIT(ADC_ADMUX_REG, ADC_REFS1_BIT)
     *   3.3 If GET_BIT(addConfig->uint8ReferenceVoltage, 0) is 1,
     *       SET_BIT(ADC_ADMUX_REG, ADC_REFS0_BIT)
     *   3.4 If GET_BIT(addConfig->uint8ReferenceVoltage, 1) is 1,
     *       SET_BIT(ADC_ADMUX_REG, ADC_REFS1_BIT) */

    /* Step 4: Make sure the result will be right-adjusted:
     *   4.1 CLR_BIT(ADC_ADMUX_REG, ADC_ADLAR_BIT) */

    /* Step 5: Select a default input channel (channel 0) so the MUX bits start
     *         in a known state. Channel 0 means every MUX bit is 0, so just
     *         clear all five of them, one CLR_BIT call per bit:
     *   5.1 CLR_BIT(ADC_ADMUX_REG, ADC_MUX0_BIT)
     *   5.2 CLR_BIT(ADC_ADMUX_REG, ADC_MUX1_BIT)
     *   5.3 CLR_BIT(ADC_ADMUX_REG, ADC_MUX2_BIT)
     *   5.4 CLR_BIT(ADC_ADMUX_REG, ADC_MUX3_BIT)
     *   5.5 CLR_BIT(ADC_ADMUX_REG, ADC_MUX4_BIT) */

    /* Step 6: Configure the clock prescaler. ADPS2:ADPS0 is a 3-bit field
     *         (bits 0-2 of ADC_ADCSRA_REG), so clear all three bits first,
     *         then set only the ones addConfig->uint8Prescaler asks for:
     *   6.1 CLR_BIT(ADC_ADCSRA_REG, ADC_ADPS0_BIT)
     *   6.2 CLR_BIT(ADC_ADCSRA_REG, ADC_ADPS1_BIT)
     *   6.3 CLR_BIT(ADC_ADCSRA_REG, ADC_ADPS2_BIT)
     *   6.4 If GET_BIT(addConfig->uint8Prescaler, 0) is 1,
     *       SET_BIT(ADC_ADCSRA_REG, ADC_ADPS0_BIT)
     *   6.5 If GET_BIT(addConfig->uint8Prescaler, 1) is 1,
     *       SET_BIT(ADC_ADCSRA_REG, ADC_ADPS1_BIT)
     *   6.6 If GET_BIT(addConfig->uint8Prescaler, 2) is 1,
     *       SET_BIT(ADC_ADCSRA_REG, ADC_ADPS2_BIT) */

    /* Step 7: Enable the ADC module itself:
     *   7.1 SET_BIT the ADC_ADEN_BIT in ADC_ADCSRA_REG.
     *   Note: on real hardware, the very first conversion after enabling the ADC
     *   takes longer (25 ADC clock cycles) than later ones (13 cycles) - this is
     *   just something to be aware of, no extra code is required for it here. */

    /* Step 8: Return local_Status. */
}

/*
 * Disables the ADC peripheral (powers it down / stops conversions).
 */
STD_ReturnType ADC_DeInit(void)
{
    /* Step 1: CLR_BIT the ADC_ADEN_BIT in ADC_ADCSRA_REG to disable the ADC. */

    /* Step 2: Return E_OK. */
}

/*
 * Selects the given channel and starts a single conversion (non-blocking).
 */
STD_ReturnType ADC_StartConversion(uint8_h uint8Channel)
{
    /* Step 1: Declare a local variable "local_Status" of type STD_ReturnType and
     *         initialize it to E_OK. */

    /* Step 2: Validate uint8Channel: it must be less than ADC_NUMBER_OF_CHANNELS.
     *         If it is out of range, set local_Status = E_NOK and skip the rest. */

    /* Step 3: Otherwise, select the new channel. ADC_CHANNEL0..ADC_CHANNEL7 only
     *         need the low 3 MUX bits (MUX2:MUX0); MUX3 and MUX4 stay 0 for these
     *         single-ended channels. Clear all five MUX bits first, then set only
     *         the low 3 bits that uint8Channel asks for:
     *   3.1 CLR_BIT(ADC_ADMUX_REG, ADC_MUX0_BIT)
     *   3.2 CLR_BIT(ADC_ADMUX_REG, ADC_MUX1_BIT)
     *   3.3 CLR_BIT(ADC_ADMUX_REG, ADC_MUX2_BIT)
     *   3.4 CLR_BIT(ADC_ADMUX_REG, ADC_MUX3_BIT)
     *   3.5 CLR_BIT(ADC_ADMUX_REG, ADC_MUX4_BIT)
     *   3.6 If GET_BIT(uint8Channel, 0) is 1, SET_BIT(ADC_ADMUX_REG, ADC_MUX0_BIT)
     *   3.7 If GET_BIT(uint8Channel, 1) is 1, SET_BIT(ADC_ADMUX_REG, ADC_MUX1_BIT)
     *   3.8 If GET_BIT(uint8Channel, 2) is 1, SET_BIT(ADC_ADMUX_REG, ADC_MUX2_BIT) */

    /* Step 4: SET_BIT the ADC_ADSC_BIT in ADC_ADCSRA_REG. This tells the hardware
     *         to start converting the selected channel right now. */

    /* Step 5: Return local_Status. */
}

/*
 * Reports whether the ADC has finished the conversion that was last started.
 */
uint8_h ADC_IsConversionComplete(void)
{
    /* Step 1: Read the ADC_ADSC_BIT from ADC_ADCSRA_REG using GET_BIT.
     *         Hardware clears this bit automatically once the conversion finishes,
     *         so while it reads 1 the conversion is still running. */

    /* Step 2: If the bit you read is 0, the conversion is done: return
     *         ADC_CONVERSION_DONE. Otherwise return ADC_CONVERSION_BUSY. */
}

/*
 * Reads the 10-bit result of the last completed conversion.
 */
STD_ReturnType ADC_ReadResult(uint16_h *puint16Result)
{
    /* Step 1: Check if puint16Result is NULL. If so, return E_NOK immediately. */

    /* Step 2: The datasheet requires ADCL to be read BEFORE ADCH (reading ADCL
     *         locks ADCH until it is read too, guaranteeing both bytes belong to
     *         the same conversion). Read ADC_ADCL_REG into a local uint8_h
     *         variable first. */

    /* Step 3: Then read ADC_ADCH_REG into a second local uint8_h variable. */

    /* Step 4: Combine the two bytes into the final 10-bit value:
     *         result = (high byte << 8) | low byte
     *         and store it in *puint16Result. */

    /* Step 5: Return E_OK. */
}

/*
 * Blocking read: starts a conversion on the given channel, busy-waits until it
 * finishes, then returns the result.
 */
STD_ReturnType ADC_ReadChannelBlocking(uint8_h uint8Channel, uint16_h *puint16Result)
{
    /* Step 1: Declare a local variable "local_Status" of type STD_ReturnType.
     *         Call ADC_StartConversion(uint8Channel) and store its return value
     *         in local_Status. */

    /* Step 2: If local_Status == E_OK, wait for the conversion to finish:
     *         write a while loop that keeps calling ADC_IsConversionComplete()
     *         and loops (does nothing) as long as it returns ADC_CONVERSION_BUSY. */

    /* Step 3: Once the loop exits, call ADC_ReadResult(puint16Result) and store
     *         its return value back into local_Status. */

    /* Step 4: Return local_Status. */
}

