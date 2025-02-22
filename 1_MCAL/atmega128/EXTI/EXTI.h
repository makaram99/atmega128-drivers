/******************************************************************************
 * @file        EXTI.h
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Interfaces header file for \ref EXTI.c
 * @version     1.0.0
 * @date        2022-03-20
 * @copyright   Copyright (c) 2022
 ******************************************************************************/
#ifndef EXTI_H       
#define EXTI_H   

/*------------------------------------------------------------------------------*/
/*                                                                              */
/*                                  TYPEDEFS                                    */
/*                                                                              */
/*------------------------------------------------------------------------------*/

typedef enum{
    FALLING_EDGE,
    RISING_EDGE,
    LOW_LEVEL_DETECT,
    LOGIC_CHANGE
}EXTI_SENSITIVITY_t;

typedef enum{
    EXTI_0,
    EXTI_1,
    EXTI_2,
    EXTI_3,
    EXTI_4,
    EXTI_5,
    EXTI_6,
    EXTI_7,
    NUM_OF_EXTI_CHANNELS
}EXTI_t;

/*------------------------------------------------------------------------------*/
/*                                                                              */
/*                             API FUNCTIONS PROTOTYPES                         */
/*                                                                              */
/*------------------------------------------------------------------------------*/

/******************************************************************************
 * @brief Initialize an EXTI pin with a given sensitivity and callback function
 * @param[in] extiNumber: The EXTI pin to initialize (EXTI0 - EXTI7)
 * @param[in] sensitivity: The sensitivity of the EXTI pin (FALLING_EDGE, RISING_EDGE, LOW_LEVEL_DETECT, LOGIC_CHANGE)
 * @param[in] callbackPtr: The callback function to be called when the EXTI pin is triggered
 *****************************************************************************/
void EXTI_Init(const EXTI_t extiNumber, const EXTI_SENSITIVITY_t  sensitivity, void (* const callbackPtr)(void));

/******************************************************************************
 * @brief Enable an EXTI pin (EXTI0 - EXTI7)
 * @param[in] extiNumber: The EXTI pin to enable (EXTI0 - EXTI7)
 *****************************************************************************/
void EXTI_EnableExternalInterrupt(const EXTI_t extiNumber);

/******************************************************************************
 * @brief Disable an EXTI pin (EXTI0 - EXTI7)
 * @param[in] extiNumber: The EXTI pin to disable (EXTI0 - EXTI7)
 *****************************************************************************/
void EXTI_DisableExternalInterrupt(const EXTI_t extiNumber);

#endif                  
