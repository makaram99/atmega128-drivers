/******************************************************************************
 * @file        KEYPAD_cfg.c
 * @author      Mahmoud Karam Emara (ma.karam272@gmail.com)
 * @brief       Configuration file for the KEYPAD module.
 * @version     1.0.0
 * @date        2022-06-17
 * @copyright   Mahmoud Karam Emara 2022, MIT License
 ******************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO.h"
#include "KEYPAD_cfg.h"
#include "KEYPAD.h"

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                   CHANGE THIS PART TO YOUR NEEDS                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*******************************************************************************
 * @brief Configuration of the DIO pins used by the KEYPAD.
 *******************************************************************************/

#if ( (NUM_OF_ROWS == 4) && (NUM_OF_COLS == 4) )
/*******************************************************************************
 *                                  4 x 4 Keypad                               *
 *******************************************************************************         
 *           ___________________                                               
 *          |    |    |    |    |                                              
 *          | A  | B  | C  | D  |--------- R0                                  
 *          |____|____|____|____|
 *          |    |    |    |    |
 *		    | E  | F  | G  | H  |--------- R1
 *          |____|____|____|____|
 *          |    |    |    |    |
 *		    | I  | J  | K  | L  |--------- R2
 *		    |____|____|____|____|
 *		    |    |    |    |    |
 *		    | M  | N  | O  | P  |--------- R3
 *          |____|____|____|____|
 *            |    |    |    |
 *            |    |    |    |____________ C3
 *            |    |    |
 *            |    |    |_________________ C2
 *            |    |
 *            |    |______________________ C1
 *            |
 *            |___________________________ C0
 * 
 * These digits are configurable inside the \ref KEYPAD_Characters array.
*******************************************************************************/
u8_t KEYPAD_Characters[NUM_OF_ROWS][NUM_OF_COLS] = {
    {'7' , '8' , '9', '/'},
	{'4' , '5' , '6', '*'},
	{'1' , '2' , '3', '-'},
	{'C' , '0' , '=', '+'},
};

KEYPAD_t KEYPAD_RowsPins[NUM_OF_ROWS] = {
    {DIO_PIN_4, DIO_PORT_B},    /* Row 0 */
    {DIO_PIN_5, DIO_PORT_B},    /* Row 1 */
    {DIO_PIN_6, DIO_PORT_B},    /* Row 2 */
    {DIO_PIN_7, DIO_PORT_B},    /* Row 3 */
};

KEYPAD_t KEYPAD_ColsPins[NUM_OF_COLS] = {
    {DIO_PIN_2, DIO_PORT_D},    /* Col 0 */
    {DIO_PIN_3, DIO_PORT_D},    /* Col 1 */
    {DIO_PIN_4, DIO_PORT_D},    /* Col 2 */
    {DIO_PIN_5, DIO_PORT_D},    /* Col 3 */
};

#elif ( (NUM_OF_ROWS == 4) && (NUM_OF_COLS == 3) )
/*******************************************************************************
 *                                  4 x 3 Keypad                               *
 *******************************************************************************         
 *           _______________                                              
 *          |    |    |    |                                              
 *          | A  | B  | C  |--------- R0                                  
 *          |____|____|____|
 *          |    |    |    |
 *		    | E  | F  | G  |--------- R1
 *          |____|____|____|
 *          |    |    |    |
 *		    | I  | J  | K  |--------- R2
 *		    |____|____|____|
 *		    |    |    |    |
 *		    | M  | N  | O  |--------- R3
 *          |____|____|____|
 *            |    |    |
 *            |    |    |____________ C2
 *            |    |
 *            |    |_________________ C1
 *            |
 *            |______________________ C0
 * 
 * These digits are configurable inside the \ref KEYPAD_Characters array.
*******************************************************************************/
u8_t KEYPAD_Characters[NUM_OF_ROWS][NUM_OF_COLS] = {
    {'7' , '8' , '9'},
	{'4' , '5' , '6'},
	{'1' , '2' , '3'},
	{'*' , '0' , '#'},
};

KEYPAD_t KEYPAD_RowsPins[NUM_OF_ROWS] = {
    {DIO_PIN_4, DIO_PORT_B},    /* Row 0 */
    {DIO_PIN_5, DIO_PORT_B},    /* Row 1 */
    {DIO_PIN_6, DIO_PORT_B},    /* Row 2 */
    {DIO_PIN_7, DIO_PORT_B},    /* Row 3 */
};

