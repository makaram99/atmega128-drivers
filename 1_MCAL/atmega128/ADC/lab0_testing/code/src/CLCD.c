/******************************************************************************
 * @file        CLCD.c
 * @author      Mahmoud Karam Emara (ma.karam272@gmail.com)
 * @brief       Keypad module driver. It has the implementation file for 
 *              \ref CLCD.h.
 * @version     1.0.0
 * @date        2022-06-17
 * @copyright   Mahmoud Karam Emara 2022, MIT License
 ******************************************************************************/
#include <util/delay.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO.h"
#include "CLCD_cfg.h"
#include "CLCD.h"

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                              TYPES DEFINITIONS                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/
typedef enum {
    SEND_MODE_COMMAND,
    SEND_MODE_DATA
} SEND_MODE_t;

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                         PRIVATE VARIABLES                                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/
static u8_t CLCD_DisplayMode = CLCD_DISPLAY_MODE;

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                         PRIVATE FUNCTIONS PROTOTYPES                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/
static ERROR_t CLCD_Send(const u8_t byte, const SEND_MODE_t sendingMode);

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                              PUBLIC FUNCTIONS                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

ERROR_t CLCD_Init(void) {
    ERROR_t error = ERROR_OK;

    /* Wait for the CLCD to be ready */
    _delay_ms(30);

    /* Set the CLCD to 8-bit mode */ 
    error |= CLCD_Send(CLCD_CMD_8_BIT_2_LINES_8_DOTS, SEND_MODE_COMMAND);
    _delay_us(4100);
    error |= CLCD_Send(CLCD_CMD_8_BIT_2_LINES_8_DOTS, SEND_MODE_COMMAND);
    _delay_us(100);
    error |= CLCD_Send(CLCD_CMD_8_BIT_2_LINES_8_DOTS, SEND_MODE_COMMAND);
    _delay_us(1);
    
    /* Initialize the CLCD according to the CLCD_cfg.h file */
    error |= CLCD_Send(CLCD_CMD_CLEAR_DISPLAY, SEND_MODE_COMMAND);
    error |= CLCD_Send(CLCD_CMD_RETURN_HOME, SEND_MODE_COMMAND);
    error |= CLCD_Send(CLCD_DisplayMode, SEND_MODE_COMMAND);
    error |= CLCD_Send(CLCD_ENTRY_MODE_SET, SEND_MODE_COMMAND); 
    error |= CLCD_Send(CLCD_OPERATING_MODE, SEND_MODE_COMMAND);

    return error;
}

ERROR_t CLCD_WriteChar(const char ch) {
    return CLCD_Send(ch, SEND_MODE_DATA);
}

ERROR_t CLCD_WriteCharInXY(const char ch, const CLCD_LINE_t line, const u8_t col) {
    ERROR_t error = ERROR_OK;

    error |= CLCD_SetCursorPosition(line, col);
    error |= CLCD_Send(ch, SEND_MODE_DATA);
    
    return error;
}

ERROR_t CLCD_CreateCustomChar(const char * const ch, const u8_t index) {
    ERROR_t error = ERROR_OK;
    u8_t i = 0;
    const u8_t MEMORY_SIZE_FOR_CHARACTER_IN_CGRAM = 8;

    for(i = 0; i < MEMORY_SIZE_FOR_CHARACTER_IN_CGRAM; ++i) {
        error |= CLCD_Send(CLCD_CMD_SET_CGRAM_ADDRESS | (index << 3) | i, SEND_MODE_COMMAND);
        error |= CLCD_Send(ch[i], SEND_MODE_DATA);
    }

    return error;
}

ERROR_t CLCD_WriteCustomChar(const u8_t index) {
    return CLCD_Send(index, SEND_MODE_DATA);
}

ERROR_t CLCD_WriteCustomCharInXY(const u8_t index, const CLCD_LINE_t line, const u8_t col) {
    ERROR_t error = ERROR_OK;

    error |= CLCD_SetCursorPosition(line, col);
    error |= CLCD_Send(index, SEND_MODE_DATA);
    
    return error;
}

