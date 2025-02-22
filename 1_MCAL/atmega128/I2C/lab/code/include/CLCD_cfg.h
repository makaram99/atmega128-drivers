#ifndef CLCD_CFG_H   
#define CLCD_CFG_H

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                   CHANGE THIS PART TO YOUR NEEDS                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/**************************************************************************
 * @brief   Flag indicates whether data pins are on the same port or not.
 * OPTIONS: 1 for yes, OR 2 for no.
 *************************************************************************/
#define DATA_ON_THE_SAME_PORT           (1U)

/**************************************************************************
 * @brief   Number of rows in the lcd.
 * OPTIONS: 1 OR 2
 *************************************************************************/
#define CLCD_NUMBER_OF_LINES            (2U)

/**************************************************************************
 * @brief   Mode of the lcd: 4-bit or 8-bit.
 * OPTIONS: 1 if 4-bit, 0 if 8-bit.
 *************************************************************************/
#define MODE_4_BITS_USED                (0U)

/******************************************************************************
 * @brief   If the RW pin is used.
 * OPTIONS: 1 if used, 0 if not used (connected exernally).
 * @note    If used, the pin must be connected to the port. If not used, the pin
 *          must be connected to the ground externally.
 ******************************************************************************/
#define CLCD_RW_PIN_USED                (1U)

/******************************************************************************
 * @brief   CLCD Operating mode.
 * OPTIONS: The available options.
 *          - CLCD_CMD_4_BIT_2_LINES_8_DOTS for 4-bit 2-lines 8-dots,
 *          - CLCD_CMD_4_BIT_2_LINES_11_DOTS for 4-bit 2-lines 11-dots,
 *          - CLCD_CMD_4_BIT_1_LINES_8_DOTS for 4-bit 1-lines 8-dots,
 *          - CLCD_CMD_4_BIT_1_LINES_11_DOTS for 4-bit 1-lines 11-dots,
 *          - CLCD_CMD_8_BIT_2_LINES_8_DOTS for 8-bit 2-lines 8-dots,
 *          - CLCD_CMD_8_BIT_2_LINES_11_DOTS for 8-bit 2-lines 11-dots,
 *          - CLCD_CMD_8_BIT_1_LINES_8_DOTS for 8-bit 1-lines 8-dots,
 *          - CLCD_CMD_8_BIT_1_LINES_11_DOTS for 8-bit 1-lines 11-dots.
 * @note    The CLCD_CMD_4_BIT_2_LINES_8_DOTS is the default mode.
 ******************************************************************************/
#define CLCD_OPERATING_MODE             CLCD_CMD_8_BIT_2_LINES_8_DOTS

/******************************************************************************
 * @brief   CLCD Entry Mode Set.
 * OPTIONS: The available options:
 *          - CLCD_CMD_CURSOR_INCREMENT_NO_DISPLAY_SHIFT
 *          - CLCD_CMD_CURSOR_INCREMENT_DISPLAY_SHIFT
 *          - CLCD_CMD_CURSOR_DECREMENT_NO_DISPLAY_SHIFT
 *          - CLCD_CMD_CURSOR_DECREMENT_DISPLAY_SHIFT
 ******************************************************************************/
#define CLCD_ENTRY_MODE_SET             CLCD_CMD_CURSOR_INCREMENT_NO_DISPLAY_SHIFT

/******************************************************************************
 * @brief   CLCD Display On/Off Control.
 * OPTIONS: The available options:
 *          - CLCD_CMD_DISPLAY_OFF_CURSOR_OFF_BLINK_OFF
 *          - CLCD_CMD_DISPLAY_ON_CURSOR_OFF_BLINK_OFF
 *          - CLCD_CMD_DISPLAY_OFF_CURSOR_ON_BLINK_OFF
 *          - CLCD_CMD_DISPLAY_ON_CURSOR_ON_BLINK_OFF
 ******************************************************************************/
#define CLCD_DISPLAY_MODE               CLCD_CMD_DISPLAY_ON_CURSOR_OFF_BLINK_OFF

/******************************************************************************
 *                              CLCD Lines offset
 *****************************************************************************/
#define CLCD_LINE_2_OFFSET              (0x40)





/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                CHANGE THE FOLLOWING ONLY WITH DIFFERENT CLCD                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

typedef struct {
    DIO_PINS_t  RS;
    #if CLCD_RW_PIN_USED
    DIO_PINS_t  RW;
    #endif
    DIO_PINS_t  E;

    #if (!MODE_4_BITS_USED)
    DIO_PINS_t  D0;
    DIO_PINS_t  D1;
    DIO_PINS_t  D2;
    DIO_PINS_t  D3;
    #endif
    DIO_PINS_t  D4;
    DIO_PINS_t  D5;
    DIO_PINS_t  D6;
    DIO_PINS_t  D7;
} CLCD_PINS_t;

extern CLCD_PINS_t CLCD_Pins;

/******************************************************************************
 *                          ASSERTIONS                                      
 *****************************************************************************/
