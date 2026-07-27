#include <avr/interrupt.h>
#include "../../Service/STD_Types.h"
#include "../../Service/Bit_Math.h"
#include "interrupt_registers.h"
#include "interrupt_interface.h"

/* ================================================================================
 *  EXTERNAL INTERRUPT DRIVER - IMPLEMENTATION SKELETON
 *  ------------------------------------------------------------------------------
 *  Each body below lists the ordered steps to implement the function. Replace the
 *  numbered comments with the actual register manipulation code.
 * ============================================================================== */

/*
 * Callback storage: one slot per external line (INT0, INT1, INT2).
 * TODO: define a static array initialised to NULL, e.g.
 *       static EXTI_CallBackType EXTI_CallBacks[EXTI_LINE_MAX] = { NULL, NULL, NULL };
 */
static EXTI_CallBackType EXTI_CallBacks[EXTI_LINE_MAX] = { NULL, NULL, NULL };


STD_ReturnType EXTI_Init(const EXTI_ConfigType *addConfig)
{
    /*
     * STEP 1: Validate the input.
     *   - If addConfig == NULL, return E_NOK.
     *   - If addConfig->line >= EXTI_LINE_MAX, return E_NOK.
     *
     * STEP 2: Program the sense control by calling
     *         EXTI_SetSenseControl(addConfig->line, addConfig->sense).
     *         If it returns E_NOK (unsupported sense for that line), forward E_NOK.
     *
     * STEP 3: Clear any stale pending flag for the line by writing 1 to its GIFR bit
     *         (INTF0/INTF1/INTF2) so an old event does not fire immediately.
     *
     * STEP 4: Enable the line by calling EXTI_Enable(addConfig->line).
     *
     * STEP 5: Return E_OK.
     */

    /* STEP 1: Validate the input. */
    if (addConfig == NULL)
    {
        return E_NOK;
    }
    if (addConfig->line >= EXTI_LINE_MAX)
    {
        return E_NOK;
    }

    /* STEP 2: Program the sense control; forward E_NOK on unsupported combo. */
    if (EXTI_SetSenseControl(addConfig->line, addConfig->sense) == E_NOK)
    {
        return E_NOK;
    }

    /* STEP 3: Clear any stale pending flag by writing 1 to the matching GIFR bit. */
    switch (addConfig->line)
    {
        case EXTI_INT0: EXTI_GIFR_REG = (1U << EXTI_INTF0_BIT); break;
        case EXTI_INT1: EXTI_GIFR_REG = (1U << EXTI_INTF1_BIT); break;
        case EXTI_INT2: EXTI_GIFR_REG = (1U << EXTI_INTF2_BIT); break;
        default: return E_NOK;
    }

    /* STEP 4: Enable the line. */
    if (EXTI_Enable(addConfig->line) == E_NOK)
    {
        return E_NOK;
    }

    /* STEP 5: Return E_OK. */
    return E_OK;
}


STD_ReturnType EXTI_Enable(EXTI_LineType line)
{
    /*
     * STEP 1: Validate line < EXTI_LINE_MAX (else E_NOK).
     * STEP 2: Set the matching enable bit in GICR:
     *         EXTI_INT0 -> INT0 bit, EXTI_INT1 -> INT1 bit, EXTI_INT2 -> INT2 bit.
     * STEP 3: Return E_OK.
     */

    /* STEP 1: Validate line < EXTI_LINE_MAX. */
    if (line >= EXTI_LINE_MAX)
    {
        return E_NOK;
    }

    /* STEP 2: Set the matching enable bit in GICR. */
    switch (line)
    {
        case EXTI_INT0: SET_BIT(EXTI_GICR_REG, EXTI_INT0_BIT); break;
        case EXTI_INT1: SET_BIT(EXTI_GICR_REG, EXTI_INT1_BIT); break;
        case EXTI_INT2: SET_BIT(EXTI_GICR_REG, EXTI_INT2_BIT); break;
        default: return E_NOK;
    }

    /* STEP 3: Return E_OK. */
    return E_OK;
}


STD_ReturnType EXTI_Disable(EXTI_LineType line)
{
    /*
     * STEP 1: Validate line < EXTI_LINE_MAX (else E_NOK).
     * STEP 2: Clear the matching enable bit in GICR (same mapping as EXTI_Enable).
     * STEP 3: Return E_OK.
     */

    /* STEP 1: Validate line < EXTI_LINE_MAX. */
    if (line >= EXTI_LINE_MAX)
    {
        return E_NOK;
    }

    /* STEP 2: Clear the matching enable bit in GICR. */
    switch (line)
    {
        case EXTI_INT0: CLR_BIT(EXTI_GICR_REG, EXTI_INT0_BIT); break;
        case EXTI_INT1: CLR_BIT(EXTI_GICR_REG, EXTI_INT1_BIT); break;
        case EXTI_INT2: CLR_BIT(EXTI_GICR_REG, EXTI_INT2_BIT); break;
        default: return E_NOK;
    }

    /* STEP 3: Return E_OK. */
    return E_OK;
}