ERROR_t CLCD_WriteString(const char * const str) {
    ERROR_t error = ERROR_OK;
    u8_t i = 0;

    while(str[i] != '\0') {
        error |= CLCD_WriteChar(str[i]);
        ++i;
    }

    return error;
}

ERROR_t CLCD_WriteStringInXY(const char * const str, const CLCD_LINE_t line, const u8_t col) {
    ERROR_t error = ERROR_OK;
    
    error |= CLCD_SetCursorPosition(line, col);
    error |= CLCD_WriteString(str);

    return error;
}

ERROR_t CLCD_WriteInteger(const s64_t number) {
    ERROR_t error = ERROR_OK;
    s64_t Loc_s64Number = number, multiplier = 0;
    u8_t digit = 0;
    u8_t count = 0, i = 0;

    /* Printing the negative sign */
    if(number < 0) {
        CLCD_WriteChar('-');
        Loc_s64Number = -number;
    }

    /* Get the number of digits in the number */
    do{
        Loc_s64Number /= 10;
        ++count;
    } while(Loc_s64Number);

    /* Write the number */
    Loc_s64Number = (number >= 0 ? number : -number);
    while(count) {
        multiplier = 1; 
        i = 0;
        while(i < (count - 1)) {
            multiplier *= 10;
            ++i;
        }        

        digit = Loc_s64Number / multiplier;
        Loc_s64Number %= multiplier;
        error |= CLCD_WriteChar(digit + '0');
        --count;
    }

    return error;
}

ERROR_t CLCD_WriteIntegerInXY(const s64_t number, const CLCD_LINE_t line, const u8_t col) {
    ERROR_t error = ERROR_OK;
    
    error |= CLCD_SetCursorPosition(line, col);
    error |= CLCD_WriteInteger(number);

    return error;
}

ERROR_t CLCD_WriteFloat(const f32_t number, const u8_t precision) {
    ERROR_t error = ERROR_OK;
    f32_t Loc_f32Number = number;
    f32_t fraction = 0.0f;
    u64_t decimal = 0;
    u8_t i = 0;

    /* Printing the negative sign */
    if(Loc_f32Number < 0) {
        error |= CLCD_WriteChar('-');
        Loc_f32Number = -Loc_f32Number;
    }

    /*!< Getting the integer, and the fractional part */
    decimal = (u32_t)Loc_f32Number;
    fraction = Loc_f32Number - decimal;
    for(i = 0; i < precision; ++i) {
        fraction *= 10;
    }

    /*!< Printing the decimal, then the fractional part */
    error |= CLCD_WriteInteger(decimal);
    error |= CLCD_WriteChar('.');
    error |= CLCD_WriteInteger(fraction);

    return error;
}

ERROR_t CLCD_WriteFloatInXY(const f32_t number, const u8_t precision, const CLCD_LINE_t line, const u8_t col) {
    ERROR_t error = ERROR_OK;
    
    error |= CLCD_SetCursorPosition(line, col);
    error |= CLCD_WriteFloat(number, precision);

    return error;
}

ERROR_t CLCD_Clr(void) {
    return CLCD_Send(CLCD_CMD_CLEAR_DISPLAY, SEND_MODE_COMMAND);
}

ERROR_t CLCD_ReturnHome(void) {
    return CLCD_Send(CLCD_CMD_RETURN_HOME, SEND_MODE_COMMAND);
}

ERROR_t CLCD_SetCursorPosition(const CLCD_LINE_t line, const u8_t col) {
    return CLCD_Send(CLCD_CMD_SET_DDRAM_ADDRESS + ( (line * CLCD_LINE_2_OFFSET) + col), SEND_MODE_COMMAND);
}

ERROR_t CLCD_ShiftRight(void) {
    return CLCD_Send(CLCD_CMD_DISPLAY_MOVE_RIGHT, SEND_MODE_COMMAND);
}

ERROR_t CLCD_ShiftLeft(void) {
    return CLCD_Send(CLCD_CMD_DISPLAY_MOVE_LEFT, SEND_MODE_COMMAND);
}

ERROR_t CLCD_TurnOn(void) {
    CLCD_DisplayMode |= 0x4;
    return CLCD_Send(CLCD_DisplayMode, SEND_MODE_COMMAND);
}

