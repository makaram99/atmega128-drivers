/******************************************************************************
 * @file        EXTI_cfg.h
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Configuration header file for \ref EXTI.c
 * @version     1.0.0
 * @date        2022-03-20
 * @copyright   Copyright (c) 2022
 ******************************************************************************/
#ifndef EXTI_CFG_H       
#define EXTI_CFG_H   

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                   CHANGE THIS PART TO YOUR NEEDS                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/******************************************************************************
 * @brief Determine if nesting is allowed in the interrupt service routines.
 *        Options are:
 *          NESTING_DISABLED --> nesting is not allowed
 *          NESTING_ENABLED --> nesting is allowed
 *****************************************************************************/
#define NESTING     NESTING_ENABLED


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*              DO NOT CHANGE ANYTHING BELOW THIS COMMENT                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#define NESTING_ENABLED  1
#define NESTING_DISABLED 0

#endif                  
