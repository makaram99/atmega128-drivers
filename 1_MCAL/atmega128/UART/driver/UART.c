/**************************************************************************
 * @file        UART.c
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       UART driver for ATMEGA128 microcontroller.
 * @version     1.0.0
 * @date        2022-03-03
 * @copyright   Copyright (c) 2022
 **************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "UART_reg.h"
#include "GIE.h"
#include "UART.h"
#include "UART_cfg.h"

/*----------------------------------------------------------------------*/
/*                                                                      */
/*                        CALLBACK POINTERS                             */
/*                                                                      */
/*----------------------------------------------------------------------*/
static void (* volatile UART0_RX_Callback)(void)   = NULL;     /*!< Pointer to the RX callback function of UART0 */
static void (* volatile UART1_RX_Callback)(void)   = NULL;     /*!< Pointer to the RX callback function of UART1 */
static void (* volatile UART0_TX_Callback)(void)   = NULL;     /*!< Pointer to the TX callback function of UART0 */
static void (* volatile UART1_TX_Callback)(void)   = NULL;     /*!< Pointer to the TX callback function of UART1 */
static void (* volatile UART0_UDRE_Callback)(void) = NULL;     /*!< Pointer to the UDRE callback function of UART0 */
static void (* volatile UART1_UDRE_Callback)(void) = NULL;     /*!< Pointer to the UDRE callback function of UART1 */

/*----------------------------------------------------------------------*/
/*                                                                      */
/*                      PRIVATE FUNCTIONS PROTYPES                      */
/*                                                                      */
/*----------------------------------------------------------------------*/
static void UART_SetBaudRate(u32_t baudRate, UART_MODE_t mode, volatile u8_t * UBRRnH, volatile u8_t * UBRRnL);
static void UART0_SetBaudRate(u32_t baudRate);
static void UART1_SetBaudRate(u32_t baudRate);
static void UART_SetDataBits(UART_DATA_BITS_t dataBits, volatile u8_t * UCSRnC, volatile u8_t * UCSRnB);
static void UART0_SetDataBits(UART_DATA_BITS_t dataBits);
static void UART1_SetDataBits(UART_DATA_BITS_t dataBits);
static void UART_SetParity(UART_PARITY_t parity, volatile u8_t * UCSRnC);
static void UART0_SetParity(UART_PARITY_t parity);
static void UART1_SetParity(UART_PARITY_t parity);
static void UART_SetStopBits(UART_STOP_BITS_t stopBits, volatile u8_t * UCSRnC);
static void UART0_SetStopBits(UART_STOP_BITS_t stopBits);
static void UART1_SetStopBits(UART_STOP_BITS_t stopBits);
static void UART_SetMode(UART_MODE_t mode, volatile u8_t * UCSRnB);
static void UART0_SetMode(UART_MODE_t mode);
static void UART1_SetMode(UART_MODE_t mode);
static void UART_SetClockPolarity(UART_CLOCK_POLARITY_t polarity, volatile u8_t * UCSRnC, volatile u8_t * UCSRnB);
static void UART0_SetClockPolarity(UART_CLOCK_POLARITY_t polarity);
static void UART1_SetClockPolarity(UART_CLOCK_POLARITY_t polarity);
static void UART_SetSpeed(UART_MODE_t mode, volatile u8_t * UCSRnB);
static void UART0_SetSpeed(UART_MODE_t mode);
static void UART1_SetSpeed(UART_MODE_t mode);
static void UART_SendByte(u8_t data, volatile u8_t * UCSRnA, volatile u8_t * UDRn);
static void UART_Send9BitData(u16_t data, volatile u8_t * UCSRnA, volatile u8_t * UCSRnB, volatile u8_t * UDRn);
static void UART_SendByte_NoBlock(u8_t data, volatile u8_t * UDRn);
static void UART_Send9BitData_NoBlock(u16_t data, volatile u8_t * UCSRnB, volatile u8_t * UDRn);
static STATE_t UART_Available(volatile u8_t * UCSRnA);
static ERROR_t UART_ReceiveByte(u8_t * data, volatile u8_t * UCSRnA, volatile u8_t * UDRn);
static ERROR_t UART_Receive9BitData(u16_t * data, volatile u8_t * UCSRnA, volatile u8_t * UDRn);
static ERROR_t UART_ReceiveByte_NoBlock(u8_t * data, volatile u8_t * UCSRnA, volatile u8_t * UDRn);
static ERROR_t UART_Receive9BitData_NoBlock(u16_t * data, volatile u8_t * UCSRnA, volatile u8_t * UDRn);
static void UART_Flush(volatile u8_t * UCSRnA, ERROR_t (* UART_ReceiveByte)(u8_t * data));

