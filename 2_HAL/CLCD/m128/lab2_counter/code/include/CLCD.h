/******************************************************************************
 * @file            CLCD.h
 * @author          Mahmoud Karam (ma.karam272@gmail.com)
 * @brief           Interface file forthe CLCD module
 * @version         1.0.0
 * @date            2022-06-18
 * PRECONDITIONS:   - CLCD.c must be included in the project
 *                  - CLCD.h must be included in the project
 * @copyright       Copyright (c) 2022
 ******************************************************************************/
#ifndef CLCD_H
#define CLCD_H

/*------------------------------------------------------------------------------*/
/*                                                                              */
/*                                  TYPEDEFS                                    */
/*                                                                              */
/*------------------------------------------------------------------------------*/

typedef enum {
    CLCD_LINE_1,
    CLCD_LINE_2,
} CLCD_LINE_t;

/*------------------------------------------------------------------------------*/
/*                                                                              */
/*                             API FUNCTIONS                                    */
/*                                                                              */
/*------------------------------------------------------------------------------*/

/*******************************************************************************
 * @brief       Initializes the CLCD module
 ******************************************************************************/
ERROR_t CLCD_Init(void);

/*******************************************************************************
 * @brief       Write a charachter to the CLCD in xy position
 * @param[in]   ch:     The character to be written
 * @param[in]   line:   The line to be written to. CLCD_LINE_1 or CLCD_LINE_2
 * @param[in]   col:    The column to be written to. 0-15
 * @return      ERROR_t: Error code. See \ref ERROR_t for more information.
 * @note        The cursor position is incremented after writing the character
 *              to the CLCD.
 ******************************************************************************/
ERROR_t CLCD_WriteCharInXY(const char ch, const CLCD_LINE_t line, const u8_t col);

/*******************************************************************************
 * @brief       Write a charachter to the CLCD in the current cursor position
 * @param[in]   ch:     The character to be written
 * @return      ERROR_t: Error code. See \ref ERROR_t for more information.
 * @note        The cursor position is incremented after writing the character
 *              to the CLCD.
 ******************************************************************************/
ERROR_t CLCD_WriteChar(const char ch);

/*******************************************************************************
 * @brief       Write a string to the CLCD in xy position
 * @param[in]   str:    Pointer to the string to be written
 * @param[in]   line:   The line to be written to. CLCD_LINE_1 or CLCD_LINE_2
 * @param[in]   col:    The column to be written to. 0-15
 * @return      ERROR_t: Error code. See \ref ERROR_t for more information.
 * @note        The cursor position is incremented after writing the string
 *              to the CLCD and points to the position after the last character
 *              of the string.
 ******************************************************************************/
ERROR_t CLCD_WriteStringInXY(const char * const str, const CLCD_LINE_t line, const u8_t col);

/*******************************************************************************
 * @brief       Write a string to the CLCD in the current cursor position
 * @param[in]   str:    Pointer to the string to be written
 * @return      ERROR_t: Error code. See \ref ERROR_t for more information.
 * @note        The cursor position is incremented after writing the string
 *              to the CLCD and points to the position after the last character
 *              of the string.
 ******************************************************************************/
ERROR_t CLCD_WriteString(const char * const str);

ERROR_t CLCD_CreateCustomChar(const char * const ch, const u8_t index);
ERROR_t CLCD_WriteCustomCharInXY(const u8_t index, const CLCD_LINE_t line, const u8_t col);
ERROR_t CLCD_WriteCustomChar(const u8_t index);

ERROR_t CLCD_WriteIntegerInXY(const s32_t number, const CLCD_LINE_t line, const u8_t col);
ERROR_t CLCD_WriteInteger(const s32_t number);

/*******************************************************************************
 * @brief       Clears the CLCD screen
 ******************************************************************************/
ERROR_t CLCD_Clr(void);

/*******************************************************************************
 * @brief       Returns the cursor to the home position (line 1, col 0)
 * @return      ERROR_t: Error code. See \ref ERROR_t for more information.
 ******************************************************************************/
ERROR_t CLCD_ReturnHome(void);

/*******************************************************************************
 * @brief       Shift the CLCD screen to the right by one character.
 * @return      ERROR_t: Error code. See \ref ERROR_t for more information.
 * @note        The cursor position does not change.
 ******************************************************************************/
ERROR_t CLCD_ShiftRight(void);

/*******************************************************************************
 * @brief       Shift the CLCD screen to the left by one character.
 * @return      ERROR_t: Error code. See \ref ERROR_t for more information.
 * @note        The cursor position does not change.
 ******************************************************************************/
ERROR_t CLCD_ShiftLeft(void);

/*******************************************************************************
 * @brief       Set the cursor position to the xy position
 * @param[in]   line:   The line to be written to. CLCD_LINE_1 or CLCD_LINE_2
 * @param[in]   col:    The column to be written to. 0-15
 * @return      ERROR_t: Error code. See \ref ERROR_t for more information.
 ******************************************************************************/
ERROR_t CLCD_SetCursorPosition(const CLCD_LINE_t line, const u8_t col);

ERROR_t CLCD_TurnOn(void);

ERROR_t CLCD_TurnOff(void);

ERROR_t CLCD_CurosrOn(void);

ERROR_t CLCD_CursorOff(void);

ERROR_t CLCD_CursorBlinkOn(void);

ERROR_t CLCD_CursorBlinkOff(void);


#endif      /* CLCD_H */                
