#ifndef CLCD_CFG_H   
#define CLCD_CFG_H

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                   CHANGE THIS PART TO YOUR NEEDS                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/******************************************************************************
 *                              CLCD configuration                              
 *****************************************************************************/
    #define CLCD_DOTS_HEIGHT             (8)
    /**************************************************************************
     * @brief   Number of rows in the lcd.
     * OPTIONS: 1 OR 2
     *************************************************************************/
    #define CLCD_NUMBER_OF_LINES         (2U)

    /**************************************************************************
     * @brief   Number of rocolumnsws in the lcd.
     * OPTIONS: 8, 16, OR 20
     *************************************************************************/
    #define CLCD_NUMBER_OF_COLS         (16U)

/******************************************************************************
 *                              CONTROL PINS CONNECTIONS
 *****************************************************************************/

    /**************************************************************************
     * @brief   Mode of the lcd: 4-bit or 8-bit.
     * OPTIONS: 1 if 4-bit, 0 if 8-bit.
     *************************************************************************/
    #define MODE_4_BITS_USED            (0U)

    /**************************************************************************
     * @brief   If all data pins are on the same port.
     * OPTIONS: 1 if all data pins are on the same port, 0 if not.
     *************************************************************************/
    #define DATA_PINS_ON_THE_SAME_PORT  (1U)

    #if (DATA_PINS_ON_THE_SAME_PORT)
        /**********************************************************************
         * @brief   The port number of the data pins.
         * OPTIONS: See \ref DIO_PORT_t for the available ports.
         *********************************************************************/
        #define DATA_PORT               (DIO_PORT_A)

        #if (MODE_4_BITS_USED)
            /************************************************************************
             * @brief   The first data pin number connected to which pin on the port
             * OPTIONS: DIO_PIN_0, DIO_PIN_1, DIO_PIN_2, DIO_PIN_3, DIO_PIN_4, DIO_PIN_5, DIO_PIN_6, DIO_PIN_7
             ***********************************************************************/
            #define START_DATA_PIN      (DIO_PIN_4)
        #endif  /* (MODE_4_BITS_USED) */
    #else   /* DATA_PINS_ON_THE_SAME_PORT */
        #if(!MODE_4_BITS_USED)
            #define D0_PIN              (DIO_PIN_0)
            #define D0_PORT             (DIO_PORT_A)
            #define D1_PIN              (DIO_PIN_1)
            #define D1_PORT             (DIO_PORT_A)
            #define D2_PIN              (DIO_PIN_2)
            #define D2_PORT             (DIO_PORT_A)
            #define D3_PIN              (DIO_PIN_3)
            #define D3_PORT             (DIO_PORT_A)
        #endif      
            #define D4_PIN              (DIO_PIN_4)
            #define D4_PORT             (DIO_PORT_A)
            #define D5_PIN              (DIO_PIN_5)
            #define D5_PORT             (DIO_PORT_A)
            #define D6_PIN              (DIO_PIN_6)
            #define D6_PORT             (DIO_PORT_A)
            #define D7_PIN              (DIO_PIN_7)
            #define D7_PORT             (DIO_PORT_A)
    #endif

