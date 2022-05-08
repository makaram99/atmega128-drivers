/******************************************************************************
 * @file        NRF24.c
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       NRF24 wireless transceiver module driver.
 * @version     1.0.0
 * @date        2022-03-20
 * @copyright   Copyright (c) 2022
 ******************************************************************************/
#include "util/delay.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "NRF24_reg.h"
#include "DIO.h"
#include "GIE.h"
#include "SPI.h"
#include "NRF24.h"
#include "NRF24_cfg.h"

/*-----------------------------------------------------------------------------*/
/*                              PRIVATE FUNCTIONS                              */
/*-----------------------------------------------------------------------------*/

static void NRF24_CS_Select() {
    DIO_WritePin(NRF24_cfg.pins.csn.pin, NRF24_cfg.pins.csn.port, LOW);
}

static void NRF24_CS_Deselect() {
    DIO_WritePin(NRF24_cfg.pins.csn.pin, NRF24_cfg.pins.csn.port, HIGH);
}

static void NRF24_CE_Enable() {
    DIO_WritePin(NRF24_cfg.pins.ce.pin, NRF24_cfg.pins.ce.port, HIGH);
}

static void NRF24_CE_Disable() {
    DIO_WritePin(NRF24_cfg.pins.ce.pin, NRF24_cfg.pins.ce.port, LOW);
}

/* Clocks only one byte into the given nrf24 register */
static void NRF24_WriteReg(u8_t reg, u8_t value) {
    NRF24_CS_Select();      /* Select nrf24 */

    SPI_SendByte(W_REGISTER | reg);
    SPI_SendByte(value);

    NRF24_CS_Deselect();    /* Deselect nrf24 */
}

/* Clock many bytes into the given nrf24 register */
static void NRF24_WriteRegMulti(u8_t reg, u8_t *value, u8_t len) {
    NRF24_CS_Select();      /* Select nrf24 */
    SPI_SendByte(W_REGISTER | reg);

    for(u8_t i = 0; i < len; ++i) {
        SPI_SendByte(value[i]);
    }

    NRF24_CS_Deselect();    /* Deselect nrf24 */
}

/* Reads only one byte from the given nrf24 register */
static u8_t NRF24_ReadReg(u8_t reg) {
    u8_t value = 0;

    NRF24_CS_Select();      /* Select nrf24 */
    SPI_SendByte(R_REGISTER | reg);
    SPI_TrancieveByte(value, &value);
    
    NRF24_CS_Deselect();    /* Deselect nrf24 */

    return value;
}

/* Reads Many bytes from the given nrf24 register */
static void NRF24_ReadRegMulti(u8_t reg, u8_t *data, u8_t length) {
    u8_t value = 0;

    NRF24_CS_Select();      /* Select nrf24 */

    SPI_SendByte(R_REGISTER | reg);

    for(u8_t i = 0; i < length; ++i) {
        SPI_ReceiveByte(&value);
        data[i] = value;
    }

    NRF24_CS_Deselect();    /* Deselect nrf24 */
}

static void NRF24_FlushRX() {
    NRF24_CS_Select();      /* Select nrf24 */

    SPI_SendByte(FLUSH_RX);

    NRF24_CS_Deselect();    /* Deselect nrf24 */
}

static void NRF24_FlushTX() {
    NRF24_CS_Select();      /* Select nrf24 */

    SPI_SendByte(FLUSH_TX);

    NRF24_CS_Deselect();    /* Deselect nrf24 */
}

