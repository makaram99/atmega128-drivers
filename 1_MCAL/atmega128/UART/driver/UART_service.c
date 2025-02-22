/**************************************************************************
 * @file        UART_services.c
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       UART Services
 * @version     1.0.0
 * @date        2022-03-06
 * @copyright   Copyright (c) 2022
 **************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MATH.h"
#include "UART.h"
#include "UART_service.h"

/*--------------------------------------------------------------------*/
/*                     UART Private Functions Prototypes              */
/*--------------------------------------------------------------------*/
static void UART_SendString(u8_t * const string, void (* const UART_SendByte)(const u8_t data));
static void UART_Send9BitString(const u16_t * const string, void (* const UART_Send9BitData)(const u16_t data));
static void ISR_UART_SendString_Asynchronous(void);
static void UART_SendString_Asynchronous(const u8_t * const string, void (* const UART_SendByte_NoBlock)(const u8_t data), void (* const UART_TX_InterruptEnable)( void (* const ptrCallback)(void) ) );
static void UART_Send9BitString_Asynchronous(const u8_t * const string, void (* const UART_Send9BitData_NoBlock)(const u16_t data));
static void UART_SendString_Checksum(const u8_t * const string, void (* const UART_SendByte)(const u8_t data));
static void UART_SendInteger(s32_t integer, void (* const UART_SendByte)(const u8_t data));
static void UART_SendFloat(float number, const u8_t precision, void (* const UART_SendByte)(const u8_t data));
static ERROR_t UART_ReceiveString(u8_t * const string, ERROR_t (* const UART_ReceiveByte)(u8_t * const data));
static ERROR_t UART_Receive9BitString(u16_t * const string, ERROR_t (* const UART_Receive9BitData)(u16_t * const data));
static void UART_ReceiveString_Asynchronous_Callback(void);
static void UART_ReceiveString_Asynchronous(const u8_t * const string, ERROR_t (* const UART_ReceiveByte_NoBlock)(u8_t * const data), void (* const UART_RX_InterruptEnable)( void (* const ptrCallback)(void) ) );
static ERROR_t UART_ReceiveString_Checksum(u8_t * const string, ERROR_t (* const UART_ReceiveByte)(u8_t * const data));

/*--------------------------------------------------------------------*/
/*                          UART Service                              */
/*--------------------------------------------------------------------*/
/*--------- Send String (Synchronous) ------------*/
void UART0_SendString(const u8_t * const string) {
    UART_SendString(string, UART0_SendByte);
}

void UART1_SendString(const u8_t * const string) {
    UART_SendString(string, UART1_SendByte);
}

void UART0_Send9BitString(const u16_t * const string) {
    UART_Send9BitString(string, UART0_Send9BitData);
}

void UART1_Send9BitString(const u16_t * const string) {
    UART_Send9BitString(string, UART1_Send9BitData);
}

/*--------- Send String (Asynchronous) ------------*/
void UART0_SendString_Asynchronous(const u8_t * const string) {
    UART_SendString_Asynchronous(string, UART0_SendByte_NoBlock, UART0_TX_InterruptEnable);
}

void UART1_SendString_Asynchronous(const u8_t * const string) {
    UART_SendString_Asynchronous(string, UART1_SendByte_NoBlock, UART1_TX_InterruptEnable);
}

/* TODO: Not implemented */
void UART0_Send9BitString_Asynchronous(const u16_t * const string) {
    
}

/* TODO: Not implemented */
void UART1_Send9BitString_Asynchronous(const u16_t * const string) {

}

/*-- Send String (Synchronous) with Checksum protection --*/
void UART0_SendString_Checksum(const u8_t * const string) {
    UART_SendString_Checksum(string, UART0_SendByte);
}

void UART1_SendString_Checksum(const u8_t * const string) {
    UART_SendString_Checksum(string, UART1_SendByte);
}

/*--------- Send Integer (Synchronous) ------------*/
void UART0_SendInteger(s32_t integer) {
    UART_SendInteger(integer, UART0_SendByte);
}

void UART1_SendInteger(s32_t integer) {
    UART_SendInteger(integer, UART1_SendByte);
}

