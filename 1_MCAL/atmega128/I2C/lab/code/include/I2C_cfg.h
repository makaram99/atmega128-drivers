/******************************************************************************
 * @file        I2C_cfg.h
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Configuration header file for \ref I2C.c
 * @version     1.0.0
 * @date        2022-03-20
 * @copyright   Copyright (c) 2022
 ******************************************************************************/
#ifndef I2C_CFG_H   
#define I2C_CFG_H   

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*              DO NOT CHANGE ANYTHING BELOW THIS COMMENT                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/


typedef enum{
    I2C_MASTER,
    I2C_SLAVE
}I2C_MODE_t;

typedef enum{
    I2C_DATA_ORDER_LSB_FIRST,
    I2C_DATA_ORDER_MSB_FIRST
}I2C_DATA_ORDER_t;

typedef enum{
    I2C_MODE0,
    I2C_MODE1,
    I2C_MODE2,
    I2C_MODE3
}I2C_CLOCK_MODE_t;

typedef enum{
    I2C_PRESCALER_2,
    I2C_PRESCALER_4,
    I2C_PRESCALER_8,
    I2C_PRESCALER_16,
    I2C_PRESCALER_32,
    I2C_PRESCALER_64,
    I2C_PRESCALER_128
}I2C_PRESCALER_t;

typedef enum{
    I2C_DOUBLE_SPEED_DISABLE,
    I2C_DOUBLE_SPEED_ENABLE
}I2C_DOUBLE_SPEED_t;

typedef struct{
    DIO_PINS_t   pin;
}I2C_PINS_t;

typedef struct{
    I2C_PINS_t  SDA;
    I2C_PINS_t  SCL;
}I2C_CONNECTIONS_t;

typedef struct{
    I2C_CONNECTIONS_t       connections;
    I2C_MODE_t              mode;
    I2C_DATA_ORDER_t        dataOrder;
    I2C_CLOCK_MODE_t        clockMode;
    I2C_PRESCALER_t         clockDivider;
    I2C_DOUBLE_SPEED_t      doubleSpeed;
}I2C_CONFIG_t;

extern I2C_CONFIG_t I2C_Config;

#endif                  