ERROR_t CLCD_TurnOff(void) {
    CLCD_DisplayMode &= ~(0x4);
    return CLCD_Send(CLCD_DisplayMode, SEND_MODE_COMMAND);
}

ERROR_t CLCD_CursorOn(void) {
    CLCD_DisplayMode |= 0x2;
    return CLCD_Send(CLCD_DisplayMode, SEND_MODE_COMMAND);
}

ERROR_t CLCD_CursorOff(void) {
    CLCD_DisplayMode &= ~(0x2);
    return CLCD_Send(CLCD_DisplayMode, SEND_MODE_COMMAND);
}

ERROR_t CLCD_CursorBlinkOn(void) {
    CLCD_DisplayMode |= 0x3;
    return CLCD_Send(CLCD_DisplayMode, SEND_MODE_COMMAND);
}

ERROR_t CLCD_CursorBlinkOff(void) {
    CLCD_DisplayMode &= ~(0x3);
    return CLCD_Send(CLCD_DisplayMode, SEND_MODE_COMMAND);
}



/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                              PRIVATE FUNCTIONS                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/
static ERROR_t CLCD_Send(const u8_t byte, const SEND_MODE_t sendingMode) {
    ERROR_t error = ERROR_OK;

    /* Setting Control pins */
    if (sendingMode == SEND_MODE_COMMAND) {
        error |= DIO_SetPinValue(CLCD_Pins.RS, LOW);      
    } else {
        error |= DIO_SetPinValue(CLCD_Pins.RS, HIGH);
    }

    #if (CLCD_RW_PIN_USED)
        error |= DIO_SetPinValue(CLCD_Pins.RW, LOW);
    #endif

    /* Sending the command on the data pins */
    #if (MODE_4_BITS_USED) 
        error |= DIO_SetPinValue(CLCD_Pins.D4, BIT_READ(byte, 4));
        error |= DIO_SetPinValue(CLCD_Pins.D5, BIT_READ(byte, 5));
        error |= DIO_SetPinValue(CLCD_Pins.D6, BIT_READ(byte, 6));
        error |= DIO_SetPinValue(CLCD_Pins.D7, BIT_READ(byte, 7));

        /* Triggering the E pin */
        error |= DIO_SetPinValue(CLCD_Pins.E, HIGH);
        _delay_us(100);
        error |= DIO_SetPinValue(CLCD_Pins.E, LOW);
        _delay_ms(2);

        error |= DIO_SetPinValue(CLCD_Pins.E, HIGH);
        error |= DIO_SetPinValue(CLCD_Pins.D4, BIT_READ(byte, 0));
        error |= DIO_SetPinValue(CLCD_Pins.D5, BIT_READ(byte, 1));
        error |= DIO_SetPinValue(CLCD_Pins.D6, BIT_READ(byte, 2));
        error |= DIO_SetPinValue(CLCD_Pins.D7, BIT_READ(byte, 3));
    #else
        error |= DIO_SetPinValue(CLCD_Pins.D0, BIT_READ(byte, 0));
        error |= DIO_SetPinValue(CLCD_Pins.D1, BIT_READ(byte, 1));
        error |= DIO_SetPinValue(CLCD_Pins.D2, BIT_READ(byte, 2));
        error |= DIO_SetPinValue(CLCD_Pins.D3, BIT_READ(byte, 3));
        error |= DIO_SetPinValue(CLCD_Pins.D4, BIT_READ(byte, 4));
        error |= DIO_SetPinValue(CLCD_Pins.D5, BIT_READ(byte, 5));
        error |= DIO_SetPinValue(CLCD_Pins.D6, BIT_READ(byte, 6));
        error |= DIO_SetPinValue(CLCD_Pins.D7, BIT_READ(byte, 7));
    #endif

    /* Triggering the E pin */
    error |= DIO_SetPinValue(CLCD_Pins.E, HIGH);
    _delay_us(100);
    error |= DIO_SetPinValue(CLCD_Pins.E, LOW);   
    _delay_ms(2);   

    return error;
}

