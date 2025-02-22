/**************************************************************************
 * @file        I2C.c
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       I2C driver for ATMEGA128 microcontroller.
 * @version     1.0.0
 * @date        2022-03-03
 * @features:   - I2C Master mode
 *              - I2C Slave mode
 *              - I2C Interrupt mode
 *              - I2C DMA mode
 *              - I2C Double Speed mode
 * @copyright   Copyright (c) 2022
 ***************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "I2C_reg.h"
#include "DIO.h"
#include "GIE.h"
#include "I2C.h"
#include "I2C_cfg.h"

/*------------------------------------------------------------------------*/
/*                                                                        */    
/*                          Global Variables                             */
/*                                                                        */
/*------------------------------------------------------------------------*/
void (*I2C_StcCallBack)(void);

/*------------------------------------------------------------------------*/
/*                                                                        */
/*                    PRIVATE Functions Prototypes                        */
/*                                                                        */
/*------------------------------------------------------------------------*/
static void I2C_SetClockPrescaler(void);
static void I2C_Enable(void);
static void I2C_Disable(void);
static void I2C_MasterInit(void);
static void I2C_SlaveInit(void);
static void I2C_SetMode(void);
static void I2C_SetDataOrder(void);
static void I2C_SetClockMode(void);

/*------------------------------------------------------------------------*/
/*                                                                        */
/*                          PUBLIC FUNCTIONS                              */
/*                                                                        */
/*------------------------------------------------------------------------*/

void I2C_Init(void) {
    /* Set I2C mode: master or slave */
    I2C_SetMode();

    /* Set I2C clock prescaler */ 
    I2C_SetClockPrescaler();

    /* Set I2C clock mode: CPOL, CPHA */
    I2C_SetClockMode();

    /* Set I2C data order: LSB or MSB first */
    I2C_SetDataOrder();

    /* Set I2C enable: SPE */
    I2C_Enable(); 
}

void I2C_SetCallBack(void (* const callback)(void)) {
    I2C_StcCallBack = callback;
}

void I2C_EnableInterrupt(void(* const callback)(void)) {
    GIE_Disable();

    I2C_SetCallBack(callback);
    BIT_SET(SPCR, I2CE);

    GIE_Enable();
}

void I2C_DisableInterrupt(void) {
    BIT_CLR(SPCR, I2CE);
}

ERROR_t I2C_SendByte(const u8_t data) {
    ERROR_t error = ERROR_OK;
    u8_t volatile fBuffer = 0;

    SPDR = data;                        /* Write data to the I2C data register */

    while(BIT_IS_CLEAR(SPSR, I2CF));    /* Wait until I2C transfer complete */

    /* Clear transmission complete flag by reading I2C Status register */
    fBuffer = SPSR; 					/* Read I2C Status register */
    fBuffer = SPDR; 					/* Then access I2C Data register */

    return error;
}

ERROR_t I2C_Available(STATE_t * const ptrToState) {
    ERROR_t error = ERROR_OK;
	
	*ptrToState = BIT_IS_SET(SPSR, I2CF);

    return error;
}

ERROR_t I2C_ReceiveByte(u8_t * const data) {
    ERROR_t error = ERROR_OK;
	u32_t u32Timeout = 10000000;
	
	/* Send garbage value	*/
	SPDR = NULL_BYTE;		

	/* Wait for transmission complete   */
    while(BIT_IS_CLEAR(SPSR, I2CF) && (--u32Timeout));               
    
	/* Read data from buffer, and clear the I2CF flag by accessing both SPSR, and SPDR registers	*/
	fBuffer = SPSR; 					/* Read I2C Status register */
    *data = SPDR;
	
    return error;
}

ERROR_t I2C_Read(u8_t * const data) {
    ERROR_t error = ERROR_OK;
	
    *data = SPDR;
	
    return error;
}

