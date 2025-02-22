/******************************************************************************
 * @file        IR_cfg.h
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Configuration header file for \ref IR.c
 * @version     1.0.0
 * @date        2022-03-20
 * @copyright   Copyright (c) 2022
 ******************************************************************************/
#ifndef IR_CFG_H
#define IR_CFG_H

typedef struct{
  IR_SENSOR_t             sensor;
  DIO_PIN_t                   pin;
  DIO_PORT_t                  port;
  ACTIVATION_STATUS_t     ActiveHighOrLow;
}IR_CONFIG_t;

extern IR_CONFIG_t IR_configs[];
extern const u8_t countIRSensorsConfigured;

#endif  /* IR_CFG_H */