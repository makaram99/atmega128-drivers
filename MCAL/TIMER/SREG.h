/**************************************************************************
 * @file    SREG.h
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Status Registers of ATmega328p MCU
 * @version 1.0.0
 * @date    2021-07-31
 **************************************************************************/
#ifndef SREG_H
#define SREG_H

#ifndef SREG
#define SREG            (* ((volatile u8_t *) 0x5F) )
#endif

#ifndef C_BIT
#define C_BIT   (0U)      /* Carry Flag */
#endif

#ifndef Z_BIT
#define Z_BIT   (1U)      /* Zero Flag */
#endif

#ifndef N_BIT
#define N_BIT   (2U)      /* Negative Flag */
#endif

#ifndef V_BIT
#define V_BIT   (3U)      /* Two's Complement Overflow Flag */
#endif

#ifndef S_BIT
#define S_BIT   (4U)      /* Sign Flag */
#endif

#ifndef H_BIT
#define H_BIT   (5U)      /* Half Carry Flag */
#endif

#ifndef T_BIT
#define T_BIT   (6U)      /* Bit Copy Storage */
#endif

#ifndef I_BIT
#define I_BIT   (7U)      /* Global Interrupt Enable */
#endif

#endif    /* SREG_H */