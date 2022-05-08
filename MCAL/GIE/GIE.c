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
    CLR_BIT(SREG, I_BIT);
}

void GIE_Enable(void) {
    SET_BIT(SREG, I_BIT);
}
