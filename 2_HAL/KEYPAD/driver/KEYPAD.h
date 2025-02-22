/******************************************************************************
 * @file            KEYPAD.h
 * @author          Mahmoud Karam (ma.karam272@gmail.com)
 * @brief           Interface file forthe KEYPAD module
 * @version         1.0.0
 * @date            2022-06-18
 * PRECONDITIONS:   - KEYPAD.c must be included in the project
 *                  - KEYPAD.h must be included in the project
 * @copyright       Copyright (c) 2022
 ******************************************************************************/
#ifndef KEYPAD_H
#define KEYPAD_H       

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                             TYPE DEFINITIONS                               */
/*                                                                            */
/*----------------------------------------------------------------------------*/

typedef enum {
    KEYPAD_0,
}KEYPAD_t;

/*******************************************************************************
 * @brief       Initialization of the KEYPAD module.
 * 
 * @return      ERROR_t: error code. See \ref ERROR_t for more information. 
 ******************************************************************************/
ERROR_t KEYPAD_Init(void);

/*******************************************************************************
 * @brief       Reads the pressed key from the KEYPAD module (if any).
 * 
 * @param[out]  data: pointer to the pressed key.
 *              - NULL_BYTE: if no key is pressed.
 *              - other value: the pressed key.
 * 
 * @return      ERROR_t: error code. See \ref ERROR_t for more information. 
 ******************************************************************************/
ERROR_t KEYPAD_Read(const KEYPAD_t keypad, u8_t * const data);

/*******************************************************************************
 * @brief       Wait until a key is pressed.
 * 
 * @param[out]  data: pointer to the pressed key.
 * 
 * @return      ERROR_t: error code. See \ref ERROR_t for more information.
 ******************************************************************************/
ERROR_t KEYPAD_WaitUntilPressed(const KEYPAD_t keypad, u8_t * const data);

/*******************************************************************************
 * @brief       Set the debounce delay time in milliseconds.
 * 
 * @param[in]   debounceTimeMs: debounce delay time in milliseconds.
 * 
 * @return      ERROR_t: error code. See \ref ERROR_t for more information.
 ******************************************************************************/
ERROR_t KEYPAD_SetDebounceTime(const u8_t debounceTimeMs);


#endif      /* KEYPAD_H */                
