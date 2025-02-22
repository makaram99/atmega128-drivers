/**************************************************************************
 * @file        GIE.c
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Global Interrupt Enable (GIE) 
 * @version     1.0.0
 * @date        2022-02-11
 * @copyright   Copyright (c) 2022
 ***************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GIE_reg.h"
#include "GIE.h"

void GIE_Disable(void) {
    BIT_CLR(SREG, I_BIT);
}

void GIE_Enable(void) {
    BIT_SET(SREG, I_BIT);
}