/*--------- Send Float (Synchronous) ------------*/
void UART0_SendFloat(const float number, const u8_t precision) {
    UART_SendFloat(number, precision, UART0_SendByte);
}

void UART1_SendFloat(const float number, const u8_t precision) {
    UART_SendFloat(number, precision, UART1_SendByte);
}

/*--------- Receive String (Synchronous) ------------*/
ERROR_t UART0_ReceiveString(u8_t * const string) {
    return UART_ReceiveString(string, UART0_ReceiveByte);
}

ERROR_t UART1_ReceiveString(u8_t * const string) {
    return UART_ReceiveString(string, UART1_ReceiveByte);
}

ERROR_t UART0_Receive9BitString(u16_t * const string) {
    return UART_Receive9BitString(string, UART0_Receive9BitData);
}

ERROR_t UART1_Receive9BitString(u16_t * const string) {
    return UART_Receive9BitString(string, UART1_Receive9BitData);
}

/*--------- Receive String (Synchronous) with Checksum protection --*/
ERROR_t UART0_ReceiveString_Checksum(u8_t * const string) {
    return UART_ReceiveString_Checksum(string, UART0_ReceiveByte);
}

ERROR_t UART1_ReceiveString_Checksum(u8_t * const string) {
    return UART_ReceiveString_Checksum(string, UART1_ReceiveByte);
}


/*--------------------------------------------------------------------*/
/*                          PRIVATE FUNCTIONS                         */
/*--------------------------------------------------------------------*/
/*--------- Send String (Synchronous) ------------*/
static void UART_SendString(const u8_t * const string, void (* const UART_SendByte)(const u8_t data)){
    u8_t i = 0;

    /* Send string until null */
    while(string[i] != NULL_BYTE) {
        UART_SendByte(string[i]);
        ++i;
    }

    UART_SendByte(NULL_BYTE);
}

static void UART_Send9BitString(const u16_t * const string, void (* const UART_Send9BitData)(const u16_t data)){
    u8_t i = 0;

    /* Send string until null */
    while(string[i] != NULL_BYTE) {
        UART_Send9BitData(string[i]);
        ++i;
    }

    UART_Send9BitData(NULL_BYTE);
}

/*--------- Send String (Asynchronous) ------------*/
static const u8_t * volatile asynchronousString_Send = NULL;
static void (* volatile asynchronous_UART_SendByte_NoBlock)(const u8_t data);

/*
    TODO: Fix the following two functions 
        --> they send the string in correctly only one time, then the first and the 
            second character are swapped. Test the following code:
            while(1) {
                UART0_SendString_Asynchronous("UART0\r");
                _delay_ms(1000);
            }

        --> IF calling this function more than once without appropriate delay, 
            there will be a problem, test the following code:
            UART0_SendString_Asynchronous("UART0\r");
            UART0_SendString_Asynchronous("UART1\r");
            UART0_SendString_Asynchronous("UART2\r");
*/
static void ISR_UART_SendString_Asynchronous(void){
    static u8_t i = 1;

    /* Send string until null */
    if(asynchronousString_Send[i] != NULL_BYTE) {
        asynchronous_UART_SendByte_NoBlock(asynchronousString_Send[i]);
        ++i;
    }else {
        /* Disabling interrupt before sending null byte */
        if(UART0_SendByte_NoBlock == asynchronous_UART_SendByte_NoBlock) {
            UART0_TX_InterruptDisable();
        } else if(UART1_SendByte_NoBlock == asynchronous_UART_SendByte_NoBlock) {
            UART1_TX_InterruptDisable();
        }
        
        /* Send null byte, then reset i */
        asynchronous_UART_SendByte_NoBlock(NULL_BYTE);
        i = 1;
    }
}

