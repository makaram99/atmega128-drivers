/******************************************************************************
 * @file        SPI_cfg.h
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Configuration header file for \ref SPI.c
 * @version     1.0.0
 * @date        2022-03-20
 * @copyright   Copyright (c) 2022
 ******************************************************************************/
#ifndef SPI_CFG_H   
#define SPI_CFG_H   

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*              DO NOT CHANGE ANYTHING BELOW THIS COMMENT                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/


typedef enum{
    SPI_MASTER,
    SPI_SLAVE
}SPI_MODE_t;

typedef enum{
    SPI_DATA_ORDER_LSB_FIRST,
    SPI_DATA_ORDER_MSB_FIRST
}SPI_DATA_ORDER_t;

typedef enum{
    SPI_MODE0,
    SPI_MODE1,
    SPI_MODE2,
    SPI_MODE3
}SPI_CLOCK_MODE_t;

typedef enum{
    SPI_PRESCALER_2,
    SPI_PRESCALER_4,
    SPI_PRESCALER_8,
    SPI_PRESCALER_16,
    SPI_PRESCALER_32,
    SPI_PRESCALER_64,
    SPI_PRESCALER_128
}SPI_PRESCALER_t;

typedef enum{
    SPI_DOUBLE_SPEED_DISABLE,
    SPI_DOUBLE_SPEED_ENABLE
}SPI_DOUBLE_SPEED_t;

typedef struct{
    PIN_t   pin;
    PORT_t  port;
}SPI_PINS_t;

typedef struct{
    SPI_PINS_t  SS;
    SPI_PINS_t  MOSI;
    SPI_PINS_t  MISO;
    SPI_PINS_t  SCK;
}SPI_CONNECTIONS_t;

typedef struct{
    SPI_CONNECTIONS_t       connections;
    SPI_MODE_t              mode;
    SPI_DATA_ORDER_t        dataOrder;
    SPI_CLOCK_MODE_t        clockMode;
    SPI_PRESCALER_t         clockDivider;
    SPI_DOUBLE_SPEED_t      doubleSpeed;
}SPI_CONFIG_t;

extern SPI_CONFIG_t SPI_Config;

#endif                  
