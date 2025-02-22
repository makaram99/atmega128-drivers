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
 * @brief       Write a charachter to the CLCD in the current cursor position
 * @param[in]   ch:     The character to be written
 * @return      ERROR_t: Error code. See \ref ERROR_t for more information.
 * @note        The cursor position is incremented after writing the character
 *              to the CLCD.
 * @par         Example:
 *              @code
 *              CLCD_WriteChar('A');
 *              @endcode
 ******************************************************************************/
ERROR_t CLCD_WriteChar(const char ch);

/*******************************************************************************
 * @brief       Write a charachter to the CLCD in xy position
 * @param[in]   ch:     The character to be written
 * @param[in]   line:   The line to be written to. CLCD_LINE_1 or CLCD_LINE_2
 * @param[in]   col:    The column to be written to. 0-15
 * @return      ERROR_t: Error code. See \ref ERROR_t for more information.
 * @note        The cursor position is incremented after writing the character
 *              to the CLCD.
 * @par         Example:
 *              @code
 *              CLCD_WriteCharInXY('A', CLCD_LINE_1, 0);
 *              @endcode
 ******************************************************************************/
ERROR_t CLCD_WriteCharInXY(const char ch, const CLCD_LINE_t line, const u8_t col);

/*******************************************************************************
 * @brief       Write a string to the CLCD in the current cursor position
 * @param[in]   str:    Pointer to the string to be written
 * @return      ERROR_t: Error code. See \ref ERROR_t for more information.
 * @note        The cursor position is incremented after writing the string
 *              to the CLCD and points to the position after the last character
 *              of the string.
 * @par         Example:
 *              @code
 *              CLCD_WriteString("Hello");
 *              @endcode
 * @warning     The string must be null terminated.
 ******************************************************************************/
ERROR_t CLCD_WriteString(const char * const str);

/*******************************************************************************
 * @brief       Write a string to the CLCD in xy position
 * @param[in]   str:    Pointer to the string to be written
 * @param[in]   line:   The line to be written to. CLCD_LINE_1 or CLCD_LINE_2
 * @param[in]   col:    The column to be written to. 0-15
 * @return      ERROR_t: Error code. See \ref ERROR_t for more information.
 * @note        The cursor position is incremented after writing the string
 *              to the CLCD and points to the position after the last character
 *              of the string.
 * @par         Example:
 *              @code
 *              CLCD_WriteStringInXY("Hello", CLCD_LINE_1, 0);
 *              @endcode
 * @warning     The string must be null terminated.
 ******************************************************************************/
ERROR_t CLCD_WriteStringInXY(const char * const str, const CLCD_LINE_t line, const u8_t col);

/*******************************************************************************
 * @brief       Create a custom character in the CLCD
 * @param[in]   ch:     Pointer to the array containing bytes of the character
 * @param[in]   index:  At which index the character will be stored in the LCd
 *                      CG RAM. 0-7
 * @return      ERROR_t: Error code. See \ref ERROR_t for more information.
 * @par         Example:
 *              @code
 *              u8_t ch[8] = {0x0f, 0x11, 0x00, 0x0C, 0x00, 0x0B, 0x05, 0x00};
 *              CLCD_CreateCustomCharacter(ch, 0);
 *              @endcode
 ******************************************************************************/
ERROR_t CLCD_CreateCustomChar(const char * const ch, const u8_t index);

/*******************************************************************************
 * @brief       Write a custom character to the CLCD in the current cursor position
 * @param[in]   ch:     The index of the custom character to be written
 * @return      ERROR_t: Error code. See \ref ERROR_t for more information.
 * @note        The cursor position is incremented after writing the character
 *              to the CLCD.
 * @par         Example:
 *              @code
 *              u8_t ch[8] = {0x0f, 0x11, 0x00, 0x0C, 0x00, 0x0B, 0x05, 0x00};
 *              CLCD_CreateCustomCharacter(ch, 0);
 *              CLCD_WriteCustomChar(0);
 *              @endcode
 * @warning     The custom character must be created before writing it to the
 *              CLCD.
 ******************************************************************************/
ERROR_t CLCD_WriteCustomChar(const u8_t index);

/*******************************************************************************
 * @brief       Write a custom character to the CLCD in xy position
 * @param[in]   index:  The index of the custom character in the CLCD CG RAM
 * @param[in]   line:   The line to be written to. See \ref CLCD_LINE_t for more
 *                      information.
 * @param[in]   col:    The column to be written to. 0-40
 * @return      ERROR_t: Error code. See \ref ERROR_t for more information.
 * @note        The cursor position is incremented after writing the character
 *              to the CLCD.
 * @par         Example:
 *              @code
 *              u8_t ch[8] = {0x0f, 0x11, 0x00, 0x0C, 0x00, 0x0B, 0x05, 0x00};
 *              CLCD_CreateCustomCharacter(ch, 0);
 *              CLCD_WriteCustomCharInXY(0, CLCD_LINE_1, 0);
 *              @endcode
 * @warning     The custom character must be created before writing it to the
 *              CLCD.
 ******************************************************************************/