static void UART_SendString_Asynchronous(const u8_t * const string, void (* const UART_SendByte_NoBlock)(const u8_t data), void (* const UART_TX_InterruptEnable)( void (* const ptrCallback)(void) ) ){
    asynchronousString_Send = string;
    asynchronous_UART_SendByte_NoBlock = UART_SendByte_NoBlock;

    UART_TX_InterruptEnable(ISR_UART_SendString_Asynchronous);

    /* Send the first byte in string synchronously to avoid corruption of current data that is being sent */
    if(UART_SendByte_NoBlock == UART0_SendByte_NoBlock) {
        UART0_SendByte(asynchronousString_Send[0]);
    } else if(UART_SendByte_NoBlock == UART1_SendByte_NoBlock) {
        UART1_SendByte(asynchronousString_Send[0]);
    }    
}

/* TODO: Implement 9-bit asynchronous */
static void UART_Send9BitString_Asynchronous(const u8_t * const string, void (* const UART_Send9BitData_NoBlock)(const u16_t data)){
    u8_t i = 0;

    /* Send string until null */
    while(string[i] != NULL_BYTE) {
        if(UART_Send9BitData_NoBlock == UART0_Send9BitData_NoBlock) {
            UART0_Send9BitData(string[i]);
        } else if(UART_Send9BitData_NoBlock == UART1_Send9BitData_NoBlock) {
            UART1_Send9BitData(string[i]);
        }

        ++i;
    }

    /* Send null byte */
    if(UART_Send9BitData_NoBlock == UART0_Send9BitData_NoBlock) {
        UART0_Send9BitData(NULL_BYTE);
    } else if(UART_Send9BitData_NoBlock == UART1_Send9BitData_NoBlock) {
        UART1_Send9BitData(NULL_BYTE);
    }
}

/*-- Send String (Synchronous) with Checksum protection --*/
static void UART_SendString_Checksum(const u8_t * const string, void (* const UART_SendByte)(const u8_t data)) {
    u8_t i = 0;
    u16_t checksum = 0;

    /* Calculating Number of elements and checksum */
    i = 0;
    while(string[i] != NULL_BYTE) {
        checksum += string[i];
        ++i;
    }

    /* Sending # of elements    */
    UART_SendByte(i);

    /* Send string until null */
    i = 0;
    while(string[i] != NULL_BYTE) {
        UART_SendByte(string[i]);
        ++i;
    }

    /* Send checksum: MSB first */
    UART_SendByte( (u8_t)(checksum >> 8) );
    UART_SendByte( (u8_t)checksum );
}

/*--------- Send Integer (Synchronous) ------------*/
static void UART_SendInteger(s32_t integer, void (* const UART_SendByte)(const u8_t data)) {
    u8_t i = 0, remainder, string[10];

	if(integer < 0) {
		UART_SendByte('-');    /* Send negative sign */
		integer = -integer;     /* Make integer positive */
	}
	
	do{
		remainder = integer % 10;
		integer /= 10;
		
		string[i] = remainder + '0';
        ++i;
	} while(integer);	/* do while integer is used to send 0 */

    /* Send string until null */
    while(i--) {
        UART_SendByte(string[i]);
    }
}

/*--------- Send Float (Synchronous) ------------*/
static void UART_SendFloat(float number, const u8_t precision, void (* const UART_SendByte)(const u8_t data)) {
    f32_t fraction;
    u32_t integer;
    u8_t i = 0;

    /*!< Send negative sign if the number is negative */
    if( IS_NEGATIVE(number) ) {
        UART_SendByte('-');
        ABS(number);
    }

    integer = (u8_t)number;               /*!< Get integer part */
    fraction = FRACTION(number);        /*!< Get fractional part */
    
    /*!< Shift the fraction part with a number of bits equal to the precision */
    for(i = 0; i < precision; ++i) {
        fraction *= 10.0f;
    }
    fraction = (u8_t)fraction;     /*!< Remove the fraction integer part */

    UART_SendByte(integer);             /*!< Send integer part */
    UART_SendByte('.');                 /*!< Send decimal point */   
    UART_SendByte((u8_t)fraction);        /*!< Send fractional part */
}