static void NRF24_Reset(u8_t reg) {
    /* Disable nrf24 */
    NRF24_CE_Disable();

    /* Reset nrf24 */
    switch(reg) {
        case STATUS:
            NRF24_WriteReg(STATUS, 0);
            break;
        case FIFO_STATUS:
            NRF24_WriteReg(FIFO_STATUS, 0x11);
            break;
        default:
            NRF24_WriteReg(CONFIG, 0x08);
            NRF24_WriteReg(EN_AA, 0x3F);
            NRF24_WriteReg(EN_RXADDR, 0x03);
            NRF24_WriteReg(SETUP_AW, 0x03);
            NRF24_WriteReg(SETUP_RETR, 0x03);
            NRF24_WriteReg(RF_CH, 0x02);
            NRF24_WriteReg(RF_SETUP, 0x0E);
            NRF24_WriteReg(STATUS, 0x0E);
            NRF24_WriteReg(OBSERVE_TX, 0x00);
            u8_t pipe0[5] = {0xE7, 0xE7, 0xE7, 0xE7, 0xE7};
            NRF24_WriteRegMulti(RX_ADDR_P0, pipe0, 5);
            u8_t pipe1[5] = {0xC2, 0xC2, 0xC2, 0xC2, 0xC2};
            NRF24_WriteRegMulti(RX_ADDR_P1, pipe1, 5);
            NRF24_WriteReg(RX_ADDR_P2, 0xC3);
            NRF24_WriteReg(RX_ADDR_P3, 0xC4);
            NRF24_WriteReg(RX_ADDR_P4, 0xC5);
            NRF24_WriteReg(RX_ADDR_P5, 0xC6);
            u8_t txAddr[5] = {0xE7, 0xE7, 0xE7, 0xE7, 0xE7};
            NRF24_WriteRegMulti(TX_ADDR, txAddr, 5);
            NRF24_WriteReg(RX_PW_P0, 0x00);
            NRF24_WriteReg(RX_PW_P1, 0x00);
            NRF24_WriteReg(RX_PW_P2, 0x00);
            NRF24_WriteReg(RX_PW_P3, 0x00);
            NRF24_WriteReg(RX_PW_P4, 0x00);
            NRF24_WriteReg(RX_PW_P5, 0x00);
            NRF24_WriteReg(FIFO_STATUS, 0x11);
            NRF24_WriteReg(DYNPD, 0x00);
            NRF24_WriteReg(FEATURE, 0x00);
            break;
    }
}

/*----------------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                                    */
/*----------------------------------------------------------------------------------*/

void NRF24_Init(void) {
    /* Setup pins */
    DIO_InitPin(NRF24_cfg.pins.ce.pin, NRF24_cfg.pins.ce.port, OUTPUT, PULLUP_FALSE);
    DIO_InitPin(NRF24_cfg.pins.csn.pin, NRF24_cfg.pins.csn.port, OUTPUT, PULLUP_FALSE);
    
    /* Initialize SPI */
    SPI_Init();

    /* Disable nrf24 to configure it */
    NRF24_CE_Disable();

    /* Set nrf24 to power Down mode */
    NRF24_WriteReg(CONFIG, 0 );

    /* Disable auto ack */
    NRF24_WriteReg(EN_AA, 0);

    /* Disable all pipes */
    NRF24_WriteReg(EN_RXADDR, 0);

    /* Set RX/TX address width to 5 bytes */
    NRF24_WriteReg(SETUP_AW, 0x03);

    /* Disable retransmit */
    NRF24_WriteReg(SETUP_RETR, 0);
    
    /* Set RF channel to default */
    NRF24_WriteReg(RF_CH, 0);

    /* 2 Mbps, RX gain: 0dbm    */
    NRF24_WriteReg(RF_SETUP, (1 << RF_DR_HIGH)|(0 << RF_DR_LOW)|((0x03) << RF_PWR0));

    /* Enable nrf24 */
    NRF24_CE_Enable();
}

void NRF24_TxMode(void) {
    u8_t configReg = 0;

    /* Disable nrf24 to configure it */
    NRF24_CE_Disable();

    /* Set nrf24 channel */
    NRF24_WriteReg(RF_CH, NRF24_cfg.channel);

    /* Set nrf24 TX address */
    NRF24_WriteRegMulti(TX_ADDR, NRF24_cfg.txAddress, NRF24_cfg.addressWidth);

    /* Set nrf24 in TX mode, and power up */
    configReg = NRF24_ReadReg(CONFIG);
    SET_BIT(configReg, PWR_UP);     /* Power up */
    CLR_BIT(configReg, PRIM_RX);    /* Set to TX mode */
    NRF24_WriteReg(CONFIG, configReg);
    

    /* Enable nrf24 */
    NRF24_CE_Enable();
}

void NRF24_SendString(u8_t *data, u8_t len) {
    u8_t fifoStatus = 0;

    /* Select nrf24 */
    NRF24_CS_Select();

    /* Flush TX FIFO */
    NRF24_FlushTX();

    /* Write data to TX FIFO */
    NRF24_WriteRegMulti(W_TX_PAYLOAD, data, len);

    /* Disable nrf24 */
    NRF24_CS_Deselect();

    /* Wait for TX FIFO to be empty */
    while(1) {
        /* Select nrf24 */
        NRF24_CS_Select();

        /* Read FIFO status */
        fifoStatus = NRF24_ReadReg(FIFO_STATUS);

        /* Deselect nrf24 */
        NRF24_CS_Deselect();

        /* Check if TX FIFO is empty */
        if(fifoStatus & (1 << TX_EMPTY)) {
            NRF24_FlushTX();
            NRF24_Reset(FIFO_STATUS);
            break;
        }
    }
}