/*--------------------------------------------------------------------*/
/*                                                                    */
/*                      PUBLIC FUNCTIONS PROTOTYPES                   */
/*                                                                    */
/*--------------------------------------------------------------------*/

/*----------------- Initialize UART Modules------------------*/
void UART0_Init(void) {
        /* Set baud rate */
         UART0_SetBaudRate(UART0_Configs.baud_rate);

        /* Set data bits: 5, 6, 7, 8 or 9 */
         UART0_SetDataBits(UART0_Configs.data_bits);

        /* Set parity: even, odd, disable */
         UART0_SetParity(UART0_Configs.parity);

        /* Set stop bits: 1 or 2 */
         UART0_SetStopBits(UART0_Configs.stop_bits);

        /* Set mode: asynchronous or synchronous */
         UART0_SetMode(UART0_Configs.mode);

        /* Set clock polarity: rising or falling */
         UART0_SetClockPolarity(UART0_Configs.clock_polarity);

        /* Set speed: normal or double speed */
         UART0_SetSpeed(UART0_Configs.mode);

        /* Enable UART */
        UART0_Enable();
}

void UART1_Init(void) {
        /* Set baud rate */
        UART1_SetBaudRate(UART1_Configs.baud_rate);

        /* Set data bits: 5, 6, 7, 8 or 9 */
        UART1_SetDataBits(UART1_Configs.data_bits);

        /* Set parity: even, odd, disable */
        UART1_SetParity(UART1_Configs.parity);

        /* Set stop bits: 1 or 2 */
        UART1_SetStopBits(UART1_Configs.stop_bits);

        /* Set mode: asynchronous or synchronous */
        UART1_SetMode(UART1_Configs.mode);

        /* Set clock polarity: rising or falling */
        UART1_SetClockPolarity(UART1_Configs.clock_polarity);

        /* Set speed: normal or double speed */
        UART1_SetSpeed(UART1_Configs.mode);

        /* Enable UART */
        UART1_Enable();
}

/*----------------- Enable UART Modules -------------------*/
void UART0_Enable(void) {
    BIT_SET(UCSR0B, RXEN);     /* Enable receiver */
    BIT_SET(UCSR0B, TXEN);     /* Enable transmitter */
}

void UART1_Enable(void) {
    BIT_SET(UCSR1B, RXEN);     /* Enable receiver */
    BIT_SET(UCSR1B, TXEN);     /* Enable transmitter */    
}

/*----------------- Disable UART Modules ------------------*/
void UART0_Disable(void) {
    BIT_CLR(UCSR0B, RXEN);     /* Enable receiver */
    BIT_CLR(UCSR0B, TXEN);     /* Enable transmitter */
}

void UART1_Disable(void) {
    BIT_CLR(UCSR1B, RXEN);     /* Enable receiver */
    BIT_CLR(UCSR1B, TXEN);     /* Enable transmitter */
}

/*----------------- Send Data (Synchronous) -------------------*/
void UART0_SendByte(const u8_t data) {
    UART_SendByte(data, &UCSR0A, &UDR0);
}

void UART1_SendByte(const u8_t data) {
    UART_SendByte(data, &UCSR1A, &UDR1);
}

void UART0_Send9BitData(const u16_t data) {
    UART_Send9BitData(data, &UCSR0A, &UCSR0B, &UDR0);
}

