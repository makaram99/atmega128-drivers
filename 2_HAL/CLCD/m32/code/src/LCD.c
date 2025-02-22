/******************************************************************************
 * @file        CLCD.c
 * @author      Mahmoud Karam Emara (ma.karam272@gmail.com)
 * @brief       Keypad module driver. It has the implementation file for 
 *              \ref CLCD.h.
 * @version     1.0.0
 * @date        2022-06-17
 * @copyright   Mahmoud Karam Emara 2022, MIT License
 ******************************************************************************/
#include "util/delay.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO.h"
#include "CLCD_cfg.h"
#include "CLCD.h"


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                         PRIVATE FUNCTIONS PROTOTYPES                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/
static ERROR_t CLCD_SendCommand(const u8_t cmd);
static ERROR_t CLCD_SendData(const char data);

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                              PUBLIC FUNCTIONS                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

ERROR_t CLCD_Init(void) {
    ERROR_t error = ERROR_OK;

    /* Wait for the CLCD to be ready */
    _delay_ms(30);      

    error |= CLCD_SendCommand(CLCD_OPERATING_MODE);
    error |= CLCD_SendCommand(CLCD_DISPLAY_MODE);
    error |= CLCD_SendCommand(CLCD_CMD_CLEAR_DISPLAY);
    error |= CLCD_SendCommand(CLCD_ENTRY_MODE_SET);


    return error;
}

ERROR_t CLCD_WriteCharInXY(const char ch, const CLCD_LINE_t line, const u8_t col) {
    ERROR_t error = ERROR_OK;

    /* Set DDRAM Address (cursor position): line0 from 0x0 to 0xf, line1 from CLCD_LINE_2_OFFSET to 0x4f */
    if(line == CLCD_LINE_1) {
        error |= CLCD_SendCommand(CLCD_CMD_SET_DDRAM_ADDRESS | col);
    } else if(line == CLCD_LINE_2) {
        error |= CLCD_SendCommand(CLCD_CMD_SET_DDRAM_ADDRESS | (col + CLCD_LINE_2_OFFSET));
    }

    /* Write data to DDRAM */
    error |= CLCD_SendData(ch);

    return error;
}

ERROR_t CLCD_WriteChar(const char ch) {
    /* Write data to DDRAM */
    return CLCD_SendData(ch);
}

