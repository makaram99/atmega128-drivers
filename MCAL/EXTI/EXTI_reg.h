/**************************************************************************
 * @file        EXTI_reg.h
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       EXTI Registers of ATmega328p MCU
 * @version     1.0.0
 * @date        2021-07-31
 * @copyright   Copyright (c) 2022
 **************************************************************************/
#ifndef EXTI_REG_H
#define EXTI_REG_H


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*              CHANGE THIS PART ONLY FOR NEW DEVICES                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#define MCUCR      (* ((volatile u8_t *) 0x55) )   /* MCU Control Register (Used with bootloader only) */
#define EICRA      (* ((volatile u8_t *) 0x6A) )   /* External Interrupt Control Register A --> INT3:0 mode: falling, rising, or Low Level */
#define EICRB      (* ((volatile u8_t *) 0x5B) )   /* External Interrupt Control Register B --> INT7:4 mode: falling, rising, or Low Level */
#define EIMSK      (* ((volatile u8_t *) 0x59) )   /* External Interrupt Mask Register: Enable or Disable External Interrupts */
#define EIFR       (* ((volatile u8_t *) 0x58) )   /* External Interrupt Flag Register: Clear External Interrupts Flag */

enum {
    IVCE,       /* Interrupt Vector Change Enable */
    IVSEL,      /* Interrupt Vector Select */
    SM2,        /* Sleep Mode */
    SM0,        /* Sleep Mode */
    SM1,        /* Sleep Mode */
    SE,         /* Sleep Enable */
    SRW10,      /* Wait state select, used with External SRAM   */
    SRE         /* External SRAM Enable */    
};  /* MCUCR: MCU Control Register */

enum {
    ISC00,      /* Interrupt Sense Control 0 */
    ISC01,      /* Interrupt Sense Control 0 */
    ISC10,      /* Interrupt Sense Control 1 */
    ISC11,      /* Interrupt Sense Control 1 */
    ISC20,      /* Interrupt Sense Control 2 */
    ISC21,      /* Interrupt Sense Control 2 */
    ISC30,      /* Interrupt Sense Control 3 */
    ISC31,      /* Interrupt Sense Control 3 */
};  /* EICRA: External Interrupt Control Register A */  

enum {
    ISC40,      /* Interrupt Sense Control 4 */
    ISC41,      /* Interrupt Sense Control 4 */
    ISC50,      /* Interrupt Sense Control 5 */
    ISC51,      /* Interrupt Sense Control 5 */
    ISC60,      /* Interrupt Sense Control 6 */
    ISC61,      /* Interrupt Sense Control 6 */
    ISC70,      /* Interrupt Sense Control 7 */
    ISC71,      /* Interrupt Sense Control 7 */
};  /* EICRB: External Interrupt Control Register B */    

enum {
    INT0,       /* External Interrupt Request 0 */
    INT1,       /* External Interrupt Request 1 */
    INT2,       /* External Interrupt Request 2 */
    INT3,       /* External Interrupt Request 3 */
    INT4,       /* External Interrupt Request 4 */
    INT5,       /* External Interrupt Request 5 */
    INT6,       /* External Interrupt Request 6 */
    INT7,       /* External Interrupt Request 7 */
};  /* EIMSK: External Interrupt Mask Register */

enum {
    INTF0,      /* External Interrupt Flag 0 */
    INTF1,      /* External Interrupt Flag 1 */
    INTF2,      /* External Interrupt Flag 2 */
    INTF3,      /* External Interrupt Flag 3 */
    INTF4,      /* External Interrupt Flag 4 */
    INTF5,      /* External Interrupt Flag 5 */
    INTF6,      /* External Interrupt Flag 6 */
    INTF7,      /* External Interrupt Flag 7 */
};  /* EIFR: External Interrupt Flag Register */

#endif    /* EXTI_REG_H */