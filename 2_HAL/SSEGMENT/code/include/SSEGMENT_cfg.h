#ifndef SSEGMENT_CFG_H   
#define SSEGMENT_CFG_H   

#define POV_ENABLE       (1U)


typedef enum{
    COMMON_ANODE,
    COMMON_CATHODE
}COMMON_CONNECTION_t;

typedef struct{
    DIO_PIN_t   pin;
    DIO_PORT_t  port;
}ENABLE_PIN_t;

typedef struct {
    SSEGMENT_t              segment;
    DIO_PORT_t                  port;
    COMMON_CONNECTION_t     anodeOrCathode;
    ENABLE_PIN_t            enable;
}SSEGMENT_CONFIGS_t;

extern SSEGMENT_CONFIGS_t segmentsConfigs[];
extern u8_t digitsConfigs[];
extern u8_t countSegments;
extern u8_t countDigits;


#endif                  