/******************************************************************************
 *                              CONTROL PINS CONNECTIONS
 ******************************************************************************/
    #define RS_PIN                      (DIO_PIN_1)
    #define RS_PORT                     (DIO_PORT_B)

    #define E_PIN                       (DIO_PIN_2)
    #define E_PORT                      (DIO_PORT_B)

    /******************************************************************************
     * @brief   If the RW pin is used.
     * OPTIONS: 1 if used, 0 if not used (connected exernally).
     * @note    If used, the pin must be connected to the port. If not used, the pin
     *          must be connected to the ground externally.
     ******************************************************************************/
    #define RW_PIN_USED                 (1U)

    #if (RW_PIN_USED)       
        #define RW_PIN                  (DIO_PIN_3)
        #define RW_PORT                 (DIO_PORT_B)
    #endif

    /******************************************************************************
     *                              Commands                           
     *****************************************************************************/
    /* CLCD Operating mode options   */
    #define CLCD_CMD_4_BIT_2_LINES_8_DOTS	            (0x28)
    #define CLCD_CMD_4_BIT_2_LINES_11_DOTS	            (0x2C)
    #define CLCD_CMD_4_BIT_1_LINES_8_DOTS	            (0x20)
    #define CLCD_CMD_4_BIT_1_LINES_11_DOTS	            (0x24)
    #define CLCD_CMD_8_BIT_2_LINES_8_DOTS	            (0x38)
    #define CLCD_CMD_8_BIT_2_LINES_11_DOTS	            (0x3C)
    #define CLCD_CMD_8_BIT_1_LINES_8_DOTS	            (0x30)
    #define CLCD_CMD_8_BIT_1_LINES_11_DOTS	            (0x34)

    #define CLCD_CMD_CLEAR_DISPLAY			            (0x01)
    #define CLCD_CMD_RETURN_HOME				            (0x02)

    /* CLCD Display Mode     */
    #define CLCD_CMD_DISPLAY_OFF_CURSOR_OFF_BLINK_OFF	(0x08)
    #define CLCD_CMD_DISPLAY_ON_CURSOR_OFF_BLINK_OFF	    (0x0C)
    #define CLCD_CMD_DISPLAY_ON_CURSOR_ON_BLINK_OFF	    (0x0E)
    #define CLCD_CMD_DISPLAY_ON_CURSOR_ON_BLINK_ON	    (0x0F)

    /* CLCD Cursor Control   */
    #define CLCD_CMD_CURSOR_SHIFT_RIGHT				    (0x14)
    #define CLCD_CMD_CURSOR_SHIFT_LEFT				    (0x10)
    #define CLCD_CMD_DISPLAY_MOVE_RIGHT				    (0x1C)
    #define CLCD_CMD_DISPLAY_MOVE_LEFT				    (0x18)

    /* Writing to RAM   */
    #define CLCD_CMD_SET_DDRAM_ADDRESS				    (0x80)
    #define CLCD_CMD_SET_CGRAM_ADDRESS				    (0x40)
    #define CLCD_CMD_WRITE_DATA						    (0x40)
    #define CLCD_CMD_SET_CURSOR_POSITION				    (0x80)

    /* Entry mode set options   */
    #define CLCD_CMD_CURSOR_INCREMENT_NO_DISPLAY_SHIFT	(0x06)
    #define CLCD_CMD_CURSOR_DECREMENT_NO_DISPLAY_SHIFT	(0x04)
    #define CLCD_CMD_CURSOR_INCREMENT_DISPLAY_SHIFT	    (0x07)
    #define CLCD_CMD_CURSOR_DECREMENT_DISPLAY_SHIFT	    (0x05)

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
    #define CLCD_OPERATING_MODE          CLCD_CMD_8_BIT_2_LINES_8_DOTS

    /******************************************************************************
     * @brief   CLCD Entry Mode Set.
     * OPTIONS: The available options:
     *          - CLCD_CMD_CURSOR_INCREMENT_NO_DISPLAY_SHIFT
     *          - CLCD_CMD_CURSOR_INCREMENT_DISPLAY_SHIFT
     *          - CLCD_CMD_CURSOR_DECREMENT_NO_DISPLAY_SHIFT
     *          - CLCD_CMD_CURSOR_DECREMENT_DISPLAY_SHIFT
     ******************************************************************************/
    #define CLCD_ENTRY_MODE_SET          CLCD_CMD_CURSOR_INCREMENT_NO_DISPLAY_SHIFT

    /******************************************************************************
     * @brief   CLCD Display On/Off Control.
     * OPTIONS: The available options:
     *          - CLCD_CMD_DISPLAY_OFF_CURSOR_OFF_BLINK_OFF
     *          - CLCD_CMD_DISPLAY_ON_CURSOR_OFF_BLINK_OFF
     *          - CLCD_CMD_DISPLAY_OFF_CURSOR_ON_BLINK_OFF
     *          - CLCD_CMD_DISPLAY_ON_CURSOR_ON_BLINK_OFF
     ******************************************************************************/
    #define CLCD_DISPLAY_MODE            CLCD_CMD_DISPLAY_ON_CURSOR_OFF_BLINK_OFF

    /******************************************************************************
     *                              CLCD Lines offset
     *****************************************************************************/
    #define CLCD_LINE_2_OFFSET                           (0x40)

    /******************************************************************************
     *                          ASSERTIONS                                      
     *****************************************************************************/

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                CHANGE THE FOLLOWING ONLY WITH DIFFERENT CLCD                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
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
