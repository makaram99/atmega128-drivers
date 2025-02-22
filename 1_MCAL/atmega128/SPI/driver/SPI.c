/**************************************************************************
 * @file        SPI.c
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       SPI driver for ATMEGA128 microcontroller.
 * @version     1.0.0
 * @date        2022-03-03
 * @features:   - SPI Master mode
 *              - SPI Slave mode
 *              - SPI Interrupt mode
 *              - SPI DMA mode
 *              - SPI Double Speed mode
 * @copyright   Copyright (c) 2022
 ***************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "SPI_reg.h"
#include "DIO.h"
#include "GIE.h"
#include "SPI.h"
#include "SPI_cfg.h"

/*------------------------------------------------------------------------*/
/*                                                                        */    
/*                          Global Variables                             */
/*                                                                        */
/*------------------------------------------------------------------------*/
void (*SPI_StcCallBack)(void);

/*------------------------------------------------------------------------*/
/*                                                                        */
/*                    PRIVATE Functions Prototypes                        */
/*                                                                        */
/*------------------------------------------------------------------------*/
static void SPI_SetClockPrescaler(void);
static void SPI_Enable(void);
static void SPI_Disable(void);
static void SPI_MasterInit(void);
static void SPI_SlaveInit(void);
static void SPI_SetMode(void);
static void SPI_SetDataOrder(void);
static void SPI_SetClockMode(void);

/*------------------------------------------------------------------------*/
/*                                                                        */
/*                          PUBLIC FUNCTIONS                              */
/*                                                                        */
/*------------------------------------------------------------------------*/

void SPI_Init(void) {
    /* Set SPI mode: master or slave */
    SPI_SetMode();

    /* Set SPI clock prescaler */ 
    SPI_SetClockPrescaler();

    /* Set SPI clock mode: CPOL, CPHA */
    SPI_SetClockMode();

    /* Set SPI data order: LSB or MSB first */
    SPI_SetDataOrder();

    /* Set SPI enable: SPE */
    SPI_Enable(); 
}

void SPI_SetCallBack(void (* const callback)(void)) {
    SPI_StcCallBack = callback;
}

void SPI_EnableInterrupt(void(* const callback)(void)) {
    GIE_Disable();

    SPI_SetCallBack(callback);
    BIT_SET(SPCR, SPIE);

    GIE_Enable();
}

void SPI_DisableInterrupt(void) {
    BIT_CLR(SPCR, SPIE);
}

ERROR_t SPI_SendByte(const u8_t data) {
    ERROR_t error = ERROR_OK;
    u8_t volatile fBuffer = 0;

    SPDR = data;                        /* Write data to the SPI data register */

    while(BIT_IS_CLEAR(SPSR, SPIF));    /* Wait until SPI transfer complete */

    /* Clear transmission complete flag by reading SPI Status register */
    fBuffer = SPSR; 					/* Read SPI Status register */
    fBuffer = SPDR; 					/* Then access SPI Data register */

    return error;
}

ERROR_t SPI_Available(STATE_t * const ptrToState) {
    ERROR_t error = ERROR_OK;
	
	*ptrToState = BIT_IS_SET(SPSR, SPIF);

    return error;
}

ERROR_t SPI_ReceiveByte(u8_t * const data) {
    ERROR_t error = ERROR_OK;
	u32_t u32Timeout = 10000000;
	
	/* Send garbage value	*/
	SPDR = NULL_BYTE;		

	/* Wait for transmission complete   */
    while(BIT_IS_CLEAR(SPSR, SPIF) && (--u32Timeout));               
    
	/* Read data from buffer, and clear the SPIF flag by accessing both SPSR, and SPDR registers	*/
	fBuffer = SPSR; 					/* Read SPI Status register */
    *data = SPDR;
	
    return error;
}

ERROR_t SPI_Read(u8_t * const data) {
    ERROR_t error = ERROR_OK;
	
    *data = SPDR;
	
    return error;
}