void UART1_Send9BitData(const u16_t data) {
    UART_Send9BitData(data, &UCSR1A, &UCSR1B, &UDR1);
}

/*----------------- Send Data (No Block) ------------------*/
void UART0_SendByte_NoBlock(const u8_t data) {
    UART_SendByte_NoBlock(data, &UDR0);
}

void UART1_SendByte_NoBlock(const u8_t data) {
    UART_SendByte_NoBlock(data, &UDR1);
}

void UART0_Send9BitData_NoBlock(const u16_t data) {
    UART_Send9BitData_NoBlock(data, &UCSR0B, &UDR0);
}

void UART1_Send9BitData_NoBlock(const u16_t data) {
    UART_Send9BitData_NoBlock(data, &UCSR1B, &UDR1);
}

/*----------------- Receive Data (Synchronous) ------------------*/
ERROR_t UART0_ReceiveByte(u8_t * const data) {
    return UART_ReceiveByte(data, &UCSR0A, &UDR0);
}

ERROR_t UART1_ReceiveByte(u8_t * const data) {
    return UART_ReceiveByte(data, &UCSR1A, &UDR1);
}

ERROR_t UART0_Receive9BitData(u16_t * const data) {
    return UART_Receive9BitData(data, &UCSR0A, &UDR0);
}

ERROR_t UART1_Receive9BitData(u16_t * const data) {
    return UART_Receive9BitData(data, &UCSR1A, &UDR1);
}

/*----------------- Receive Data (No Check) -----------------*/
ERROR_t UART0_ReceiveByte_NoBlock(u8_t * const data) {
    return UART_ReceiveByte_NoBlock(data, &UCSR0A, &UDR0);
}

ERROR_t UART1_ReceiveByte_NoBlock(u8_t * const data) {
    return UART_ReceiveByte_NoBlock(data, &UCSR1A, &UDR1);
}

ERROR_t UART0_Receive9BitData_NoBlock(u16_t * const data) {
    return UART_Receive9BitData_NoBlock(data, &UCSR0A, &UDR0);
}

ERROR_t UART1_Receive9BitData_NoBlock(u16_t * const data) {
    return UART_Receive9BitData_NoBlock(data, &UCSR1A, &UDR1);
}

/*----------------- Check if Data is Received ------------------*/
STATE_t UART0_Available(void) {
    return UART_Available(&UCSR0A);
}

STATE_t UART1_Available(void) {
    return UART_Available(&UCSR1A);
}

/********************************************************************************
 * @brief The receiver buffer FIFO will be flushed when the receiver is disabled, 
 *          i.e. the buffer will be emptied of its contents. 
 *        Unread data will be lost. If the buffer has to be flushed during normal 
 *          operation, due to for instance an error condition, 
 *          read the UDR I/O location until the RXC flag is cleared. 
 *******************************************************************************/
void UART0_Flush(void) {
    UART_Flush(&UCSR0A, UART0_ReceiveByte);
}

void UART1_Flush(void) {
    UART_Flush(&UCSR1A, UART1_ReceiveByte);
}

void UART0_RX_InterruptEnable(void(* const ptrCallback)(void)) {    
    GIE_Disable();                      /* Disable global interrupt while configurating */

    /*------------- Start of Configurations -------------*/
    BIT_SET(UCSR0B, RXCIE);        /* Enable RX Complete Interrupt */
    UART0_RX_Callback = ptrCallback;    /* Set the callback function */
    /*------------- End of Configurations ---------------*/

    GIE_Enable();                       /* Re-enable global interrupt */
}

void UART1_RX_InterruptEnable(void(* const ptrCallback)(void)) {    
    GIE_Disable();                      /* Disable global interrupt while configurating */

    /*------------- Start of Configurations -------------*/
    BIT_SET(UCSR1B, RXCIE);        /* Enable RX Complete Interrupt */
    UART1_RX_Callback = ptrCallback;    /* Set the callback function */
    /*------------- End of Configurations ---------------*/

    GIE_Enable();                       /* Re-enable global interrupt */
}