/*--------- Receive String (Synchronous) ------------*/
static ERROR_t UART_ReceiveString(u8_t * const string, ERROR_t (* const UART_ReceiveByte)(u8_t * const data)) {
    ERROR_t error = ERROR_OK;
    u8_t i = 0;

    /* Receive string */
    error = UART_ReceiveByte(&string[i]);
    while(string[i] != '#') {
        if(error == ERROR_NOK) {
            break;
        }
        ++i;

        /* Receive byte */
        error = UART_ReceiveByte(&string[i]);
    }

    /* Setting null byte at the end of the string */
    string[i] = NULL_BYTE;

    return error;
}

static ERROR_t UART_Receive9BitString(u16_t * const string, ERROR_t (* const UART_Receive9BitData)(u16_t * const data)) {
    ERROR_t error = ERROR_OK;
    u8_t i = 0;

    /* Receive string */
    UART_Receive9BitData(&string[i]);
    while(string[i] != '#') {
        if(error == ERROR_NOK) {
            break;
        } else {
            /* do nothing */
        }

        ++i;
        error = UART_Receive9BitData(&string[i]);
    }

    /* Setting null byte at the end of the string */
    string[i] = NULL_BYTE;

    return error;
}

/*--------- Receive String (Asynchronous) ------------*/
static u8_t * asynchronousString_Receive = NULL;
static ERROR_t (*asynchronous_UART_ReceiveByte_NoBlock)(u8_t * const data);

/* TODO: Not tested */
static void UART_ReceiveString_Asynchronous_Callback(void){
    static u8_t i = 1;

    asynchronous_UART_ReceiveByte_NoBlock(&asynchronousString_Receive[i]);
    
    /* Receive string until null */
    if(asynchronousString_Receive[i] != NULL_BYTE) {
        ++i;
    }else {
        /* Disabling interrupt before sending null byte */
        if(asynchronous_UART_ReceiveByte_NoBlock == UART0_ReceiveByte_NoBlock) {
            UART0_RX_InterruptDisable();
        } else if(asynchronous_UART_ReceiveByte_NoBlock == UART1_ReceiveByte_NoBlock) {
            UART1_RX_InterruptDisable();
        }
        
        /* Reset i */
        i = 1;
    }
}

/* TODO: Not tested */
static void UART_ReceiveString_Asynchronous(const u8_t * const string, ERROR_t (* const UART_ReceiveByte_NoBlock)(u8_t * const data), void (* const UART_RX_InterruptEnable)( void (* const ptrCallback)(void) ) ){
    UART_RX_InterruptEnable(UART_ReceiveString_Asynchronous_Callback);
    
    asynchronous_UART_ReceiveByte_NoBlock = UART_ReceiveByte_NoBlock;

    asynchronousString_Receive = (u8_t *)string;

    /* Receive the first byte in string synchronously to avoid corruption of current data that is being  */
    if(asynchronous_UART_ReceiveByte_NoBlock == UART0_ReceiveByte_NoBlock) {
        UART0_ReceiveByte(&asynchronousString_Receive[0]);
    } else if(asynchronous_UART_ReceiveByte_NoBlock == UART1_ReceiveByte_NoBlock) {
        UART1_ReceiveByte(&asynchronousString_Receive[0]);
    }
}

/*--------- Receive String (Synchronous) with Checksum protection --*/
static ERROR_t UART_ReceiveString_Checksum(u8_t * const string, ERROR_t (* const UART_ReceiveByte)(u8_t * const data)) {
    ERROR_t error = ERROR_OK;
    u16_t checksumCalculated = 0;
    u16_t checksumReceived = 0;
    u8_t  size = 0;

    /* Receive Size of incoming string */
    UART_ReceiveByte(&size);

    /* Receive string */
    for(u8_t i = 0; i < size; ++i) {
        UART_ReceiveByte(&string[i]);

        /* Calculating checksum */
        checksumCalculated += string[i];
    }

    /* Setting null byte at the end of the string */
    string[size] = NULL_BYTE;

    /* Receive checksum: MSB first */
    UART_ReceiveByte( (u8_t *)&checksumReceived + 1 );
    UART_ReceiveByte( (u8_t *)&checksumReceived );

    /* Checking checksum */
    if(checksumCalculated != checksumReceived) {
        error = ERROR_NOK;
    }
    
    return error;
}