STD_ReturnType EXTI_SetSenseControl(EXTI_LineType line, EXTI_SenseType sense)
{
    /*
     * STEP 1: Validate line < EXTI_LINE_MAX (else E_NOK).
     *
     * STEP 2: Handle each line separately:
     *
     *   INT0 (bits ISC01:ISC00 in MCUCR):
     *     - EXTI_SENSE_LOW_LEVEL  -> 00
     *     - EXTI_SENSE_ANY_CHANGE -> 01
     *     - EXTI_SENSE_FALLING    -> 10
     *     - EXTI_SENSE_RISING     -> 11
     *     Clear both bits first, then set according to the table.
     *
     *   INT1 (bits ISC11:ISC10 in MCUCR): same 2-bit encoding as INT0.
     *
     *   INT2 (single bit ISC2 in MCUCSR):
     *     - EXTI_SENSE_FALLING    -> clear ISC2
     *     - EXTI_SENSE_RISING     -> set   ISC2
     *     - LOW_LEVEL / ANY_CHANGE are NOT supported -> return E_NOK.
     *
     * STEP 3: Return E_OK (or E_NOK for an unsupported sense/line combination).
     */

    /* STEP 1: Validate line < EXTI_LINE_MAX. */
    if (line >= EXTI_LINE_MAX)
    {
        return E_NOK;
    }

    /* STEP 2: Handle each line separately. */
    switch (line)
    {
        case EXTI_INT0:
            /* ISC01:ISC00 in MCUCR - encoding matches the sense enum value. */
            CLR_BIT(EXTI_MCUCR_REG, EXTI_ISC00_BIT);
            CLR_BIT(EXTI_MCUCR_REG, EXTI_ISC01_BIT);
            EXTI_MCUCR_REG |= ((u8)sense << EXTI_ISC00_BIT);
            break;

        case EXTI_INT1:
            /* ISC11:ISC10 in MCUCR - same 2-bit encoding as INT0. */
            CLR_BIT(EXTI_MCUCR_REG, EXTI_ISC10_BIT);
            CLR_BIT(EXTI_MCUCR_REG, EXTI_ISC11_BIT);
            EXTI_MCUCR_REG |= ((u8)sense << EXTI_ISC10_BIT);
            break;

        case EXTI_INT2:
            /* Single bit ISC2 in MCUCSR - edge only. */
            if (sense == EXTI_SENSE_FALLING)
            {
                CLR_BIT(EXTI_MCUCSR_REG, EXTI_ISC2_BIT);
            }
            else if (sense == EXTI_SENSE_RISING)
            {
                SET_BIT(EXTI_MCUCSR_REG, EXTI_ISC2_BIT);
            }
            else
            {
                /* LOW_LEVEL / ANY_CHANGE are not supported on INT2. */
                return E_NOK;
            }
            break;

        default:
            return E_NOK;
    }

    /* STEP 3: Return E_OK. */
    return E_OK;
}


STD_ReturnType EXTI_SetCallBack(EXTI_LineType line, EXTI_CallBackType callBack)
{
    /*
     * STEP 1: Validate line < EXTI_LINE_MAX and callBack != NULL (else E_NOK).
     * STEP 2: Store 'callBack' in EXTI_CallBacks[line].
     * STEP 3: Return E_OK.
     *
     * NOTE: Provide the three ISRs here so each fires its stored callback:
     *       ISR(INT0_vect){ if (EXTI_CallBacks[EXTI_INT0]) EXTI_CallBacks[EXTI_INT0](); }
     *       ISR(INT1_vect){ ... }   ISR(INT2_vect){ ... }
     */

    /* STEP 1: Validate line and callback pointer. */
    if ((line >= EXTI_LINE_MAX) || (callBack == NULL))
    {
        return E_NOK;
    }

    /* STEP 2: Store the callback in the matching slot. */
    EXTI_CallBacks[line] = callBack;

    /* STEP 3: Return E_OK. */
    return E_OK;
}


/* ---------------- Interrupt Service Routines ---------------- */
ISR(INT0_vect)
{
    if (EXTI_CallBacks[EXTI_INT0] != NULL)
    {
        EXTI_CallBacks[EXTI_INT0]();
    }
}

ISR(INT1_vect)
{
    if (EXTI_CallBacks[EXTI_INT1] != NULL)
    {
        EXTI_CallBacks[EXTI_INT1]();
    }
}

ISR(INT2_vect)
{
    if (EXTI_CallBacks[EXTI_INT2] != NULL)
    {
        EXTI_CallBacks[EXTI_INT2]();
    }
}


void EXTI_EnableGlobalInterrupt(void)
{
    /*
     * STEP 1: Set the I-bit (bit 7) of SREG:
     *         SET_BIT(EXTI_SREG_REG, EXTI_GLOBAL_INT_BIT);   // same as sei()
     */
    SET_BIT(EXTI_SREG_REG, EXTI_GLOBAL_INT_BIT);
}


void EXTI_DisableGlobalInterrupt(void)
{
    /*
     * STEP 1: Clear the I-bit (bit 7) of SREG:
     *         CLR_BIT(EXTI_SREG_REG, EXTI_GLOBAL_INT_BIT);   // same as cli()
     */
    CLR_BIT(EXTI_SREG_REG, EXTI_GLOBAL_INT_BIT);
}
