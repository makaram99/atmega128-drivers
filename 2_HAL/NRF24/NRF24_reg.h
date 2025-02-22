/**************************************************************************
 * @file        NRF24_reg.h
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Registers of NRF24L01 wireless transceiver module.
 * @version     1.0.0
 * @date        2021-07-31
 **************************************************************************/
#ifndef NRF_REG_H
#define NRF_REG_H

enum{
    PRIM_RX,        /* PRIMARY RX TX */
    PWR_UP,         /* POWER UP */
    CRCO,           /* CRC encoding scheme  */
    EN_CRC,         /* Enable CRC */
    MASK_MAX_RT,    /* Mask interrupt caused by MAX_RT */
    MASK_TX_DS,     /* Mask interrupt caused by TX_DS */
    MASK_RX_DR,     /* Mask interrupt caused by RX_DR */
};  /* CONFIG: configuration register */

enum{
    ENAA_P0,        /* Enable auto acknowledgment data pipe 0 */
    ENAA_P1,        /* Enable auto acknowledgment data pipe 1 */
    ENAA_P2,        /* Enable auto acknowledgment data pipe 2 */
    ENAA_P3,        /* Enable auto acknowledgment data pipe 3 */
    ENAA_P4,        /* Enable auto acknowledgment data pipe 4 */
    ENAA_P5,        /* Enable auto acknowledgment data pipe 5 */
};  /* EN_AA: Enable auto acknowledgment register */

enum{
    ERX_P0,         /* Enable data pipe 0 */
    ERX_P1,         /* Enable data pipe 1 */
    ERX_P2,         /* Enable data pipe 2 */
    ERX_P3,         /* Enable data pipe 3 */
    ERX_P4,         /* Enable data pipe 4 */
    ERX_P5,         /* Enable data pipe 5 */
};  /* EN_RXADDR: Enable RX addresses */

enum{
    AW0,            /* Address width 0 */
    AW1,            /* Address width 1 */
};  /* SETUP_AW: Setup address width */

enum{
    ARC0,           /* Auto retransmit count 0 */
    ARC1,           /* Auto retransmit count 1 */
    ARC2,           /* Auto retransmit count 2 */
    ARC3,           /* Auto retransmit count 3 */
    ARD0,           /* Auto retransmit delay 0 */
    ARD1,           /* Auto retransmit delay 1 */
    ARD2,           /* Auto retransmit delay 2 */
    ARD3,           /* Auto retransmit delay 3 */
};  /* SETUP_RETR: Setup of automatic retransmission */

enum{
    RF_CH0,
    RF_CH1,
    RF_CH2,
    RF_CH3,
    RF_CH4,
    RF_CH5,
    RF_CH6, 
};  /* RF_CH: RF channel register: range 0-127 */

enum{
    Obsolete,       /* Obsolete */
    RF_PWR0,        /* Set RF output power 0 */
    RF_PWR1,        /* Set RF output power 1 */
    RF_DR_HIGH,     /* Set RF data rate: HIGH */
    PLL_LOCK,       /* Set PLL lock */
    RF_DR_LOW,      /* Set RF data rate: LOW */
    RESERVED,       /* Reserved: Only 0 allowed */
    CONT_WAVE,      /* Set RF to continuous wave */
};  /* RF_SETUP: RF setup register */

enum{
    TX_FULL0,   /* TX FIFO full */
    RX_P_NO0,  /* RX pipe number for payload available in the RX FIFO 0 */
    RX_P_NO1,  /* RX pipe number for payload available in the RX FIFO 1 */
    RX_P_NO2,  /* RX pipe number for payload available in the RX FIFO 2 */
    MAX_RT,     /* Maximum number of TX retransmits interrupt */
    TX_DS,      /* Data sent interrupt */
    RX_DR,      /* Data received interrupt */
};  /* STATUS: Status register */

enum{
    ARC_CNT0,     /* Auto retransmit count 0 */
    ARC_CNT1,     /* Auto retransmit count 1 */
    ARC_CNT2,     /* Auto retransmit count 2 */
    ARC_CNT3,     /* Auto retransmit count 3 */
    PLOS_CNT0,    /* Count lost packets */
    PLOS_CNT1,    /* Count lost packets */
    PLOS_CNT2,    /* Count lost packets */
    PLOS_CNT3,    /* Count lost packets */
};  /* OBSERVE_TX: Transmit observe register */

enum{
    RPD,         /* Received power detector */
};  /* RPD: Received power detector */