/* Assertion of CLCD operating mode   */
#if (CLCD_OPERATING_MODE != CLCD_CMD_4_BIT_2_LINES_8_DOTS)  && \
    (CLCD_OPERATING_MODE != CLCD_CMD_4_BIT_2_LINES_11_DOTS) && \
    (CLCD_OPERATING_MODE != CLCD_CMD_4_BIT_1_LINES_8_DOTS)  && \
    (CLCD_OPERATING_MODE != CLCD_CMD_4_BIT_1_LINES_11_DOTS) && \
    (CLCD_OPERATING_MODE != CLCD_CMD_8_BIT_2_LINES_8_DOTS)  && \
    (CLCD_OPERATING_MODE != CLCD_CMD_8_BIT_2_LINES_11_DOTS) && \
    (CLCD_OPERATING_MODE != CLCD_CMD_8_BIT_1_LINES_8_DOTS)  && \
    (CLCD_OPERATING_MODE != CLCD_CMD_8_BIT_1_LINES_11_DOTS)
    
    #error "Invalid CLCD operating mode"
#endif

/* Assertion of CLCD entry mode set   */
#if (CLCD_ENTRY_MODE_SET != CLCD_CMD_CURSOR_INCREMENT_NO_DISPLAY_SHIFT)   && \
    (CLCD_ENTRY_MODE_SET != CLCD_CMD_CURSOR_INCREMENT_DISPLAY_SHIFT)      && \
    (CLCD_ENTRY_MODE_SET != CLCD_CMD_CURSOR_DECREMENT_NO_DISPLAY_SHIFT)   && \
    (CLCD_ENTRY_MODE_SET != CLCD_CMD_CURSOR_DECREMENT_DISPLAY_SHIFT)
    
    #error "Invalid CLCD entry mode set"
#endif

/* Assertion of CLCD display mode    */
#if (CLCD_DISPLAY_MODE != CLCD_CMD_DISPLAY_OFF_CURSOR_OFF_BLINK_OFF)  && \
    (CLCD_DISPLAY_MODE != CLCD_CMD_DISPLAY_ON_CURSOR_OFF_BLINK_OFF)   && \
    (CLCD_DISPLAY_MODE != CLCD_CMD_DISPLAY_ON_CURSOR_ON_BLINK_OFF)    && \
    (CLCD_DISPLAY_MODE != CLCD_CMD_DISPLAY_ON_CURSOR_ON_BLINK_ON)
    #error "Invalid CLCD display mode"
#endif

/* Asserting Number of lines configuration with CLCD operating mode   */
#if (CLCD_OPERATING_MODE == CLCD_CMD_4_BIT_2_LINES_8_DOTS)    || \
    (CLCD_OPERATING_MODE == CLCD_CMD_4_BIT_2_LINES_11_DOTS)   || \
    (CLCD_OPERATING_MODE == CLCD_CMD_8_BIT_2_LINES_8_DOTS)    || \
    (CLCD_OPERATING_MODE == CLCD_CMD_8_BIT_2_LINES_11_DOTS)
    #if (CLCD_NUMBER_OF_LINES != 2)
        #error "CLCD number of lines configuration conflict with CLCD operating mode"
    #endif
#elif   (CLCD_OPERATING_MODE == CLCD_CMD_4_BIT_1_LINES_8_DOTS)  || \
        (CLCD_OPERATING_MODE == CLCD_CMD_4_BIT_1_LINES_11_DOTS) || \
        (CLCD_OPERATING_MODE == CLCD_CMD_8_BIT_1_LINES_8_DOTS)  || \
        (CLCD_OPERATING_MODE == CLCD_CMD_8_BIT_1_LINES_11_DOTS)
    #if (CLCD_NUMBER_OF_LINES != 1)
        #error "CLCD number of lines configuration conflict with CLCD operating mode"
    #endif
#endif

/* Assertion of Operating mode configuration with CLCD operating mode   */
#if (CLCD_OPERATING_MODE == CLCD_CMD_4_BIT_2_LINES_8_DOTS)   || \
    (CLCD_OPERATING_MODE == CLCD_CMD_4_BIT_2_LINES_11_DOTS)  || \
    (CLCD_OPERATING_MODE == CLCD_CMD_4_BIT_1_LINES_8_DOTS)   || \
    (CLCD_OPERATING_MODE == CLCD_CMD_4_BIT_1_LINES_11_DOTS)
    #if (!MODE_4_BITS_USED)
        #error "MODE_4_BITS_USED conflicts with CLCD_OPERATING_MODE"
    #endif
#elif   (CLCD_OPERATING_MODE == CLCD_CMD_8_BIT_2_LINES_8_DOTS)  || \
        (CLCD_OPERATING_MODE == CLCD_CMD_8_BIT_2_LINES_11_DOTS) || \
        (CLCD_OPERATING_MODE == CLCD_CMD_8_BIT_1_LINES_8_DOTS)  || \
        (CLCD_OPERATING_MODE == CLCD_CMD_8_BIT_1_LINES_11_DOTS)
    #if (MODE_4_BITS_USED)
        #error "MODE_4_BITS_USED conflicts with CLCD_OPERATING_MODE"
    #endif
#endif


#endif                  
