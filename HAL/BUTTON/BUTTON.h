/******************************************************************************
 * @file        BUTTON.h
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Interfaces header file for \ref BUTTON.c
 * @version     1.0.0
 * @date        2022-03-20
 * @copyright   Copyright (c) 2022
 ******************************************************************************/
#ifndef BUTTON_H       
#define BUTTON_H       

/*------------------------------------------------------------------------------*/
/*                                  TYPEDEFs                                    */
/*------------------------------------------------------------------------------*/
typedef enum{
    BUTTON_0,
    BUTTON_1,
    BUTTON_2,
    BUTTON_3,
    BUTTON_4,
    BUTTON_5,
    BUTTON_6,
    BUTTON_7
}BUTTON_t;





/*------------------------------------------------------------------------------*/
/*                                  API's                                       */
/*------------------------------------------------------------------------------*/

/********************************************************************************
 * @brief Initializes Buttons connected to DIO
 ********************************************************************************/
void BUTTON_Init(void);

/********************************************************************************
 * @brief Check whether a specific button is pressed or not
 * @param[in] button: Button number: options from \ref BUTTON_t enum in BUTTON.h file
 * @return State of the button: \ref HIGH if pressed and \ref LOW if not, member of \ref STATE_t enum
 * @par For example:
 *      @code 
 *      BUTTON_Read(BUTTON_0);   //returns \ref HIGH if button 0 is pressed and \ref LOW otherwise
 *      @endcode
 ********************************************************************************/
STATE_t BUTTON_Read(BUTTON_t button);


#endif    /* BUTTON_H */       
