/******************************************************************************
 * @file        IR.h
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Interfaces header file for \ref IR.c
 * @version     1.0.0
 * @date        2022-03-20
 * @copyright   Copyright (c) 2022
 ******************************************************************************/
#ifndef IR_H
#define IR_H

/**************************************************************************************
 *                                  Typedefs
 *************************************************************************************/
typedef enum{
    IR_0,
    IR_1,
    IR_2,
    NUM_OF_IRS
}IR_SENSOR_t;

/**************************************************************************************
 **************************************************************************************
 *                                   API FUNCTIONS
 **************************************************************************************
 *************************************************************************************/

/**************************************************************************************
 * @brief Initialize IR Sensors Configurations
 *************************************************************************************/
ERROR_t IR_Init(void);

/**************************************************************************************
 * @brief       Get status of a specific IR Sensor, whether it is high or low
 * @param[in]   sensor: Number of the sensor to be read; Options in \ref IR_SENSOR_t
 * @param[out]  ptrToState: Pointer to a variable that will hold the status of the sensor
 *                  Options:
 *                      - HIGH if White
 *                      - LOW if black
 * @return      ERROR_t: error code; Options in \ref ERROR_t
 * @par Example:
 *  @code 
 *      // state is \ref HIGH if IR_0 is on white track and \ref LOW if black track, 
 *      IR_Read(IR_0, &state);      
 *  @endcode
 *************************************************************************************/
ERROR_t IR_Read(const IR_SENSOR_t sensor, STATE_t * const ptrToState);

/**************************************************************************************
 * @brief       Scan all IR Sensors and return the status of all of them
 * @return      State of all sensors; HIGH if White, LOW if black.
 * @par Example:
 *  @code 
 *      IR_ReadAll(&u32Value););     
 *      // when u32Value = 0x0F00FFF0(0B0000_1111_0000_0000_1111_1111_1111_0000):
 *      // This means:
 *      //    * (IR_0 --> IR_15) and (IR_24 --> IR_27) are on white track.
 *      //    * (IR_16 --> IR_23) and (IR_28 --> IR_31) are on black track.
 *  @endcode                 
 * @note    This function:
 *          * Only scans the configured sensors. So, if you have configured only IR_0 and IR_1, this function will only return a maximum of 0x00000003 (0B0000_0000_0000_0000_0000_0000_0000_0011)
 *          * Scans in the order of sensors' configurations. So, if you have configured IR_1 before IR_0 in the configuration, the status of IR_1 will be returned on bit 0 and the status of IR_0 will on bit 1.
 *************************************************************************************/
ERROR_t IR_ReadAll(u32_t * const ptr_u32Value);

/**************************************************************************
 * @brief   Get the number of configured IR sensors
 * @return  Number of configured IR sensors
 * @par For Example:
 *  @code 
 *      IR_ReadCount();  // returns 2 if only IR_0 and IR_1 are configured   
 * @endcode
 *************************************************************************/
ERROR_t IR_ReadCount(u8_t * const ptr_u8Count);

#endif  /* IR_H */