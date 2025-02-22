/******************************************************************************
 * @file        BUTTON_cfg.h
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Configuration header file for \ref BUTTON.c
 * @version     1.0.0
 * @date        2022-03-20
 * @copyright   Copyright (c) 2022
 ******************************************************************************/
#ifndef BUTTON_CFG_H   
#define BUTTON_CFG_H

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                    CHANGE THE FOLLOWING TO YOUR NEEDS                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/******************************************************************************
 * @brief   This is the time in ms that the button must be pressed to be
 *          considered pressed.
 * @note    This time is used only when the debounce is enabled for the button
 *          in the configuration file BUTTON_cfg.c, and the button is pressed.
 * OPTIONS: 20 to 150 ms
 ******************************************************************************/
#define DEBOUNCE_TIME_MS   (30U)



/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                    DO NOT CHANGE ANYTHING BELOW THIS LINE                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

typedef struct{
    BUTTON_t                button;
    DIO_PIN_t                   pin;
    DIO_PORT_t                  port;
    ACTIVATION_STATUS_t     ActiveHighOrLow;
    DEBOUNCE_t              debounce;
}BUTTON_CONFIGS_t;

extern BUTTON_CONFIGS_t buttonsConfigs[];
extern const u8_t countButtonsConfigured;

#endif      /* BUTTON_CFG_H */              
