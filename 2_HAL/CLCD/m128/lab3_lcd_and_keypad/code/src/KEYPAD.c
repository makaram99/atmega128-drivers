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
#include "KEYPAD.h"
#include "KEYPAD_cfg.h"


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
static ERROR_t KEYPAD_Debounce(const DIO_PINS_t pin, STATE_t * const state);
static ERROR_t KEYPAD_GetPressedKeyPosition(const u8_t index, s8_t * const row, s8_t * const col);

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                              PUBLIC FUNCTIONS                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

ERROR_t KEYPAD_Init(void) {   
    return ERROR_OK;
}

ERROR_t KEYPAD_Read(const KEYPAD_t keypad, u8_t * const data) {
    ERROR_t error = ERROR_OK;
    STATE_t state = LOW;
    s8_t row = 0, col = 0;
    u8_t k = 0;

    if(data == NULL) {
       return ERROR_NULL_POINTER;
    }

    *data = NULL_BYTE;

    /* Check if the keypad is active */
    for(k = 0; k < countKeypadConfigs; ++k) {
        if(keypad == KEYPAD_Configs[k].keypad) {
            if(KEYPAD_INACTIVE == KEYPAD_Configs[k].state) {
                return ERROR_INVALID_PARAMETER;
            }
            break;
        }
    }
    if(k == countKeypadConfigs) {
        return ERROR_INVALID_PARAMETER;
    }

    /* Get the pressed key position */
    KEYPAD_GetPressedKeyPosition(k, &row, &col);

    /*!< If a key is pressed, debounce if needed, and get the key value */
    if( (row != -1) && (col != -1) ) {
        #if DEBOUNCE_CTRL
        /*!< Pull-down the row pin to get the state */
        error |= DIO_ClrPin(KEYPAD_Configs[k].rows[row].pin);
        KEYPAD_Debounce(KEYPAD_Configs[k].cols[col].pin, &state);
        error |= DIO_SetPin(KEYPAD_Configs[k].rows[row].pin);

        if(ACTIVE_STATE == state) {
            *data = KEYPAD_Configs[k].characters[row][col];
        }
        
        #else
        *data =  KEYPAD_Configs[k].characters[row][col];
        #endif   
    }

	return error;
}

ERROR_t KEYPAD_WaitUntilPressed(const KEYPAD_t keypad, u8_t * const data) {
    ERROR_t error = ERROR_OK;

    if(NULL == data) {
        return ERROR_NULL_POINTER;
    }

    do {
        error |= KEYPAD_Read(keypad, data);
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
static ERROR_t KEYPAD_GetPressedKeyPosition(const u8_t index, s8_t * const row, s8_t * const col) {
    ERROR_t error = ERROR_OK;
    STATE_t state = LOW;
    u8_t i = 0, j = 0;

    for (i = 0; i < NUM_OF_ROWS; ++i) {
		error |= DIO_ClrPin(KEYPAD_Configs[index].rows[i].pin);
        
		for (j = 0; j < NUM_OF_COLS; ++j) {
			error |= DIO_ReadPin(KEYPAD_Configs[index].cols[j].pin, &state);  
			
            if( (ACTIVE_STATE == state) || (error != ERROR_OK) ) {    /* If the key is pressed */
                break;
            }
		}

        if(j < NUM_OF_COLS) {
            break;
        }

        error |= DIO_SetPin(KEYPAD_Configs[index].rows[i].pin);
	}

    error |= DIO_SetPin(KEYPAD_Configs[index].rows[i].pin);

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
static ERROR_t KEYPAD_Debounce(const DIO_PINS_t pin, STATE_t * const state) {
    ERROR_t error = ERROR_OK;

	error |= DIO_ReadPin(pin, state);  

	if(ACTIVE_STATE == *state) {
        _delay_ms(DEBOUNCE_DELAY_MS);     /* debounce */

        error |= DIO_ReadPin(pin, state);
        if(ACTIVE_STATE == *state) {
            do {
                error |= DIO_ReadPin(pin, state);
            } while( (ACTIVE_STATE == *state) && (error == ERROR_OK) );
            
            *state = ACTIVE_STATE;
        }
    }

    return error;
}
