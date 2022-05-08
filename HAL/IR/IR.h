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
}IR_SENSOR_t;

/**************************************************************************************
 **************************************************************************************
 *                                   API FUNCTIONS
 **************************************************************************************
 *************************************************************************************/

/**************************************************************************************
 * @brief Initialize IR Sensors Configurations
 *************************************************************************************/
void IR_Init(void);

/**************************************************************************************
 * @brief       Get status of a specific IR Sensor, whether it is high or low
 * @param[in]   sensor: Number of the sensor to be read; IR_0, IR_1, ..., IR_7
 * @return      State of the sensor; HIGH if White, LOW if black.
 * @par Example:
 *      @code 
 *      IR_Read(IR_0);     // \ref HIGH if IR_0 is on white track and \ref LOW if black track, member of \ref STATE_t enum
 *      @endcode
 *************************************************************************************/
STATE_t IR_Read(IR_SENSOR_t sensor);

/**************************************************************************************
 * @brief       Scan all IR Sensors and return the status of all of them
 * @return  State of all sensors; HIGH if White, LOW if black.
 * @par Example:
 *      @code 
 *      IR_ReadAll();     
 *      // when it returns a 0x0F00FFF0(0B0000_1111_0000_0000_1111_1111_1111_0000):
 *      // This means:
 *      //    * (IR_0 --> IR_15) and (IR_24 --> IR_27) are on white track.
 *      //    * (IR_16 --> IR_23) and (IR_28 --> IR_31) are on black track.
 *      @endcode                 
 * @note    This function:
 *          * Only scans the configured sensors. So, if you have configured only IR_0 and IR_1, this function will only return a maximum of 0x00000003 (0B0000_0000_0000_0000_0000_0000_0000_0011)
 *          * Scans in the order of sensors' configurations. So, if you have configured IR_1 before IR_0 in the configuration, the status of IR_1 will be returned on bit 0 and the status of IR_0 will on bit 1.
 *************************************************************************************/
u32_t IR_ReadAll(void);

/**************************************************************************
 * @brief Get the number of configured IR sensors
 * @return Number of configured IR sensors
 * @par Example:
 *     @code IR_GetNumOfSensors();  // returns 2 if only IR_0 and IR_1 are configured   @endcode
 *************************************************************************/
u8_t IR_GetCount(void);

#endif  /* IR_H */