void UART1_TX_InterruptEnable(void(* const ptrCallback)(void)) {
    GIE_Disable();                      /* Disable global interrupt while configurating */

    /*------------- Start of Configurations -------------*/
    BIT_SET(UCSR1B, TXCIE);        /* Enable TX Complete Interrupt */
    UART1_TX_Callback = ptrCallback;    /* Set the callback function */
    /*------------- End of Configurations ---------------*/

    GIE_Enable();                       /* Re-enable global interrupt */
}

void UART0_TX_InterruptEnable(void(* const ptrCallback)(void)) {
    GIE_Disable();                      /* Disable global interrupt while configurating */

    /*------------- Start of Configurations -------------*/
    BIT_SET(UCSR0B, TXCIE);             /* Enable TX Complete Interrupt */
    UART0_TX_Callback = ptrCallback;    /* Set the callback function */
    /*------------- End of Configurations ---------------*/

    GIE_Enable();                       /* Re-enable global interrupt */
}

void UART0_UDRE_InterruptEnable(void(* const ptrCallback)(void)) {
    GIE_Disable();                      /* Disable global interrupt while configurating */

    /*------------- Start of Configurations -------------*/ 
    BIT_SET(UCSR0B, UDRIE);        /* Enable UDRE Interrupt */
    UART0_UDRE_Callback = ptrCallback;  /* Set the callback function */
    /*------------- End of Configurations ---------------*/

    GIE_Enable();                       /* Re-enable global interrupt */
}

void UART1_UDRE_InterruptEnable(void(* const ptrCallback)(void)) {
    GIE_Disable();                      /* Disable global interrupt while configurating */

    /*------------- Start of Configurations -------------*/ 
    BIT_SET(UCSR1B, UDRIE);        /* Enable UDRE Interrupt */
    UART1_UDRE_Callback = ptrCallback;  /* Set the callback function */
    /*------------- End of Configurations ---------------*/

    GIE_Enable();                       /* Re-enable global interrupt */
}

void UART0_RX_InterruptDisable(void) {
    BIT_CLR(UCSR0B, RXCIE);        /* Disable RX Complete Interrupt */
}

void UART1_RX_InterruptDisable(void) {
    BIT_CLR(UCSR1B, RXCIE);        /* Disable RX Complete Interrupt */
}

void UART0_TX_InterruptDisable(void) {
    BIT_CLR(UCSR0B, TXCIE);        /* Disable TX Complete Interrupt */
}

void UART1_TX_InterruptDisable(void) {
    BIT_CLR(UCSR1B, TXCIE);        /* Disable TX Complete Interrupt */
}

void UART0_UDRE_InterruptDisable(void) {
    BIT_CLR(UCSR0B, UDRIE);        /* Disable UDRE Interrupt */
}

void UART1_UDRE_InterruptDisable(void) {
    BIT_CLR(UCSR1B, UDRIE);        /* Disable UDRE Interrupt */
}

/*--------------------------------------------------------------------*/
/*                 UART PRIVATE FUNCTIONS PROTOTYPES                 */
/*--------------------------------------------------------------------*/
static void UART_SetBaudRate(const u32_t baudRate, const UART_MODE_t mode, volatile u8_t * const UBRRnH, volatile u8_t * const UBRRnL) {
    u16_t ubbrValue = 0;

    /* Calculate UBRR value */
    switch(mode) {
        case UART_MODE_ASYNCHRONOUS_NORMAL:
            ubbrValue = (u16_t)( ( ( (u32_t)F_CPU ) / ((u32_t)16 * baudRate) ) - 1);
            break;
        case UART_MODE_ASYNCHRONOUS_DOUBLE_SPEED:
            ubbrValue = (u16_t)( ( ( (u32_t)F_CPU ) / ((u32_t)8 * baudRate) ) - 1);
            break;
        case UART_MODE_SYNCHRONOUS_MASTER:
            ubbrValue = (u16_t)( ( ( (u32_t)F_CPU ) / ((u32_t)2 * baudRate) ) - 1);
            break;
        default:
            break;
    }
            
    /* Set UBRR value. UBRRH must be written before UBRRL */
    *UBRRnH = (u8_t)(ubbrValue >> 8);
    *UBRRnL = (u8_t)ubbrValue;
}

