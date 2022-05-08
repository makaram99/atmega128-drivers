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
    SET_BIT(SPCR, SPIE);

    GIE_Enable();
}

void SPI_DisableInterrupt(void) {
    CLR_BIT(SPCR, SPIE);
}

ERROR_t SPI_SendByte(const u8_t data) {
    ERROR_t error = ERROR_NO;
    u8_t volatile fBuffer = 0;

    SPDR = data;                        /* Write data to the SPI data register */

    while(BIT_IS_CLEAR(SPSR, SPIF))
        ;                               /* Wait until SPI transfer complete */

    /* Clear transmission complete flag by reading SPI Status register */
    fBuffer = SPSR; /* Read SPI Status register */
    fBuffer = SPDR; /* Then access SPI Data register */

    return error;
}

ERROR_t SPI_ReceiveByte(u8_t * const data) {
    ERROR_t errorStatus = ERROR_NO;

    while(BIT_IS_CLEAR(SPSR, SPIF))
        ;                                           /* Wait for transmission complete   */
    
    *data = SPDR;                                  /* Read data from buffer */
    /* Reading SPDR also clears the SPIF flag. So, no need to clear it again */

    return errorStatus;
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

    SET_BIT(SPSR, SPIF);        /* Clear SPI interrupt flag */

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
            CLR_BIT(SPCR, SPR0);
            CLR_BIT(SPCR, SPR1);
            SET_BIT(SPSR, SPI2X);
            break;
        case SPI_PRESCALER_4:
            CLR_BIT(SPCR, SPR0);
            CLR_BIT(SPCR, SPR1);
            CLR_BIT(SPSR, SPI2X);
            break;
        case SPI_PRESCALER_8:
            SET_BIT(SPCR, SPR0);
            CLR_BIT(SPCR, SPR1);
            SET_BIT(SPSR, SPI2X);
            break;
        case SPI_PRESCALER_16:
            SET_BIT(SPCR, SPR0);
            CLR_BIT(SPCR, SPR1);
            CLR_BIT(SPSR, SPI2X);
            break;
        case SPI_PRESCALER_32:
            CLR_BIT(SPCR, SPR0);
            SET_BIT(SPCR, SPR1);
            SET_BIT(SPSR, SPI2X);
            break;
        case SPI_PRESCALER_64:
            SET_BIT(SPCR, SPR1);
            if(SPI_Config.doubleSpeed == SPI_DOUBLE_SPEED_ENABLE) {
                SET_BIT(SPCR, SPR0);
                SET_BIT(SPSR, SPI2X);
            }else {
                CLR_BIT(SPCR, SPR0);
                CLR_BIT(SPSR, SPI2X);
            }
            break;
        case SPI_PRESCALER_128:
            SET_BIT(SPCR, SPR1);
            SET_BIT(SPCR, SPR0);
            CLR_BIT(SPSR, SPI2X);
            break;
        default:
            break;
    }
        

}

/****************************************************************************
 * @brief Enable SPI module by setting the SPI Enable bit in the SPCR register
 ****************************************************************************/
static void SPI_Enable(void) {
    SET_BIT(SPCR, SPE);   
}

/****************************************************************************
 * @brief Disable SPI module by clearing the SPI Enable bit in the SPCR register
 ****************************************************************************/
static void SPI_Disable(void) {
    CLR_BIT(SPCR, SPE);
}

/****************************************************************************   
 * @brief Set the SPI in Master mode
 ****************************************************************************/
static void SPI_MasterInit(void) {
    /* Configure pins */
    DIO_InitPin(SPI_Config.connections.SS.pin  , SPI_Config.connections.SS.port    , OUTPUT , PULLUP_FALSE);
    DIO_InitPin(SPI_Config.connections.MOSI.pin, SPI_Config.connections.MOSI.port  , OUTPUT , PULLUP_FALSE);
    DIO_InitPin(SPI_Config.connections.MISO.pin, SPI_Config.connections.MISO.port  , INPUT  , PULLUP_FALSE);
    DIO_InitPin(SPI_Config.connections.SCK.pin , SPI_Config.connections.SCK.port   , OUTPUT , PULLUP_FALSE);

    /* Sending Falling Edge on the SS pin */
    DIO_WritePin(SPI_Config.connections.SS.pin, SPI_Config.connections.SS.port, HIGH);
    DIO_WritePin(SPI_Config.connections.SS.pin, SPI_Config.connections.SS.port, LOW);

    /* Set Master mode */
    SET_BIT(SPCR, MSTR);
}

/****************************************************************************
 * @brief Set the SPI in Slave mode by clearing the Master bit in the SPCR register
 *        and setting MISO as output and others as input
 ****************************************************************************/
static void SPI_SlaveInit(void) {
    /* Configure pins */
    DIO_InitPin(SPI_Config.connections.SS.pin  , SPI_Config.connections.SS.port    , INPUT  , PULLUP_FALSE);
    DIO_InitPin(SPI_Config.connections.MOSI.pin, SPI_Config.connections.MOSI.port  , INPUT  , PULLUP_FALSE);
    DIO_InitPin(SPI_Config.connections.MISO.pin, SPI_Config.connections.MISO.port  , OUTPUT , PULLUP_FALSE);
    DIO_InitPin(SPI_Config.connections.SCK.pin , SPI_Config.connections.SCK.port   , INPUT  , PULLUP_FALSE);

    /* Set Slave mode */
    CLR_BIT(SPCR, MSTR);

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
            SET_BIT(SPCR, DORD);
            break;
        case SPI_DATA_ORDER_MSB_FIRST:
            CLR_BIT(SPCR, DORD);
            break;
        default:
            break;
    }
}

static void SPI_SetClockMode(void) {
    switch(SPI_Config.clockMode) {
        case SPI_MODE0:
            CLR_BIT(SPCR, CPOL);
            CLR_BIT(SPCR, CPHA);
            break;
        case SPI_MODE1:
            CLR_BIT(SPCR, CPOL);
            SET_BIT(SPCR, CPHA);
            break;
        case SPI_MODE2:
            SET_BIT(SPCR, CPOL);
            CLR_BIT(SPCR, CPHA);
            break;
        case SPI_MODE3:
            SET_BIT(SPCR, CPOL);
            SET_BIT(SPCR, CPHA);
            break;
        default:
            break;
    }
}