void SPI_TrancieveByte(const u8_t dataToSend, u8_t * const dataReceived) {   
    SPDR = dataToSend;  /* Send dummy data to receive data from slave */

    while(BIT_IS_CLEAR(SPSR, SPIF));      /* Wait for transmission complete   */
    *dataReceived = SPDR;             /* Read data from buffer            */
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*                          ISR FUNCTIONS                                 */
/*                                                                        */
/*------------------------------------------------------------------------*/
/* SPI_STC_ISR */
void __vector_17(void) __attribute__((signal));
void __vector_17(void) {
    GIE_Disable();

    if(SPI_StcCallBack != NULL) {
        SPI_StcCallBack();
    } else {
        /* DEBUG: No callback function defined */
    }

    BIT_SET(SPSR, SPIF);        /* Clear SPI interrupt flag */

    GIE_Enable();
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*                          PRIVATE FUNCTIONS                             */
/*                                                                        */
/*------------------------------------------------------------------------*/

/*********************************************************************
 * @brief Set Clock Prescaler for SPI module 
 *********************************************************************/
static void SPI_SetClockPrescaler(void) {
    switch(SPI_Config.clockDivider) {
        case SPI_PRESCALER_2:
            BIT_CLR(SPCR, SPR0);
            BIT_CLR(SPCR, SPR1);
            BIT_SET(SPSR, SPI2X);
            break;
        case SPI_PRESCALER_4:
            BIT_CLR(SPCR, SPR0);
            BIT_CLR(SPCR, SPR1);
            BIT_CLR(SPSR, SPI2X);
            break;
        case SPI_PRESCALER_8:
            BIT_SET(SPCR, SPR0);
            BIT_CLR(SPCR, SPR1);
            BIT_SET(SPSR, SPI2X);
            break;
        case SPI_PRESCALER_16:
            BIT_SET(SPCR, SPR0);
            BIT_CLR(SPCR, SPR1);
            BIT_CLR(SPSR, SPI2X);
            break;
        case SPI_PRESCALER_32:
            BIT_CLR(SPCR, SPR0);
            BIT_SET(SPCR, SPR1);
            BIT_SET(SPSR, SPI2X);
            break;
        case SPI_PRESCALER_64:
            BIT_SET(SPCR, SPR1);
            if(SPI_Config.doubleSpeed == SPI_DOUBLE_SPEED_ENABLE) {
                BIT_SET(SPCR, SPR0);
                BIT_SET(SPSR, SPI2X);
            }else {
                BIT_CLR(SPCR, SPR0);
                BIT_CLR(SPSR, SPI2X);
            }
            break;
        case SPI_PRESCALER_128:
            BIT_SET(SPCR, SPR1);
            BIT_SET(SPCR, SPR0);
            BIT_CLR(SPSR, SPI2X);
            break;
        default:
            break;
    }
        

}

/****************************************************************************
 * @brief Enable SPI module by setting the SPI Enable bit in the SPCR register
 ****************************************************************************/
static void SPI_Enable(void) {
    BIT_SET(SPCR, SPE);   
}

/****************************************************************************
 * @brief Disable SPI module by clearing the SPI Enable bit in the SPCR register
 ****************************************************************************/
static void SPI_Disable(void) {
    BIT_CLR(SPCR, SPE);
}

/****************************************************************************   
 * @brief Set the SPI in Master mode
 ****************************************************************************/
static void SPI_MasterInit(void) {
    /* Configure pins */
    DIO_InitPin(SPI_Config.connections.SS.pin  , SPI_Config.connections.SS.port    , DIO_OUTPUT , DIO_PULLUP_OFF);
    DIO_InitPin(SPI_Config.connections.MOSI.pin, SPI_Config.connections.MOSI.port  , DIO_OUTPUT , DIO_PULLUP_OFF);
    DIO_InitPin(SPI_Config.connections.MISO.pin, SPI_Config.connections.MISO.port  , DIO_INPUT  , DIO_PULLUP_OFF);
    DIO_InitPin(SPI_Config.connections.SCK.pin , SPI_Config.connections.SCK.port   , DIO_OUTPUT , DIO_PULLUP_OFF);

    /* Sending Falling Edge on the SS pin */
    DIO_SetPinValue(SPI_Config.connections.SS.pin, SPI_Config.connections.SS.port, HIGH);
    DIO_SetPinValue(SPI_Config.connections.SS.pin, SPI_Config.connections.SS.port, LOW);

    /* Set Master mode */
    BIT_SET(SPCR, MSTR);
}

/****************************************************************************
 * @brief Set the SPI in Slave mode by clearing the Master bit in the SPCR register
 *        and setting MISO as output and others as input
 ****************************************************************************/
static void SPI_SlaveInit(void) {
    /* Configure pins */
    DIO_InitPin(SPI_Config.connections.SS.pin  , SPI_Config.connections.SS.port    , DIO_INPUT  , DIO_PULLUP_OFF);
    DIO_InitPin(SPI_Config.connections.MOSI.pin, SPI_Config.connections.MOSI.port  , DIO_INPUT  , DIO_PULLUP_OFF);
    DIO_InitPin(SPI_Config.connections.MISO.pin, SPI_Config.connections.MISO.port  , DIO_OUTPUT , DIO_PULLUP_OFF);
    DIO_InitPin(SPI_Config.connections.SCK.pin , SPI_Config.connections.SCK.port   , DIO_INPUT  , DIO_PULLUP_OFF);

    /* Set Slave mode */
    BIT_CLR(SPCR, MSTR);

    #if 0   /* TEST */
    /* Clear the Master bit in the SPCR register */
    SPSR = SPSR;
    #endif

}

static void SPI_SetMode(void) {
    switch(SPI_Config.mode) {
        case SPI_MASTER:
            SPI_MasterInit();
            break;
        case SPI_SLAVE:
            SPI_SlaveInit();
            break;
        default:
            break;
    }
}

static void SPI_SetDataOrder(void) {
    switch(SPI_Config.dataOrder) {
        case SPI_DATA_ORDER_LSB_FIRST:
            BIT_SET(SPCR, DORD);
            break;
        case SPI_DATA_ORDER_MSB_FIRST:
            BIT_CLR(SPCR, DORD);
            break;
        default:
            break;
    }
}

static void SPI_SetClockMode(void) {
    switch(SPI_Config.clockMode) {
        case SPI_MODE0:
            BIT_CLR(SPCR, CPOL);
            BIT_CLR(SPCR, CPHA);
            break;
        case SPI_MODE1:
            BIT_CLR(SPCR, CPOL);
            BIT_SET(SPCR, CPHA);
            break;
        case SPI_MODE2:
            BIT_SET(SPCR, CPOL);
            BIT_CLR(SPCR, CPHA);
            break;
        case SPI_MODE3:
            BIT_SET(SPCR, CPOL);
            BIT_SET(SPCR, CPHA);
            break;
        default:
            break;
    }
}
