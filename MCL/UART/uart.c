#include "../../Service/STD_Types.h"
#include "../../Service/Bit_Math.h"
#include "uart_registers.h"
#include "uart_interface.h"

/* ================================================================================
 *  UART (USART) DRIVER - IMPLEMENTATION SKELETON
 *  ------------------------------------------------------------------------------
 *  Each body lists the ordered steps to implement the function. Replace the
 *  numbered comments with the actual register manipulation code.
 * ============================================================================== */

/*
 * Storage for the RX-complete callback.
 * TODO: static UART_RxCallBackType UART_RxCallBack = NULL;
 */


STD_ReturnType UART_Init(const UART_ConfigType *addConfig)
{
    /*
     * STEP 1: Validate the input.
     *   - If addConfig == NULL, return E_NOK.
     *
     * STEP 2: Compute the baud rate register value (normal speed, U2X = 0):
     *         UBRR = (UART_F_CPU / (16 * baudRate)) - 1
     *         Use a local uint16_h to hold the result.
     *
     * STEP 3: Load the baud value into the baud registers:
     *   - High byte: write UBRRH with URSEL = 0 (so the write targets UBRRH, not UCSRC),
     *                i.e. UART_UBRRH_REG = (u8)(UBRR >> 8) & 0x0F;   (URSEL bit stays 0)
     *   - Low  byte: UART_UBRRL_REG = (u8)UBRR;
     *
     * STEP 4: Configure the frame format in UCSRC. Because UCSRC shares the address
     *         with UBRRH, every write MUST set URSEL (bit 7) = 1. Build the value:
     *   - Set URSEL.
     *   - Async mode: clear UMSEL.
     *   - Parity  (UPM1:UPM0) from addConfig->parity.
     *   - Stop    (USBS)      from addConfig->stopBits.
     *   - Data    (UCSZ1:UCSZ0) from the low 2 bits of addConfig->dataSize; if
     *             9-bit is requested also set UCSZ2 in UCSRB (STEP 5).
     *   Then write the assembled byte to UART_UCSRC_REG in ONE store.
     *
     * STEP 5: Configure UCSRB:
     *   - Set UCSZ2 only for 9-bit data, otherwise clear it.
     *   - Enable transmitter (TXEN) and receiver (RXEN).
     *
     * STEP 6: Return E_OK.
     */
    return E_NOK;
}


STD_ReturnType UART_DeInit(void)
{
    /*
     * STEP 1: Clear TXEN and RXEN in UCSRB to disable the transmitter and receiver.
     * STEP 2: Clear RXCIE/TXCIE/UDRIE in UCSRB to disable USART interrupts.
     * STEP 3: Return E_OK.
     */
    return E_NOK;
}


STD_ReturnType UART_SendByte(uint8_h uint8Data)
{
    /*
     * STEP 1: Busy-wait until the data register is empty:
     *         while ( GET_BIT(UART_UCSRA_REG, UART_UDRE_BIT) == 0 ) { }
     * STEP 2: Write the byte: UART_UDR_REG = uint8Data;
     * STEP 3: Return E_OK.
     */
    return E_NOK;
}


STD_ReturnType UART_ReceiveByte(uint8_h *puint8Data)
{
    /*
     * STEP 1: Validate puint8Data != NULL (else E_NOK).
     * STEP 2: Busy-wait until a full frame has been received:
     *         while ( GET_BIT(UART_UCSRA_REG, UART_RXC_BIT) == 0 ) { }
     * STEP 3: Read the byte: *puint8Data = UART_UDR_REG;
     * STEP 4: Return E_OK.
     */
    return E_NOK;
}


STD_ReturnType UART_ReceiveByteNonBlocking(uint8_h *puint8Data)
{
    /*
     * STEP 1: Validate puint8Data != NULL (else E_NOK).
     * STEP 2: Check the RXC flag ONCE (no waiting):
     *         if RXC == 0, return E_NOK (nothing available).
     * STEP 3: Otherwise read *puint8Data = UART_UDR_REG and return E_OK.
     */
    return E_NOK;
}


STD_ReturnType UART_SendString(const uint8_h *pString)
{
    /*
     * STEP 1: Validate pString != NULL (else E_NOK).
     * STEP 2: Loop over the string until the '\0' terminator:
     *         for (i = 0; pString[i] != '\0'; i++) UART_SendByte(pString[i]);
     * STEP 3: Return E_OK.
     */
    return E_NOK;
}


STD_ReturnType UART_ReceiveString(uint8_h *buffer, uint16_h maxLength, uint8_h terminator)
{
    /*
     * STEP 1: Validate buffer != NULL and maxLength > 0 (else E_NOK).
     * STEP 2: Loop:
     *   - Read one byte with UART_ReceiveByte().
     *   - If it equals 'terminator', break.
     *   - Store it in buffer[index] and increment index.
     *   - Stop when index reaches (maxLength - 1) to leave room for '\0'.
     * STEP 3: Write buffer[index] = '\0' to NUL-terminate.
     * STEP 4: Return E_OK.
     */
    return E_NOK;
}


STD_ReturnType UART_SetRxCallBack(UART_RxCallBackType callBack)
{
    /*
     * STEP 1: Validate callBack != NULL (else E_NOK).
     * STEP 2: Store it: UART_RxCallBack = callBack;
     * STEP 3: Enable the RX-complete interrupt: SET_BIT(UART_UCSRB_REG, UART_RXCIE_BIT);
     * STEP 4: Return E_OK.
     *
     * NOTE: Provide the ISR here:
     *       ISR(USART_RXC_vect){ uint8_h d = UART_UDR_REG;
     *                            if (UART_RxCallBack) UART_RxCallBack(d); }
     */
    return E_NOK;
}
