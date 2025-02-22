/******************************************************************************
 * @file        GIE.h
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Interfaces header file for \ref GIE.c
 * @version     1.0.0
 * @date        2022-03-20
 * @copyright   Copyright (c) 2022
 ******************************************************************************/
#ifndef GIE_H       
#define GIE_H      

/******************************************************************************
 * @brief Global Interrupt Enable (GIE)
 *****************************************************************************/
void GIE_Enable(void);

/******************************************************************************
 * @brief Global Interrupt Disable (GID)
 *****************************************************************************/
void GIE_Disable(void);


#endif                  