static void UART0_SetBaudRate(const u32_t baudRate) {
    UART_SetBaudRate(baudRate, UART0_Configs.mode, &UBRR0H, &UBRR0L);
}

static void UART1_SetBaudRate(const u32_t baudRate) {
    UART_SetBaudRate(baudRate, UART1_Configs.mode, &UBRR1H, &UBRR1L);
}

static void UART_SetDataBits(const UART_DATA_BITS_t dataBits, volatile u8_t * const UCSRnC, volatile u8_t * const UCSRnB) {
    switch(dataBits) {
        case UART_DATA_5_BITS:
            BIT_CLR(*UCSRnC, UCSZ0);
            BIT_CLR(*UCSRnC, UCSZ1);
            BIT_CLR(*UCSRnB, UCSZ2);
            break;
        case UART_DATA_6_BITS:
            BIT_SET(*UCSRnC, UCSZ0);
            BIT_CLR(*UCSRnC, UCSZ1);
            BIT_CLR(*UCSRnB, UCSZ2);
            break;
        case UART_DATA_7_BITS:
            BIT_CLR(*UCSRnC, UCSZ0);
            BIT_SET(*UCSRnC, UCSZ1);
            BIT_CLR(*UCSRnB, UCSZ2);
            break;
        case UART_DATA_8_BITS:
            BIT_SET(*UCSRnC, UCSZ0);
            BIT_SET(*UCSRnC, UCSZ1);
            BIT_CLR(*UCSRnB, UCSZ2);
            break;
        case UART_DATA_9_BITS:
            BIT_SET(*UCSRnC, UCSZ0);
            BIT_SET(*UCSRnC, UCSZ1);
            BIT_SET(*UCSRnB, UCSZ2);
            break;
        default:
            break;
    }
}

static void UART0_SetDataBits(const UART_DATA_BITS_t dataBits) {
    UART_SetDataBits(dataBits, &UCSR0C, &UCSR0B);
}

static void UART1_SetDataBits(const UART_DATA_BITS_t dataBits) {
    UART_SetDataBits(dataBits, &UCSR1C, &UCSR1B);
}

static void UART_SetParity(const UART_PARITY_t parity, volatile u8_t * const UCSRnC) {
    switch(parity) {
        case UART_PARITY_DISABLE:
            BIT_CLR(*UCSRnC, UPM0);
            BIT_CLR(*UCSRnC, UPM1);
            break;
        case UART_PARITY_EVEN:
            BIT_CLR(*UCSRnC, UPM0);
            BIT_SET(*UCSRnC, UPM1);
            break;
        case UART_PARITY_ODD:
            BIT_SET(*UCSRnC, UPM0);
            BIT_SET(*UCSRnC, UPM1);
            break;
        default:
            /* DEBUGGING */
            break;
    }
}

static void UART0_SetParity(const UART_PARITY_t parity) {
    UART_SetParity(parity, &UCSR0C);
}

static void UART1_SetParity(const UART_PARITY_t parity) {
    UART_SetParity(parity, &UCSR1C);
}

static void UART_SetStopBits(const UART_STOP_BITS_t stopBits, volatile u8_t * const UCSRnC) {
    switch(stopBits) {
        case UART_STOP_1_BIT:
            BIT_CLR(*UCSRnC, USBS);
            break;
        case UART_STOP_2_BIT:
            BIT_SET(*UCSRnC, USBS);
            break;
        default:
            break;
    }
}

static void UART0_SetStopBits(const UART_STOP_BITS_t stopBits) {
    UART_SetStopBits(stopBits, &UCSR0C);
}

