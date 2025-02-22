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
/*                                                                              */
/*                                  TYPEDEFs                                    */
/*                                                                              */
/*------------------------------------------------------------------------------*/
typedef enum{
    BUTTON_0,
    NUM_OF_BUTTONS
}BUTTON_t;

typedef enum{
    DEBOUNCE_OFF,
    DEBOUNCE_ON
}DEBOUNCE_t;





/*------------------------------------------------------------------------------*/
/*                                                                              */
/*                                  API's                                       */
/*                                                                              */
/*------------------------------------------------------------------------------*/

/********************************************************************************
 * @brief       Initializes Buttons connected to DIO
 * @return      ERROR_t: error state. See \ref ERROR_t to see error possibilities.
 ********************************************************************************/
ERROR_t BUTTON_Init(void);

/********************************************************************************
 * @brief       Check whether a specific button is pressed or not
 * @param[in]   button:     Button number: See options in \ref BUTTON_t enum in 
 *                          BUTTON.h file.
 * @param[out]  ptrToState: Pointer to a variable that will hold the state of the 
 *                          button. See \ref STATE_t to know return possibilities.
 * @return      ERROR_t:    error state. See \ref ERROR_t for more information.
 * @par         Example:
 *              @code 
 *              // Set \ref ptrToState to \ref HIGH if button 0 is pressed and 
 *              // \ref LOW otherwise
 *              BUTTON_Read(BUTTON_0, &state);
 *              @endcode
 ********************************************************************************/
ERROR_t BUTTON_Read(const BUTTON_t button, STATE_t * const ptrToState);

/******************************************************************************
 * @brief       Set Or Clear the internal Pullup resistor of the button
 * 
 * @param[in]   button:     The button to set/clear the pullup resistor of
 * @param[in]   pullup:     The state of the pullup resistor.
 * @return      ERROR_t:    error code. See \ref ERROR_t for more information.
 ******************************************************************************/
ERROR_t BUTTON_SetClrPullup(const BUTTON_t button, const DIO_PULLUP_t pullup);

/********************************************************************************
 * @brief       Set the internal pull-up resistor of a specific button
 * 
 * @param[in]   button:     Button number: See options in \ref BUTTON_t enum in
 *                          BUTTON.h file.
 * @return      ERROR_t:    error state. See \ref ERROR_t for more information.
 ********************************************************************************/
#define BUTTON_SetPullup(button)     ( BUTTON_SetClrPullup(button, DIO_PULLUP_ON) )

/********************************************************************************
 * @brief       Remove the internal pull-up resistor of a specific button
 * 
 * @param[in]   button:     Button number: See options in \ref BUTTON_t enum in
 *                          BUTTON.h file.
 * @return      ERROR_t:    error state. See \ref ERROR_t for more information.
 ********************************************************************************/
#define BUTTON_ClrPullup(button)    ( BUTTON_SetClrPullup(button, DIO_PULLUP_OFF) )

/********************************************************************************
 * @brief       Set or Clear the debounce of a specific button
 * 
 * @param[in]   button:     Button number: See options in \ref BUTTON_t enum in
 *                          BUTTON.h file.
 * @param[in]   debounce:   The state of the debounce.
 * @return      ERROR_t:    error state. See \ref ERROR_t for more information.
 ********************************************************************************/
ERROR_t BUTTON_SetClrDebounce(const BUTTON_t button, const DEBOUNCE_t debounce);

/********************************************************************************
 * @brief       Set the debounce of a specific button
 * 
 * @param[in]   button:     Button number: See options in \ref BUTTON_t enum in
 *                          BUTTON.h file.
 * @return      ERROR_t:    error state. See \ref ERROR_t for more information.
 ********************************************************************************/
#define BUTTON_SetDebounce(button)  ( BUTTON_SetClrDebounce(button, DEBOUNCE_ON) )

/********************************************************************************
 * @brief       Clear the debounce of a specific button
 * 
 * @param[in]   button:     Button number: See options in \ref BUTTON_t enum in
 *                          BUTTON.h file.
 * @return      ERROR_t:    error state. See \ref ERROR_t for more information.
 ********************************************************************************/
#define BUTTON_ClrDebounce(button) ( BUTTON_SetClrDebounce(button, DEBOUNCE_OFF) )

#endif    /* BUTTON_H */       