void NRF24_RxMode(void) {
    u8_t configReg = 0;
    u8_t enableRXAddr = 0;

    /* Disable nrf24 to configure it */
    NRF24_CE_Disable();

    /* Set nrf24 channel */
    NRF24_WriteReg(RF_CH, NRF24_cfg.channel);

    enableRXAddr = NRF24_ReadReg(EN_RXADDR);

    /* Set nrf24 RX address */
    switch(NRF24_cfg.rxPipe) {
        case RX_PIPE0:
            enableRXAddr |= (1 << ERX_P0);
            NRF24_WriteReg(EN_RXADDR, enableRXAddr);
            NRF24_WriteRegMulti(RX_ADDR_P0, NRF24_cfg.rx0Address, NRF24_cfg.addressWidth);
            break;
        case RX_PIPE1:
            enableRXAddr |= (1 << ERX_P1);
            NRF24_WriteReg(EN_RXADDR, enableRXAddr);
            NRF24_WriteRegMulti(RX_ADDR_P1, NRF24_cfg.rx1Address, NRF24_cfg.addressWidth);
            break;
        case RX_PIPE2:
            enableRXAddr |= (1 << ERX_P2);
            NRF24_WriteReg(EN_RXADDR, enableRXAddr);
            NRF24_WriteRegMulti(RX_ADDR_P2, NRF24_cfg.rx2Address, NRF24_cfg.addressWidth);
            break;
        case RX_PIPE3:
            enableRXAddr |= (1 << ERX_P3);
            NRF24_WriteReg(EN_RXADDR, enableRXAddr);
            NRF24_WriteRegMulti(RX_ADDR_P3, NRF24_cfg.rx3Address, NRF24_cfg.addressWidth);
            break;
        case RX_PIPE4:
            enableRXAddr |= (1 << ERX_P4);
            NRF24_WriteReg(EN_RXADDR, enableRXAddr);
            NRF24_WriteRegMulti(RX_ADDR_P4, NRF24_cfg.rx4Address, NRF24_cfg.addressWidth);
            break;
        case RX_PIPE5:
            enableRXAddr |= (1 << ERX_P5);
            NRF24_WriteReg(EN_RXADDR, enableRXAddr);
            NRF24_WriteRegMulti(RX_ADDR_P5, NRF24_cfg.rx5Address, NRF24_cfg.addressWidth);
            break;
        default:
            break;
    }

    /* Set nrf24 in TX mode, and power up */
    configReg = NRF24_ReadReg(CONFIG);
    SET_BIT(configReg, PWR_UP);     /* Power up */
    SET_BIT(configReg, PRIM_RX);    /* Set to RX mode */
    NRF24_WriteReg(CONFIG, configReg);

    /* Enable nrf24 */
    NRF24_CE_Enable();
}

u8_t NRF24_Available(void) {
    u8_t retVal = 0;
    u8_t statusReg = 0;

    /* Select nrf24 */
    NRF24_CS_Select();

    /* Read status register */
    statusReg = NRF24_ReadReg(STATUS);

    /* Deselect nrf24 */
    NRF24_CS_Deselect();

    /* Check if data is ready */
    if( (statusReg & (1 << RX_DR)) && ( ( (statusReg >> RX_P_NO0) & NRF24_cfg.rxPipe ) == NRF24_cfg.rxPipe ) ) {
        retVal = 1;
    }

    return retVal;
}

ERROR_t NRF24_ReceiveString(u8_t *data, u8_t length) {
    ERROR_t retVal = ERROR_NO;
    u8_t volatile fifoStatus = 0;

    /* Select nrf24 */
    NRF24_CS_Select();

    /* Read FIFO status */
    fifoStatus = NRF24_ReadReg(FIFO_STATUS);

    if(NRF24_Available()) {
        /* Read data from RX FIFO */
        NRF24_ReadRegMulti(R_RX_PAYLOAD, data, length);
    }else {
        retVal = ERROR_YES;
    }

    /* Deselect nrf24 */
    NRF24_CS_Deselect();

    /* Flush RX FIFO */
    NRF24_FlushRX();
    
    return retVal;
}
       
