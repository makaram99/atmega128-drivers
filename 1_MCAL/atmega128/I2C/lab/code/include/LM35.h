/******************************************************************************
 * @file            LM35.h
 * @author          Mahmoud Karam (ma.karam272@gmail.com)
 * @brief           Interface file for LM35 temperature sensor
 * @version         1.0.0
 * @date            2022-07-02
 * PRECONDITIONS:   - LM35.c must be included in the project
 * @copyright       Copyright (c) 2022
 ******************************************************************************/
#ifndef LM35_H
#define LM35_H

/*------------------------------------------------------------------------------*/
/*                                                                              */
/*                                  TYPEDEFS                                    */
/*                                                                              */
/*------------------------------------------------------------------------------*/

typedef enum {
    LM35_0,
} LM35_t;

/*------------------------------------------------------------------------------*/
/*                                                                              */
/*                             API FUNCTIONS                                    */
/*                                                                              */
/*------------------------------------------------------------------------------*/

/*******************************************************************************
 * @brief       Initialize LM35 configurations based on user configurations in 
 *              LM35_cfg.h and LM35_cfg.c
 ******************************************************************************/
ERROR_t LM35_Init(void);
ERROR_t LM35_Read(const LM35_t lm35, u8_t * const ptrToValue);
ERROR_t LM35_ReadAsync(const LM35_t lm35, u8_t * const ptrToValue, void (* const LM35_Callback) (void));
#define LM35_Enable()       (ADC_Enable())
#define LM35_Disable()      (ADC_Disable())
void LM35_ISR(void);


#endif      /* LM35_H */