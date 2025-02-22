#ifndef KEYPAD_CFG_H   
#define KEYPAD_CFG_H

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                   CHANGE THIS PART TO YOUR NEEDS                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/******************************************************************************
 * @brief   Number of rows in the keypad.
 * OPTIONS: 3 OR 4
 ******************************************************************************/
#define NUM_OF_ROWS         (4U)

/******************************************************************************
 * @brief   Number of rocolumnsws in the keypad.
 * OPTIONS: 3 OR 4
 ******************************************************************************/
#define NUM_OF_COLS         (4U)

/******************************************************************************
 * @brief   Activation of keypad buttons: Active Low or Active High.
 * OPTIONS: LOW for active low, HIGH for active high.
 ******************************************************************************/
#define ACTIVE_STATE        (LOW)

/******************************************************************************
 * @brief   Enable or Disable the debouncing of the keypad.
 * OPTIONS: 1 to enable, 0 to disable
 ******************************************************************************/
#define DEBOUNCE_CTRL       (1U)

/******************************************************************************
 * @brief   If DEBOUNCE_CTRL is enabled, this is the time in ms that the keypad
 *          will wait before checking again if the keypad is still pressed.
 * OPTIONS: 20 to 150 ms
 * @par     Example:
 *          @code
 *          #define DEBOUNCE_CTRL       1       // Enable debouncing
 *          #define DEBOUNCE_TIME       10      // Debounce time is 10ms
 *          @endcode
 ******************************************************************************/
#define DEBOUNCE_TIME_MS    (30U)


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                    DO NOT CHANGE ANYTHING BELOW THIS COMMENT               */
/*                                                                            */
/*----------------------------------------------------------------------------*/

typedef struct {
    DIO_PINS_t pin;
} KEY_t;

typedef enum {
    KEYPAD_ACTIVE,
    KEYPAD_INACTIVE
} KEYPAD_STATE_t;

typedef struct {
    KEYPAD_t        keypad;
    KEYPAD_STATE_t  state;
    KEY_t           rows[NUM_OF_ROWS];
    KEY_t           cols[NUM_OF_COLS];
    u8_t            characters[NUM_OF_ROWS][NUM_OF_COLS];
} KEYPAD_CONFIGS_t;

extern KEYPAD_CONFIGS_t KEYPAD_Configs[];
extern u8_t countKeypadConfigs;

/******************************************************************************
 * @brief Asserting the debounce time.
 ******************************************************************************/
#if ( (DEBOUNCE_TIME_MS > 150U) || (DEBOUNCE_TIME_MS < 20U) )
#error "DEBOUNCE_TIME_MS must be between 20 and 150 ms"
#endif

/******************************************************************************
 * @brief Assert the keypad rows and columns numbers.
 ******************************************************************************/
#if ( (NUM_OF_ROWS != 3) && (NUM_OF_ROWS != 4) )
#error "NUM_OF_ROWS must be 3 or 4"
#elif ( (NUM_OF_COLS != 3) && (NUM_OF_COLS != 4) )
#error "NUM_OF_COLS must be 3 or 4"
#endif

#endif                  