ERROR_t CLCD_WriteCustomCharInXY(const u8_t index, const CLCD_LINE_t line, const u8_t col);

/*******************************************************************************
 * @brief       Write an integer to the CLCD in the current cursor position
 * @param[in]   number: The integer to be written
 * @return      ERROR_t: Error code. See \ref ERROR_t for more information.
 * @note        The cursor position is incremented after writing the integer
 *              to the CLCD.
 * @par         Example:
 *              @code
 *              CLCD_WriteInt(123);
 *              @endcode
 ******************************************************************************/
ERROR_t CLCD_WriteInteger(const s32_t number);

/*******************************************************************************
 * @brief       Write an integer to the CLCD in xy position
 * @param[in]   number: The integer to be written
 * @param[in]   line:   The line to be written to. See \ref CLCD_LINE_t for more
 *                      information.
 * @param[in]   col:    The column to be written to. 0-40
 * @return      ERROR_t: Error code. See \ref ERROR_t for more information.
 * @note        The cursor position is incremented after writing the integer
 *              to the CLCD.
 * @par         Example:
 *              @code
 *              CLCD_WriteIntInXY(123, CLCD_LINE_1, 0);
 *              @endcode
 ******************************************************************************/  
ERROR_t CLCD_WriteIntegerInXY(const s32_t number, const CLCD_LINE_t line, const u8_t col);

/*******************************************************************************
 * @brief       Write a float to the CLCD in the current cursor position
 * @param[in]   number: The float to be written
 * @param[in]   precision: The number of digits after the decimal point
 * @return      ERROR_t: Error code. See \ref ERROR_t for more information.
 * @note        The cursor position is incremented after writing the float
 *              to the CLCD.
 * @par         Example:
 *              @code
 *              CLCD_WriteFloat(3.1400, 2);   // Writes 3.14
 *              CLCD_WriteFloat(3.1400, 2);   // Writes 3.140
 *              @endcode
 ******************************************************************************/
ERROR_t CLCD_WriteFloat(const f32_t number, const u8_t precision);

/*******************************************************************************
 * @brief       Write a float to the CLCD in xy position
 * @param[in]   number: The float to be written
 * @param[in]   precision: The number of digits after the decimal point
 * @param[in]   line:   The line to be written to. See \ref CLCD_LINE_t for more
 *                      information.
 * @param[in]   col:    The column to be written to. 0-40
 * @return      ERROR_t: Error code. See \ref ERROR_t for more information.
 * @note        The cursor position is incremented after writing the float
 *              to the CLCD.
 * @par         Example:
 *              @code
 *              CLCD_WriteFloatInXY(3.1400, 2, CLCD_LINE_1, 0);   // Writes 3.14
 *              CLCD_WriteFloatInXY(3.1400, 2, CLCD_LINE_1, 2);   // Writes 3.140
 *              @endcode
 ******************************************************************************/ 
ERROR_t CLCD_WriteFloatInXY(const f32_t number, const u8_t precision, const CLCD_LINE_t line, const u8_t col);

/*******************************************************************************
 * @brief       Clears the CLCD screen
 * @return      ERROR_t: Error code. See \ref ERROR_t for more information.
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

/*******************************************************************************
 * @brief       Turn on the CLCD pixels.
 * @return      ERROR_t: Error code. See \ref ERROR_t for more information.
 ******************************************************************************/
ERROR_t CLCD_TurnOn(void);

/*******************************************************************************
 * @brief       Turn off the CLCD pixels.
 * @return      ERROR_t: Error code. See \ref ERROR_t for more information.
 ******************************************************************************/
ERROR_t CLCD_TurnOff(void);

/*******************************************************************************
 * @brief       Turn on the CLCD cursor.
 * @return      ERROR_t: Error code. See \ref ERROR_t for more information.
 ******************************************************************************/
ERROR_t CLCD_CursorOn(void);

/*******************************************************************************
 * @brief       Turn off the CLCD cursor.
 * @return      ERROR_t: Error code. See \ref ERROR_t for more information.
 ******************************************************************************/
ERROR_t CLCD_CursorOff(void);

/*******************************************************************************
 * @brief       Enable blinking of the cursor.
 * @return      ERROR_t: Error code. See \ref ERROR_t for more information.
 ******************************************************************************/
ERROR_t CLCD_CursorBlinkOn(void);

/*******************************************************************************
 * @brief       Disable blinking of the cursor.
 * @return      ERROR_t: Error code. See \ref ERROR_t for more information.
 ******************************************************************************/
ERROR_t CLCD_CursorBlinkOff(void);


#endif      /* CLCD_H */                
