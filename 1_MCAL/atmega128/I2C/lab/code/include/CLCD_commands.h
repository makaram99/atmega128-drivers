#ifndef CLCD_COMMANDS_H   
#define CLCD_COMMANDS_H

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
#define CLCD_CMD_RETURN_HOME				        (0x02)

/* CLCD Display Mode     */
#define CLCD_CMD_DISPLAY_OFF_CURSOR_OFF_BLINK_OFF	(0x08)
#define CLCD_CMD_DISPLAY_ON_CURSOR_OFF_BLINK_OFF	(0x0C)
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
#define CLCD_CMD_SET_CURSOR_POSITION				(0x80)

/* Entry mode set options   */
#define CLCD_CMD_CURSOR_INCREMENT_NO_DISPLAY_SHIFT	(0x06)
#define CLCD_CMD_CURSOR_DECREMENT_NO_DISPLAY_SHIFT	(0x04)
#define CLCD_CMD_CURSOR_INCREMENT_DISPLAY_SHIFT	    (0x07)
#define CLCD_CMD_CURSOR_DECREMENT_DISPLAY_SHIFT	    (0x05)

#endif                  /* CLCD_COMMANDS_H */