static void UART1_SetStopBits(const UART_STOP_BITS_t stopBits) {
    UART_SetStopBits(stopBits, &UCSR1C);
}

static void UART_SetMode(const UART_MODE_t mode, volatile u8_t * const UCSRnB) {
    switch(mode) {
        case UART_MODE_ASYNCHRONOUS_NORMAL: case UART_MODE_ASYNCHRONOUS_DOUBLE_SPEED:
            BIT_CLR(*UCSRnB, UMSEL);
            break;
        case UART_MODE_SYNCHRONOUS_MASTER: case UART_MODE_SYNCHRONOUS_SLAVE:
            BIT_SET(*UCSRnB, UMSEL);
            break;
        default:
            break;
    }
}

static void UART0_SetMode(const UART_MODE_t mode) {
    UART_SetMode(mode, &UCSR0B);
}

static void UART1_SetMode(const UART_MODE_t mode) {
    UART_SetMode(mode, &UCSR1B);
}

static void UART_SetClockPolarity(const UART_CLOCK_POLARITY_t polarity, volatile u8_t * const UCSRnC, volatile u8_t * const UCSRnB) {
    switch(UART0_Configs.mode ) {
        case UART_MODE_ASYNCHRONOUS_NORMAL: case UART_MODE_ASYNCHRONOUS_DOUBLE_SPEED:
            BIT_CLR(*UCSRnC, UCPOL);
            break;
        case UART_MODE_SYNCHRONOUS_MASTER: case UART_MODE_SYNCHRONOUS_SLAVE:
            switch(polarity) {
                case UART_RISING_EDGE_CLOCK:
                    BIT_CLR(*UCSRnB, UCPOL);
                    break;
                case UART_FALLING_EDGE_CLOCK:
                    BIT_SET(*UCSRnB, UCPOL);
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

static void UART0_SetClockPolarity(const UART_CLOCK_POLARITY_t polarity) {
    UART_SetClockPolarity(polarity, &UCSR0C, &UCSR0B);
}

static void UART1_SetClockPolarity(const UART_CLOCK_POLARITY_t polarity) {
    UART_SetClockPolarity(polarity, &UCSR1C, &UCSR1B);
}

static void UART_SetSpeed(const UART_MODE_t mode, volatile u8_t * const UCSRnB) {
    switch(mode) {
        case UART_MODE_ASYNCHRONOUS_NORMAL:
            BIT_CLR(*UCSRnB, U2X);
            break;
        case UART_MODE_ASYNCHRONOUS_DOUBLE_SPEED:
            BIT_SET(*UCSRnB, U2X);
            break;
        default:
            break;
    }
}

static void UART0_SetSpeed(const UART_MODE_t mode) {
    UART_SetSpeed(mode, &UCSR0B);
}

static void UART1_SetSpeed(const UART_MODE_t mode) {
    UART_SetSpeed(mode, &UCSR1B);
}

/*----------------- Send Data (Synchronous) -------------------*/
static void UART_SendByte(const u8_t data, volatile u8_t * const UCSRnA, volatile u8_t * const UDRn) {
    ASSERT_PTR(UCSRnA);
    ASSERT_PTR(UDRn);

    /* Wait for empty transmit buffer: Synchronous */
    while( BIT_IS_CLEAR(*UCSRnA, UDRE) )
        ;

    /* Put data into buffer, sends the data */
    *UDRn = data;
}

static void UART_Send9BitData(const u16_t data, volatile u8_t * const UCSRnA, volatile u8_t * const UCSRnB, volatile u8_t * const UDRn) {
    ASSERT_PTR(UCSRnA);
    ASSERT_PTR(UCSRnB);
    ASSERT_PTR(UDRn);
    
    /* Wait for empty transmit buffer: Synchronous */
    while(BIT_IS_CLEAR(*UCSRnA, UDRE));

    /* Put 9th bit into buffer: Must be written before the data register */
    if(data & 0x0100) {     /* If 9th bit is 1 */
        BIT_SET(*UCSRnB, TXB8);
    }else {
        BIT_CLR(*UCSRnB, TXB8);
    }

    /* Put data into buffer, sends the data */
    *UDRn = (u8_t)(data & 0x00FF);
}

/*----------------- Send Data (No Check) ------------------*/
static void UART_SendByte_NoBlock(const u8_t data, volatile u8_t * const UDRn) {
    ASSERT_PTR(UDRn);

    /* Put data into buffer, sends the data */
    *UDRn = data;
}

static void UART_Send9BitData_NoBlock(const u16_t data, volatile u8_t * const UCSRnB, volatile u8_t * const UDRn) {
    ASSERT_PTR(UCSRnB);
    ASSERT_PTR(UDRn);
    
    /* Put 9th bit into buffer: Must be written before the data register */
    if(data & 0x0100) {     /* If 9th bit is 1 */
        BIT_SET(*UCSRnB, TXB8);
    }else {
        BIT_CLR(*UCSRnB, TXB8);
    }

    /* Put data into buffer, sends the data */
    *UDRn = (u8_t)(data & 0x00FF);
}

/*----------------- Check if Data is Received ------------------*/
static STATE_t UART_Available(volatile u8_t * const UCSRnA) {
    STATE_t state = LOW;

    ASSERT_PTR(UCSRnA);

    /* Check if data is available in receive buffer */
    if(BIT_IS_SET(*UCSRnA, RXC)) {
        state = HIGH;
    }else {
        state = LOW;
    }

    return state;
}

/*----------------- Receive Data (Synchronous) ------------------*/
static ERROR_t UART_ReceiveByte(u8_t * const data, volatile u8_t * const UCSRnA, volatile u8_t * const UDRn) {
    ERROR_t error = ERROR_OK;

    ASSERT_PTR(UCSRnA);
    ASSERT_PTR(UDRn);

    /* Wait for data to be received */
    while( BIT_IS_CLEAR(*UCSRnA, RXC) ) 
        ;

    /* Check for errors. Must be checked before reading the data register */
    if( BIT_IS_SET(*UCSRnA, FE) || BIT_IS_SET(*UCSRnA, DOR) || BIT_IS_SET(*UCSRnA, UPE)) {
        error = ERROR_NOK;
    }else {
        error = ERROR_OK;
    }

    /* Get data from buffer */
    *data = *UDRn;
    /* Reading data register clears the receive complete flag. So, no need to clear it again */

    return error;
}

static ERROR_t UART_Receive9BitData(u16_t * const data, volatile u8_t * const UCSRnA, volatile u8_t * const UDRn) {
    ERROR_t error = ERROR_OK;

    ASSERT_PTR(UCSRnA);
    ASSERT_PTR(UDRn);

    /* Wait for data to be received */
    while(BIT_IS_CLEAR(*UCSRnA, RXC) )
        ;

    /* Check for errors. Must be checked before reading the data register */
    if( BIT_IS_SET(*UCSRnA, FE) || BIT_IS_SET(*UCSRnA, DOR) || BIT_IS_SET(*UCSRnA, UPE)) {
        error = ERROR_NOK;
    }else {
        error = ERROR_OK;
    }

    /* Get 9th bit from buffer */
    if(BIT_IS_SET(UCSR0B, RXB8)) {
        *data = (u16_t)(*UDRn) | 0x0100;   /* Must be read before the data register */
    }else {
        *data = (u16_t)(*UDRn);
    }

    return error;
}

/*----------------- Receive Data (No Check) -----------------*/
static ERROR_t UART_ReceiveByte_NoBlock(u8_t * const data, volatile u8_t * const UCSRnA, volatile u8_t * const UDRn) {
    ERROR_t error = ERROR_OK;
    
    ASSERT_PTR(UCSRnA);
    ASSERT_PTR(UDRn);

    /* Check for errors. Must be checked before reading the data register */
    if( BIT_IS_SET(*UCSRnA, FE) || BIT_IS_SET(*UCSRnA, DOR) || BIT_IS_SET(*UCSRnA, UPE)) {
        error = ERROR_NOK;
    }else {
        error = ERROR_OK;
    }

    /* Get data from buffer */
    *data = *UDRn;
    /* Reading data register clears the receive complete flag. So, no need to clear it again */

    return error;
}

static ERROR_t UART_Receive9BitData_NoBlock(u16_t * const data, volatile u8_t * const UCSRnA, volatile u8_t * const UDRn) {
    ERROR_t error = ERROR_OK;

    ASSERT_PTR(UCSRnA);
    ASSERT_PTR(UDRn);

    /* Check for errors. Must be checked before reading the data register */
    if( BIT_IS_SET(*UCSRnA, FE) || BIT_IS_SET(*UCSRnA, DOR) || BIT_IS_SET(*UCSRnA, UPE)) {
        error = ERROR_NOK;
    }else {
        error = ERROR_OK;
    }

    /* Get 9th bit from buffer */
    if(BIT_IS_SET(UCSR0B, RXB8)) {
        *data = (u16_t)(*UDRn) | 0x0100;   /* Must be read before the data register */
    }else {
        *data = (u16_t)(*UDRn);
    }

    return error;
}

/*----------------- Receive Data (Interrupt) -----------------*/


/*----------------- Flush Receive Buffer ------------------*/
static void UART_Flush(volatile u8_t *UCSRnA, ERROR_t (* const UART_ReceiveByte)(u8_t * const data)) {
    u8_t dummy;

    ASSERT_PTR(UCSRnA);
    ASSERT_PTR(UART_ReceiveByte);
    
    while(BIT_IS_SET(*UCSRnA, RXC) ) {
        UART_ReceiveByte(&dummy);
    }
}

/*----------------------------------------------------------------------*/
/*                          ISR FUNCTIONS                               */
/*----------------------------------------------------------------------*/
/* UART0_RX_ISR */
void __vector_18(void) __attribute__((signal));
void __vector_18(void) {

    GIE_Disable();

    if(NULL != UART0_RX_Callback) {
        UART0_RX_Callback();
    }

    /* Clear the RXC flag */
    BIT_SET(UCSR0A, RXC);

    GIE_Enable();
}

/* UART0_TX_ISR */
void __vector_20(void) __attribute__((signal));
void __vector_20(void) {
    GIE_Disable();

    if(UART0_TX_Callback != NULL) {
        UART0_TX_Callback();
    }

    /* Clear the TXC flag */
    BIT_SET(UCSR0A, TXC);

    GIE_Enable();
}

/* UART0_UDRE_ISR */
void __vector_19(void) __attribute__((signal));
void __vector_19(void) {
    GIE_Disable();

    if(UART0_UDRE_Callback != NULL) {
        UART0_UDRE_Callback();
    }

    /* Clear the UDRE flag */
    BIT_CLR(UCSR0A, UDRE);

    GIE_Enable();
}

/* UART1_RX_ISR */
void __vector_30(void) __attribute__((signal));
void __vector_30(void) {
    GIE_Disable();

    if(NULL != UART1_RX_Callback) {
        UART1_RX_Callback();
    }

    /* Clear the RXC flag */
    BIT_SET(UCSR1A, RXC);

    GIE_Enable();
}

/* UART1_TX_ISR */
void __vector_32(void) __attribute__((signal));
void __vector_32(void) {
    GIE_Disable();

    if(UART1_TX_Callback != NULL) {
        UART1_TX_Callback();
    }

    /* Clear the TXC flag */
    BIT_SET(UCSR1A, TXC);

    GIE_Enable();
}

/* UART1_UDRE_ISR */
void __vector_31(void) __attribute__((signal));
void __vector_31(void) {
    GIE_Disable();

    if(UART1_UDRE_Callback != NULL) {
        UART1_UDRE_Callback();
    }

    /* Clear the UDRE flag */
    BIT_CLR(UCSR1A, UDRE);

    GIE_Enable();
}
