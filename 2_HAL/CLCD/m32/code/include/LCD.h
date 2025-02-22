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

typedef enum {
    CLCD_LINE_1,
    CLCD_LINE_2,
} CLCD_LINE_t;



ERROR_t CLCD_Init(void);
ERROR_t CLCD_WriteCharInXY(const char ch, const CLCD_LINE_t line, const u8_t col);
ERROR_t CLCD_WriteChar(const char ch);
ERROR_t CLCD_WriteStringInXY(const char * const str, const CLCD_LINE_t line, const u8_t col);
ERROR_t CLCD_WriteString(const char * const str);
ERROR_t CLCD_Clr(void);
ERROR_t CLCD_SetCursorPosition(const CLCD_LINE_t line, const u8_t col);

#endif      /* CLCD_H */                