ERROR_t CLCD_WriteStringInXY(const char * const str, const CLCD_LINE_t line, const u8_t col) {
    ERROR_t error = ERROR_OK;
    u8_t i = 0;

    while(str[i] != '\0') {
        error |= CLCD_WriteCharInXY(str[i], line, col + i);
        ++i;
    }

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

ERROR_t CLCD_WriteIntegerInXY(const s32_t number, const CLCD_LINE_t line, u8_t col) {
    ERROR_t error = ERROR_OK;
    s32_t Loc_s32Number = number;
    u8_t digit = 0;

    if(Loc_s32Number < 0) {
        CLCD_WriteCharInXY('-', line, col);
        ++col;
        Loc_s32Number = -Loc_s32Number;
    }

    do {        /* Using do-while to handle the case of 0   */
        digit = Loc_s32Number % 10;
        Loc_s32Number /= 10;
        error |= CLCD_WriteCharInXY(digit + '0', line, col);
        ++col;
    } while(Loc_s32Number && (ERROR_OK == error));

    return error;
}

ERROR_t CLCD_WriteInteger(const s32_t number) {
    ERROR_t error = ERROR_OK;
    s32_t Loc_s32Number = number;
    u8_t digit = 0;

    if(Loc_s32Number < 0) {
        CLCD_WriteChar('-');
        Loc_s32Number = -Loc_s32Number;
    }

    do {        /* Using do-while to handle the case of 0   */
        digit = Loc_s32Number % 10;
        Loc_s32Number /= 10;
        error |= CLCD_WriteChar(digit + '0');
    } while(Loc_s32Number && (ERROR_OK == error));

    return error;
}

ERROR_t CLCD_WriteFloat(const f32_t number, const u8_t precision) {
    ERROR_t error = ERROR_OK;
    f32_t Loc_f32Number = number;
    f32_t fraction = 0.0f;
    u32_t decimal = 0;
    u8_t digit = 0, i = 0;

    if(Loc_f32Number < 0) {
        CLCD_WriteChar('-');
        Loc_f32Number = -Loc_f32Number;
    }

    /*!< Printing the decimal part      */
    decimal = (u32_t)Loc_f32Number;
    fraction = Loc_f32Number - decimal;
    do {        /* Using do-while to handle the case of 0   */
        digit = decimal % 10;
        decimal /= 10;
        error |= CLCD_WriteChar(digit + '0');
    } while(Loc_f32Number && (ERROR_OK == error));

    /* Printing the fraction part       */
    while(i < precision) {
        digit = (u8_t)(fraction * 10);
        fraction = (fraction * 10) - digit;
        error |= CLCD_WriteChar(digit + '0');
    }

    return error;
}


ERROR_t CLCD_Clr(void) {
    ERROR_t error = ERROR_OK;

    error |= CLCD_SendCommand(CLCD_CMD_CLEAR_DISPLAY);

    return error;
}

ERROR_t CLCD_SetCursorPosition(const CLCD_LINE_t line, const u8_t col) {
    ERROR_t error = ERROR_OK;

    error |= CLCD_SendCommand(CLCD_CMD_SET_DDRAM_ADDRESS + ( (line * CLCD_LINE_2_OFFSET) + col));

    return error;
}

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                              PRIVATE FUNCTIONS                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/
static ERROR_t CLCD_SendCommand(const u8_t cmd) {
    ERROR_t error = ERROR_OK;

    /* Setting Control pins */
    error |= DIO_SetPinValue(RS_PIN, RS_PORT, LOW);      
    error |= DIO_SetPinValue(E_PIN, E_PORT, HIGH);   
    #if (RW_PIN_USED)
        error |= DIO_SetPinValue(RW_PIN, RW_PORT, LOW);
    #endif

    /* Sending the command on the data pins */
    #if (MODE_4_BITS_USED) && (DATA_PINS_ON_THE_SAME_PORT)
        error |= DIO_SetNibbleValue(START_DATA_PIN, DATA_PORT, cmd >> 4);

        /* Triggering the E pin */
        error |= DIO_SetPinValue(E_PIN, E_PORT, LOW);   
        _delay_ms(2); 

        error |= DIO_SetPinValue(E_PIN, E_PORT, HIGH); 
        error |= DIO_SetNibbleValue(START_DATA_PIN, DATA_PORT, cmd);
        
    #elif (MODE_4_BITS_USED) && (!DATA_PINS_ON_THE_SAME_PORT)
        error |= DIO_SetPinValue(D4_PIN, D4_PORT, BIT_READ(cmd, 4));
        error |= DIO_SetPinValue(D5_PIN, D5_PORT, BIT_READ(cmd, 5));
        error |= DIO_SetPinValue(D6_PIN, D6_PORT, BIT_READ(cmd, 6));
        error |= DIO_SetPinValue(D7_PIN, D7_PORT, BIT_READ(cmd, 7));

        /* Triggering the E pin */
        error |= DIO_SetPinValue(E_PIN, E_PORT, LOW);
        _delay_ms(2);

        error |= DIO_SetPinValue(E_PIN, E_PORT, HIGH);
        error |= DIO_SetPinValue(D4_PIN, D4_PORT, BIT_READ(cmd, 0));
        error |= DIO_SetPinValue(D5_PIN, D5_PORT, BIT_READ(cmd, 1));
        error |= DIO_SetPinValue(D6_PIN, D6_PORT, BIT_READ(cmd, 2));
        error |= DIO_SetPinValue(D7_PIN, D7_PORT, BIT_READ(cmd, 3));
    #elif (!MODE_4_BITS_USED) && (DATA_PINS_ON_THE_SAME_PORT)
        error |= DIO_SetPortValue(DATA_PORT, cmd);
    #elif (!MODE_4_BITS_USED) && (!DATA_PINS_ON_THE_SAME_PORT)
        error |= DIO_SetPinValue(D0_PIN, D0_PORT, BIT_READ(cmd, 0));
        error |= DIO_SetPinValue(D1_PIN, D1_PORT, BIT_READ(cmd, 1));
        error |= DIO_SetPinValue(D2_PIN, D2_PORT, BIT_READ(cmd, 2));
        error |= DIO_SetPinValue(D3_PIN, D3_PORT, BIT_READ(cmd, 3));
        error |= DIO_SetPinValue(D4_PIN, D4_PORT, BIT_READ(cmd, 4));
        error |= DIO_SetPinValue(D5_PIN, D5_PORT, BIT_READ(cmd, 5));
        error |= DIO_SetPinValue(D6_PIN, D6_PORT, BIT_READ(cmd, 6));
        error |= DIO_SetPinValue(D7_PIN, D7_PORT, BIT_READ(cmd, 7));
    #endif

    /* Triggering the E pin */
    error |= DIO_SetPinValue(E_PIN, E_PORT, LOW);   
    _delay_ms(2);   

    return error;
}

static ERROR_t CLCD_SendData(const char data) {
    ERROR_t error = ERROR_OK;

    /* Setting Control pins */
    error |= DIO_SetPinValue(RS_PIN, RS_PORT, HIGH);      
    error |= DIO_SetPinValue(E_PIN, E_PORT, HIGH);   
    #if (RW_PIN_USED)
        error |= DIO_SetPinValue(RW_PIN, RW_PORT, LOW);
    #endif

    /* Sending the command on the data pins */
    #if (MODE_4_BITS_USED) && (DATA_PINS_ON_THE_SAME_PORT)
        error |= DIO_SetNibbleValue(START_DATA_PIN, DATA_PORT, data >> 4);
        
        /* Triggering the E pin */
        error |= DIO_SetPinValue(E_PIN, E_PORT, LOW);   
        _delay_ms(2); 

        error |= DIO_SetPinValue(E_PIN, E_PORT, HIGH); 
        error |= DIO_SetNibbleValue(START_DATA_PIN, DATA_PORT, data);

    #elif (MODE_4_BITS_USED) && (!DATA_PINS_ON_THE_SAME_PORT)
        error |= DIO_SetPinValue(D4_PIN, D4_PORT, BIT_READ(data, 4));
        error |= DIO_SetPinValue(D5_PIN, D5_PORT, BIT_READ(data, 5));
        error |= DIO_SetPinValue(D6_PIN, D6_PORT, BIT_READ(data, 6));
        error |= DIO_SetPinValue(D7_PIN, D7_PORT, BIT_READ(data, 7));

        /* Triggering the E pin */
        error |= DIO_SetPinValue(E_PIN, E_PORT, LOW);
        _delay_ms(2);

        error |= DIO_SetPinValue(E_PIN, E_PORT, HIGH);
        error |= DIO_SetPinValue(D4_PIN, D4_PORT, BIT_READ(data, 0));
        error |= DIO_SetPinValue(D5_PIN, D5_PORT, BIT_READ(data, 1));
        error |= DIO_SetPinValue(D6_PIN, D6_PORT, BIT_READ(data, 2));
        error |= DIO_SetPinValue(D7_PIN, D7_PORT, BIT_READ(data, 3));
    #elif (!MODE_4_BITS_USED) && (DATA_PINS_ON_THE_SAME_PORT)
        error |= DIO_SetPortValue(DATA_PORT, data);
    #elif (!MODE_4_BITS_USED) && (!DATA_PINS_ON_THE_SAME_PORT)
        error |= DIO_SetPinValue(D0_PIN, D0_PORT, BIT_READ(data, 0));
        error |= DIO_SetPinValue(D1_PIN, D1_PORT, BIT_READ(data, 1));
        error |= DIO_SetPinValue(D2_PIN, D2_PORT, BIT_READ(data, 2));
        error |= DIO_SetPinValue(D3_PIN, D3_PORT, BIT_READ(data, 3));
        error |= DIO_SetPinValue(D4_PIN, D4_PORT, BIT_READ(data, 4));
        error |= DIO_SetPinValue(D5_PIN, D5_PORT, BIT_READ(data, 5));
        error |= DIO_SetPinValue(D6_PIN, D6_PORT, BIT_READ(data, 6));
        error |= DIO_SetPinValue(D7_PIN, D7_PORT, BIT_READ(data, 7));
    #endif

    /* Triggering the E pin */
    error |= DIO_SetPinValue(E_PIN, E_PORT, LOW);   
    _delay_ms(2);   

    return error;
}
