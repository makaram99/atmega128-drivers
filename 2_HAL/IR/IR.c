/**************************************************************************************
 * @file        IR_Library.ino
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       IR sensors array used in Line follwer applications.
 * @version     1.0.0
 * @date        21 Aug 2021
 *************************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO.h"
#include "IR.h"
#include "IR_cfg.h"


/*------------------------------------------------------------------------------*/
/*                            PRIVATE FUNCTIONS PROTOTYPES                      */
/*------------------------------------------------------------------------------*/
static ERROR_t readIRIndex(const IR_t sensor, s8_t * const ptr_s8Index);

/*------------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                                */
/*------------------------------------------------------------------------------*/

ERROR_t IR_Init(void) {
    return ERROR_OK;
}
ERROR_t IR_Read(const IR_SENSOR_t sensor, STATE_t * const ptrToState) {
    ERROR_t error = ERROR_OK;
    s8_t i = 0;

    if (ptrToState == NULL) {
        return ERROR_NULL_POINTER;
    } 

    error |= readIRIndex(sensor, &i);
    if(i < 0) {
        return ERROR_INVALID_PARAMETER;
    }

    error |= DIO_ReadPin(irConfigs[i].pin, irConfigs[i].port, ptrToState);

    /* Check if the IR returns LOW for white color  */
    if( ACTIVE_LOW == IR_configs[i].ActiveHighOrLow ) { 
      *ptrToState = (*ptrToState ? LOW : HIGH);
    }

    return error;
}
ERROR_t IR_ReadAll(u32_t * const ptr_u32Value) {
    ERROR_t error = ERROR_OK;
    u8_t i = 0, sensorValue = 0;

    if (ptr_u32Value == NULL) {
        return ERROR_NULL_POINTER;
    }

    for(i = 0; i < countIRSensorsConfigured; ++i) {
      error |= (IR_Read(IR_configs[i].sensor, &sensorValue) << i);
      *ptr_u32Value |= (sensorValue << i);
    }

    return error;
}

ERROR_t IR_ReadCount(u8_t * const ptr_u8Count) {
    if (ptr_u8Count == NULL) {
        return ERROR_NULL_POINTER;
    }

    *ptr_u8Count = countIRSensorsConfigured;

    return ERROR_OK;
}



/*------------------------------------------------------------------------------*/
/*                              PRIVATE FUNCTIONS                               */
/*------------------------------------------------------------------------------*/
/******************************************************************************
 * @brief Get the index of the IR sensor in the IR_configs array
 * 
 * @param[in] sensor: The IR to get the index of
 * @param[in] ptr_s8Index: The pointer to the index of the IR. 
 *              Options:
 *                    -1: The IR is not in the IR_configs array
 *                  >= 0: The index of the IR in the IR_configs array
 * @return ERROR_t: The error status of the function.
 ******************************************************************************/
static ERROR_t readIRIndex(const IR_t sensor, s8_t * const ptr_s8Index) {
    ERROR_t error = ERROR_OK;
    u8_t i = 0;

    if(NULL == ptr_s8Index) {
        return ERROR_NULL_POINTER;
    }

    if( (sensor >= NUM_OF_IRS) || (sensor < IR_0) ) {
        *ptr_s8Index = -1;
        return ERROR_INVALID_PARAMETER;
    }

    *ptr_s8Index = -1;
    for(i = 0; i < countIRSensorsConfigured; ++i) {
        if(sensor == IR_configs[i].sensor) {
            *ptr_s8Index = i;
        }
    }
    
    return error;
}
