/**************************************************************************
 * @file        SPI_reg.h
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       SPI Registers of ATmega328p MCU
 * @version     1.0.0
 * @date        2021-07-31
 * @copyright   Copyright (c) 2022
 **************************************************************************/
#ifndef SPI_REG_H
#define SPI_REG_H

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*              CHANGE THIS PART ONLY FOR NEW DEVICES                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#define SPCR        (* ((volatile u8_t *) 0x2D) )
#define SPSR        (* ((volatile u8_t *) 0x2E) )
#define SPDR        (* ((volatile u8_t *) 0x2F) )


enum {
    SPR0, /* SPI Clock Rate Select Bit 0 */
    SPR1, /* SPI Clock Rate Select Bit 1 */
    CPHA, /* SPI Clock Phase */
    CPOL, /* SPI Clock Polarity */
    MSTR, /* SPI Master/Slave Select */
    DORD, /* Data Order */
    SPE,  /* SPI Enable */
    SPIE, /* SPI Interrupt Enable */
};  /* SPCR: SPI Control Register */

enum {
    SPI2X,      /* Double SPI Speed Bit */
    WCOL = 6,   /* Write Collision Flag */
    SPIF,       /* SPI Interrupt Flag */
};  /* SPSR: SPI Status Register */

#endif    /* SPI_REG_H */