void I2C_TrancieveByte(const u8_t dataToSend, u8_t * const dataReceived) {   
    SPDR = dataToSend;  /* Send dummy data to receive data from slave */

    while(BIT_IS_CLEAR(SPSR, I2CF));      /* Wait for transmission complete   */
    *dataReceived = SPDR;             /* Read data from buffer            */
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*                          ISR FUNCTIONS                                 */
/*                                                                        */
/*------------------------------------------------------------------------*/
/* I2C_STC_ISR */
void __vector_17(void) __attribute__((signal));
void __vector_17(void) {
    GIE_Disable();

    if(I2C_StcCallBack != NULL) {
        I2C_StcCallBack();
    } else {
        /* DEBUG: No callback function defined */
    }

    BIT_SET(SPSR, I2CF);        /* Clear I2C interrupt flag */

    GIE_Enable();
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*                          PRIVATE FUNCTIONS                             */
/*                                                                        */
/*------------------------------------------------------------------------*/

/*********************************************************************
 * @brief Set Clock Prescaler for I2C module 
 *********************************************************************/
static void I2C_SetClockPrescaler(void) {
    switch(I2C_Config.clockDivider) {
        case I2C_PRESCALER_2:
            BIT_CLR(SPCR, SPR0);
            BIT_CLR(SPCR, SPR1);
            BIT_SET(SPSR, I2C2X);
            break;
        case I2C_PRESCALER_4:
            BIT_CLR(SPCR, SPR0);
            BIT_CLR(SPCR, SPR1);
            BIT_CLR(SPSR, I2C2X);
            break;
        case I2C_PRESCALER_8:
            BIT_SET(SPCR, SPR0);
            BIT_CLR(SPCR, SPR1);
            BIT_SET(SPSR, I2C2X);
            break;
        case I2C_PRESCALER_16:
            BIT_SET(SPCR, SPR0);
            BIT_CLR(SPCR, SPR1);
            BIT_CLR(SPSR, I2C2X);
            break;
        case I2C_PRESCALER_32:
            BIT_CLR(SPCR, SPR0);
            BIT_SET(SPCR, SPR1);
            BIT_SET(SPSR, I2C2X);
            break;
        case I2C_PRESCALER_64:
            BIT_SET(SPCR, SPR1);
            if(I2C_Config.doubleSpeed == I2C_DOUBLE_SPEED_ENABLE) {
                BIT_SET(SPCR, SPR0);
                BIT_SET(SPSR, I2C2X);
            }else {
                BIT_CLR(SPCR, SPR0);
                BIT_CLR(SPSR, I2C2X);
            }
            break;
        case I2C_PRESCALER_128:
            BIT_SET(SPCR, SPR1);
            BIT_SET(SPCR, SPR0);
            BIT_CLR(SPSR, I2C2X);
            break;
        default:
            break;
    }
        

}

/****************************************************************************
 * @brief Enable I2C module by setting the I2C Enable bit in the SPCR register
 ****************************************************************************/
static void I2C_Enable(void) {
    BIT_SET(SPCR, SPE);   
}

/****************************************************************************
 * @brief Disable I2C module by clearing the I2C Enable bit in the SPCR register
 ****************************************************************************/
static void I2C_Disable(void) {
    BIT_CLR(SPCR, SPE);
}

/****************************************************************************   
 * @brief Set the I2C in Master mode
 ****************************************************************************/
static void I2C_MasterInit(void) {
    /* Configure pins */
    DIO_InitPin(I2C_Config.connections.SS.pin  , I2C_Config.connections.SS.port    , DIO_OUTPUT , DIO_PULLUP_OFF);
    DIO_InitPin(I2C_Config.connections.MOSI.pin, I2C_Config.connections.MOSI.port  , DIO_OUTPUT , DIO_PULLUP_OFF);
    DIO_InitPin(I2C_Config.connections.MISO.pin, I2C_Config.connections.MISO.port  , DIO_INPUT  , DIO_PULLUP_OFF);
    DIO_InitPin(I2C_Config.connections.SCK.pin , I2C_Config.connections.SCK.port   , DIO_OUTPUT , DIO_PULLUP_OFF);

    /* Sending Falling Edge on the SS pin */
    DIO_SetPinValue(I2C_Config.connections.SS.pin, I2C_Config.connections.SS.port, HIGH);
    DIO_SetPinValue(I2C_Config.connections.SS.pin, I2C_Config.connections.SS.port, LOW);

    /* Set Master mode */
    BIT_SET(SPCR, MSTR);
}

/****************************************************************************
 * @brief Set the I2C in Slave mode by clearing the Master bit in the SPCR register
 *        and setting MISO as output and others as input
 ****************************************************************************/
static void I2C_SlaveInit(void) {
    /* Configure pins */
    DIO_InitPin(I2C_Config.connections.SS.pin  , I2C_Config.connections.SS.port    , DIO_INPUT  , DIO_PULLUP_OFF);
    DIO_InitPin(I2C_Config.connections.MOSI.pin, I2C_Config.connections.MOSI.port  , DIO_INPUT  , DIO_PULLUP_OFF);
    DIO_InitPin(I2C_Config.connections.MISO.pin, I2C_Config.connections.MISO.port  , DIO_OUTPUT , DIO_PULLUP_OFF);
    DIO_InitPin(I2C_Config.connections.SCK.pin , I2C_Config.connections.SCK.port   , DIO_INPUT  , DIO_PULLUP_OFF);

    /* Set Slave mode */
    BIT_CLR(SPCR, MSTR);

    #if 0   /* TEST */
    /* Clear the Master bit in the SPCR register */
    SPSR = SPSR;
    #endif

}

static void I2C_SetMode(void) {
    switch(I2C_Config.mode) {
        case I2C_MASTER:
            I2C_MasterInit();
            break;
        case I2C_SLAVE:
            I2C_SlaveInit();
            break;
        default:
            break;
    }
}

static void I2C_SetDataOrder(void) {
    switch(I2C_Config.dataOrder) {
        case I2C_DATA_ORDER_LSB_FIRST:
            BIT_SET(SPCR, DORD);
            break;
        case I2C_DATA_ORDER_MSB_FIRST:
            BIT_CLR(SPCR, DORD);
            break;
        default:
            break;
    }
}

static void I2C_SetClockMode(void) {
    switch(I2C_Config.clockMode) {
        case I2C_MODE0:
            BIT_CLR(SPCR, CPOL);
            BIT_CLR(SPCR, CPHA);
            break;
        case I2C_MODE1:
            BIT_CLR(SPCR, CPOL);
            BIT_SET(SPCR, CPHA);
            break;
        case I2C_MODE2:
            BIT_SET(SPCR, CPOL);
            BIT_CLR(SPCR, CPHA);
            break;
        case I2C_MODE3:
            BIT_SET(SPCR, CPOL);
            BIT_SET(SPCR, CPHA);
            break;
        default:
            break;
    }
}
