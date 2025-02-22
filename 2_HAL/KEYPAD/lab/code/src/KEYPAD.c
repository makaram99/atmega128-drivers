/******************************************************************************
 * @file        KEYPAD.c
 * @author      Mahmoud Karam Emara (ma.karam272@gmail.com)
 * @brief       Keypad module driver. It has the implementation file for 
 *              \ref KEYPAD.h.
 * @version     1.0.0
 * @date        2022-06-17
 * @copyright   Mahmoud Karam Emara 2022, MIT License
 ******************************************************************************/
#include "util/delay.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO.h"
#include "KEYPAD_cfg.h"
#include "KEYPAD.h"

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                          PRIVATE DATA                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
u8_t DEBOUNCE_DELAY_MS = DEBOUNCE_TIME_MS;

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                      PRIVATE FUNCTIONS PROTOTYPES                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/
static ERROR_t KEYPAD_Debounce(const DIO_PIN_t pin, const DIO_PORT_t port, STATE_t * const state);
static ERROR_t KEYPAD_GetPressedKeyPosition(s8_t * const row, s8_t * const col);


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                              PUBLIC FUNCTIONS                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

ERROR_t KEYPAD_Init(void) {
    ERROR_t error = ERROR_OK;
    u8_t i = 0;

    /*!< Rows must be initialized as outputs, and set to HIGH */
    for(i = 0; i < NUM_OF_ROWS; ++i) {
        error |= DIO_InitPin(KEYPAD_RowsPins[i].pin, KEYPAD_RowsPins[i].port, DIO_OUTPUT, DIO_PULLUP_OFF);
        error |= DIO_SetPinValue(KEYPAD_RowsPins[i].pin, KEYPAD_RowsPins[i].pin, HIGH);
    }

    /*!< Columns must be initialized as inputs with pull-up resistors */
    for(i = 0; i < NUM_OF_COLS; ++i) {
        error |= DIO_InitPin(KEYPAD_ColsPins[i].pin, KEYPAD_ColsPins[i].port, DIO_INPUT, DIO_PULLUP_ON);
    }
    
    return error;
}

ERROR_t KEYPAD_Read(u8_t * const data) {
    ERROR_t error = ERROR_OK;
    s8_t row = 0, col = 0;
    STATE_t state = LOW;

    *data = NULL_BYTE;

    KEYPAD_GetPressedKeyPosition(&row, &col);

    /*!< If a key is pressed, debounce */
    if((row != -1) && (col != -1)) {
        #if DEBOUNCE_CTRL
        /*!< Pull-down the row pin to get the state */
        error |= DIO_ClrPin(KEYPAD_RowsPins[row].pin, KEYPAD_RowsPins[row].port); 
        KEYPAD_Debounce(KEYPAD_ColsPins[col].pin, KEYPAD_ColsPins[col].port, &state);
        error |= DIO_SetPin(KEYPAD_RowsPins[row].pin, KEYPAD_RowsPins[row].port);

        if(ACTIVE_STATE == state) {
            *data = KEYPAD_Characters[row][col];
        }
        
        #else
        *data =  KEYPAD_Characters[row][col];
        #endif   
    }

	return error;
}

ERROR_t KEYPAD_WaitUntilPressed(u8_t * const data) {
    ERROR_t error = ERROR_OK;

    if(NULL == data) {
        return ERROR_NULL_POINTER;
    }

    do {
        error |= KEYPAD_Read(data);
    }while( (NULL_BYTE == *data) && (ERROR_OK == error) );

	return error;
}

ERROR_t KEYPAD_SetDebounceTime(const u8_t debounceTimeMs) {
    DEBOUNCE_DELAY_MS = debounceTimeMs;

    return ERROR_OK;
}


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                              PRIVATE FUNCTIONS                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*******************************************************************************
 * @brief       Get the pressed key position in the keypad in the form of row 
 *              and column. 
 * 
 * @param[out]  row: Pointer to the row number. 
 * @param[out]  col: Pointer to the column number.
 * @note        \ref row and \ref col are pointers to s8_t variables.
 *              \ref row and \ref col are set to -1 if no key is pressed.
 *              \ref row and \ref col are set to -1 if an error occurred.
 *              \ref row and \ref col are positive numbers if a key is pressed.
 * @return      ERROR_t: Error status. See \ref ERROR_t.
 ******************************************************************************/
static ERROR_t KEYPAD_GetPressedKeyPosition(s8_t * const row, s8_t * const col) {
    ERROR_t error = ERROR_OK;
    STATE_t state = LOW;
    u8_t i = 0, j = 0;
    
    for (i = 0; i < NUM_OF_ROWS; ++i) {
		error |= DIO_ClrPin(KEYPAD_RowsPins[i].pin, KEYPAD_RowsPins[i].port);

		for (j = 0; j < NUM_OF_COLS; ++j) {
			error |= DIO_ReadPin(KEYPAD_ColsPins[j].pin, KEYPAD_ColsPins[j].port, &state);  
			
            if( (ACTIVE_STATE == state) || (error != ERROR_OK) ) {    /* If the key is pressed */
                break;
            }
		}

        if(j < NUM_OF_COLS) {
            break;
        }

        error |= DIO_SetPin(KEYPAD_RowsPins[i].pin, KEYPAD_RowsPins[i].port);
	}

    error |= DIO_SetPin(KEYPAD_RowsPins[i].pin, KEYPAD_RowsPins[i].port);

    if( (i >= NUM_OF_ROWS) || (error != ERROR_OK) ) {
        *row = *col = -1;
    } else {
        *row = i;
        *col = j;
    }
    
    return error;
}

/*******************************************************************************
 * @brief       Debounce the keypad column pin.
 * 
 * @param[in]   pin:    The pin number.
 * @param[in]   port:   The port number.
 * @param[out]  state:  The state of the pin.
 * @note        \ref state is set the state of the pin after the debounce.
 * @return      ERROR_t: Error status. See \ref ERROR_t.
 ******************************************************************************/
static ERROR_t KEYPAD_Debounce(const DIO_PIN_t pin, const DIO_PORT_t port, STATE_t * const state) {
    ERROR_t error = ERROR_OK;

	error |= DIO_ReadPin(pin, port, state);  

	if(ACTIVE_STATE == *state) {
        _delay_ms(DEBOUNCE_DELAY_MS);     /* debounce */

        error |= DIO_ReadPin(pin, port, state);
        if(ACTIVE_STATE == *state) {
            do {
                error |= DIO_ReadPin(pin, port, state);
            } while( (ACTIVE_STATE == *state) && (error == ERROR_OK) );
            
            *state = ACTIVE_STATE;
        }
    }

    return error;
}
