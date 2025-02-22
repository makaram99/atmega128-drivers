/**************************************************************************
 * @file        I2C_reg.h
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       I2C Registers of ATmega328p MCU
 * @version     1.0.0
 * @date        2021-07-31
 * @copyright   Copyright (c) 2022
 **************************************************************************/
#ifndef I2C_REG_H
#define I2C_REG_H

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*              CHANGE THIS PART ONLY FOR NEW DEVICES                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#define SPCR        (* ((volatile u8_t *) 0x2D) )
#define SPSR        (* ((volatile u8_t *) 0x2E) )
#define SPDR        (* ((volatile u8_t *) 0x2F) )


enum {
    SPR0, /* I2C Clock Rate Select Bit 0 */
    SPR1, /* I2C Clock Rate Select Bit 1 */
    CPHA, /* I2C Clock Phase */
    CPOL, /* I2C Clock Polarity */
    MSTR, /* I2C Master/Slave Select */
    DORD, /* Data Order */
    SPE,  /* I2C Enable */
    I2CE, /* I2C Interrupt Enable */
};  /* SPCR: I2C Control Register */

enum {
    I2C2X,      /* Double I2C Speed Bit */
    WCOL = 6,   /* Write Collision Flag */
    I2CF,       /* I2C Interrupt Flag */
};  /* SPSR: I2C Status Register */

#endif    /* I2C_REG_H */