enum{
    RX_EMPTY,    /* RX FIFO empty */
    RX_FULL1,     /* RX FIFO full */
    TX_EMPTY = 4,    /* TX FIFO empty */
    TX_FULL,     /* TX FIFO full */
    TX_REUSE,    /* TX FIFO re-use */
};  /* FIFO_STATUS: FIFO status register */

enum{
    DYNPD0,      /* Enable dynamic payload length data pipe 0 */
    DYNPD1,      /* Enable dynamic payload length data pipe 1 */
    DYNPD2,      /* Enable dynamic payload length data pipe 2 */
    DYNPD3,      /* Enable dynamic payload length data pipe 3 */
    DYNPD4,      /* Enable dynamic payload length data pipe 4 */
    DYNPD5,      /* Enable dynamic payload length data pipe 5 */
};  /* DYNPD: Enable dynamic payload length */

enum{
    EN_DYN_ACK, /* Enables the W_TX_PAYLOAD_NOACK command   */
    EN_ACK_PAY, /* Enables Payload with ACK                 */
    EN_DPL,     /* Enables dynamic payload length           */

};  /* FEATURE: Feature register */

enum{
    DPL_P0,      /* Dynamic payload length data pipe 0 */
    DPL_P1,      /* Dynamic payload length data pipe 1 */
    DPL_P2,      /* Dynamic payload length data pipe 2 */
    DPL_P3,      /* Dynamic payload length data pipe 3 */
    DPL_P4,      /* Dynamic payload length data pipe 4 */
    DPL_P5,      /* Dynamic payload length data pipe 5 */
};  /* DPL_P: Dynamic payload length */
    
/*---------------------------------------------------------------------------*/
/*                                Memory Map                                 */
/*---------------------------------------------------------------------------*/
#define CONFIG      0x00
#define EN_AA       0x01
#define EN_RXADDR   0x02
#define SETUP_AW    0x03
#define SETUP_RETR  0x04
#define RF_CH       0x05
#define RF_SETUP    0x06
#define STATUS      0x07
#define OBSERVE_TX  0x08
#define CD          0x09

/**
 * @brief Pipes 0-5 addressses
 */
#define RX_ADDR_P0  0x0A
#define RX_ADDR_P1  0x0B
#define RX_ADDR_P2  0x0C
#define RX_ADDR_P3  0x0D
#define RX_ADDR_P4  0x0E
#define RX_ADDR_P5  0x0F

/**
 * @brief Transmit address
 */
#define TX_ADDR     0x10

/**
 * @brief RX payload widths of pipes 0-5: 0 - 32 bytes
 */
#define RX_PW_P0    ( (u8_t)0x11 )
#define RX_PW_P1    ( (u8_t)0x12 )
#define RX_PW_P2    ( (u8_t)0x13 )
#define RX_PW_P3    ( (u8_t)0x14 )
#define RX_PW_P4    ( (u8_t)0x15 )
#define RX_PW_P5    ( (u8_t)0x16 )

#define FIFO_STATUS ( (u8_t)0x17 )
#define DYNPD       ( (u8_t)0x1C )
#define FEATURE     ( (u8_t)0x1D )

/*---------------------------------------------------------------------------*/
/*                        Instruction Mnemonics                              */
/*---------------------------------------------------------------------------*/
#define R_REGISTER    ( (u8_t)0x00U )  /* Read command */
#define W_REGISTER    ( (u8_t)0x20U )  /* Write command */
#define R_RX_PAYLOAD  ( (u8_t)0x61U )  /* Read RX payload */
#define W_TX_PAYLOAD  ( (u8_t)0xA0U )  /* Write TX payload */
#define FLUSH_TX      ( (u8_t)0xE1U )  /* Flush TX FIFO */
#define FLUSH_RX      ( (u8_t)0xE2U )  /* Flush RX FIFO */
#define REUSE_TX_PL   ( (u8_t)0xE3U )  /* Reuse last transmitted payload */
#define R_RX_PL_WID   ( (u8_t)0x60U )  /* Read RX payload width for the top RX payload in the FIFO */
#define W_ACK_PAYLOAD ( (u8_t)0xA8U )  /* Write Payload to be transmitted together with ACK */
#define W_TX_PAYLOAD_NOACK ( (u8_t)0xB0U ) /* Write Payload to be transmitted without ACK */
#define NOP           ( (u8_t)0xFF )  /* No operation */

#define ACTIVATE      ( (u8_t)0x50U )  /* Activate features */
#define REGISTER_MASK ( (u8_t)0x1FU )  /* Register mask */

#endif    /* NRF_REG_H */