KEYPAD_t KEYPAD_ColsPins[NUM_OF_COLS] = {
    {DIO_PIN_2, DIO_PORT_D},    /* Col 0 */
    {DIO_PIN_3, DIO_PORT_D},    /* Col 1 */
    {DIO_PIN_4, DIO_PORT_D},    /* Col 2 */
}; 

#elif ( (NUM_OF_ROWS == 3) && (NUM_OF_COLS == 4) )

u8_t KEYPAD_Characters[NUM_OF_ROWS][NUM_OF_COLS] = {
    /*******************************************************************************
 *                                  3 x 4 Keypad                               *
 *******************************************************************************         
 *           ___________________                                               
 *          |    |    |    |    |                                              
 *          | A  | B  | C  | D  |--------- R0                                  
 *          |____|____|____|____|
 *          |    |    |    |    |
 *		    | E  | F  | G  | H  |--------- R1
 *          |____|____|____|____|
 *          |    |    |    |    |
 *		    | I  | J  | K  | L  |--------- R2
 *		    |____|____|____|____|
 *            |    |    |    |
 *            |    |    |    |____________ C3
 *            |    |    |
 *            |    |    |_________________ C2
 *            |    |
 *            |    |______________________ C1
 *            |
 *            |___________________________ C0
 * 
 * These digits are configurable inside the \ref KEYPAD_Characters array.
*******************************************************************************/
    {'7' , '8' , '9', '*'},
	{'4' , '5' , '6', '0'},
	{'1' , '2' , '3', '#'},
};

KEYPAD_t KEYPAD_RowsPins[NUM_OF_ROWS] = {
    {DIO_PIN_4, DIO_PORT_B},    /* Row 0 */
    {DIO_PIN_5, DIO_PORT_B},    /* Row 1 */
    {DIO_PIN_6, DIO_PORT_B},    /* Row 2 */
};

KEYPAD_t KEYPAD_ColsPins[NUM_OF_COLS] = {
    {DIO_PIN_2, DIO_PORT_D},    /* Col 0 */
    {DIO_PIN_3, DIO_PORT_D},    /* Col 1 */
    {DIO_PIN_4, DIO_PORT_D},    /* Col 2 */
    {DIO_PIN_5, DIO_PORT_D},    /* Col 3 */
};

#elif ( (NUM_OF_ROWS == 3) && (NUM_OF_COLS == 3) )
/*******************************************************************************
 *                                  3 x 3 Keypad                               *
 *******************************************************************************         
 *           _______________                                              
 *          |    |    |    |                                              
 *          | A  | B  | C  |--------- R0                                  
 *          |____|____|____|
 *          |    |    |    |
 *		    | E  | F  | G  |--------- R1
 *          |____|____|____|
 *          |    |    |    |
 *		    | I  | J  | K  |--------- R2
 *		    |____|____|____|
 *            |    |    |
 *            |    |    |____________ C2
 *            |    |
 *            |    |_________________ C1
 *            |
 *            |______________________ C0
 * 
 * These digits are configurable inside the \ref KEYPAD_Characters array.
*******************************************************************************/
u8_t KEYPAD_Characters[NUM_OF_ROWS][NUM_OF_COLS] = {
    {'7' , '8' , '9'},
	{'4' , '5' , '6'},
	{'1' , '2' , '3'},
};

KEYPAD_t KEYPAD_RowsPins[NUM_OF_ROWS] = {
    {DIO_PIN_4, DIO_PORT_B},    /* Row 0 */
    {DIO_PIN_5, DIO_PORT_B},    /* Row 1 */
    {DIO_PIN_6, DIO_PORT_B},    /* Row 2 */
};

KEYPAD_t KEYPAD_ColsPins[NUM_OF_COLS] = {
    {DIO_PIN_2, DIO_PORT_D},    /* Col 0 */
    {DIO_PIN_3, DIO_PORT_D},    /* Col 1 */
    {DIO_PIN_4, DIO_PORT_D},    /* Col 2 */
};

#endif

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                    DO NOT CHANGE ANYTHING BELOW THIS COMMENT               */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/******************************************************************************
 * @brief Assert the keypad rows and columns numbers.
 ******************************************************************************/
#if ( (NUM_OF_ROWS != 3) && (NUM_OF_ROWS != 4) )
#error "NUM_OF_ROWS must be 3 or 4"
#elif ( (NUM_OF_COLS != 3) && (NUM_OF_COLS != 4) )
#error "NUM_OF_COLS must be 3 or 4"
#endif
