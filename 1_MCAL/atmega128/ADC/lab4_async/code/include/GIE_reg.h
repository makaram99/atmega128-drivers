/**************************************************************************
 * @file        GIE_reg.h
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Registers file of Global Interrupt Enable Flag
 * @version     1.0.0
 * @date        2021-07-31
 * @copyright   Copyright (c) 2022
 **************************************************************************/
#ifndef GIE_REG_H
#define GIE_REG_H

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*              CHANGE THIS PART ONLY FOR NEW DEVICES                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#ifndef SREG
#define SREG            (* ((volatile u8_t *) 0x5F) )
#endif

#ifndef I_BIT
#define I_BIT           (7U)
#endif


#endif    /* GIE_REG_H */