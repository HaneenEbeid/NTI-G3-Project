#include "../../Service/STD_Types.h"
#include "../../Service/Bit_Math.h"
#include "../../MCL/GPIO/gpio_interface.h"
#include "keypad_interface.h"

/* ================================================================================
 *  MATRIX KEYPAD DRIVER - IMPLEMENTATION SKELETON
 *  ------------------------------------------------------------------------------
 *  Each body lists the ordered steps to implement the function. Replace the
 *  numbered comments with the actual GPIO calls.
 *
 *  You will need a short blocking delay for debouncing, referenced below as
 *  Keypad_DelayMs(ms) - implement it as a static helper (busy loop or Timer).
 * ============================================================================== */


STD_ReturnType Keypad_Init(const Keypad_ConfigType *addConfig)
{
    /*
     * STEP 1: Validate addConfig != NULL and both ports are in range (else E_NOK).
     *
     * STEP 2: Configure the ROW pins as OUTPUT (rowStartPin .. +KEYPAD_ROWS-1) via
     *         GPIO_SetPinDirection, and drive them all HIGH (idle/inactive).
     *
     * STEP 3: Configure the COLUMN pins as INPUT (colStartPin .. +KEYPAD_COLS-1).
     *         If the hardware lacks external pull-ups, enable the internal pull-ups
     *         by writing 1 to the column PORT bits while they are inputs.
     *
     * STEP 4: Return E_OK.
     */
    return E_NOK;
}


STD_ReturnType Keypad_GetKey(const Keypad_ConfigType *addConfig, uint8_h *pKey)
{
    /*
     * STEP 1: Validate addConfig != NULL and pKey != NULL (else E_NOK).
     *
     * STEP 2: Default the result: *pKey = KEYPAD_NO_KEY;
     *
     * STEP 3: Scan one row at a time (for r = 0 .. KEYPAD_ROWS-1):
     *   a) Drive ALL rows HIGH (inactive).
     *   b) Drive the current row LOW (active):
     *      GPIO_SetPinValue(rowPort, rowStartPin + r, 0);
     *   c) For each column (for c = 0 .. KEYPAD_COLS-1):
     *        - Read the column pin: GPIO_GetPinStatus(colPort, colStartPin + c).
     *        - If it reads LOW, a key at (r,c) is pressed:
     *            * Debounce: Keypad_DelayMs(~20), then read again to confirm.
     *            * If still LOW, set *pKey = addConfig->keyMap[r][c].
     *            * (Optional) wait for release before returning.
     *            * Return E_OK.
     *
     * STEP 4: If no key found after scanning all rows, *pKey stays KEYPAD_NO_KEY.
     * STEP 5: Return E_OK.
     */
    return E_NOK;
}


STD_ReturnType Keypad_WaitForKey(const Keypad_ConfigType *addConfig, uint8_h *pKey)
{
    /*
     * STEP 1: Validate addConfig != NULL and pKey != NULL (else E_NOK).
     * STEP 2: Loop:
     *   - Call Keypad_GetKey(addConfig, pKey).
     *   - If *pKey != KEYPAD_NO_KEY, a key was pressed -> break out of the loop.
     * STEP 3: Return E_OK (with the pressed character in *pKey).
     */
    return E_NOK;
}
