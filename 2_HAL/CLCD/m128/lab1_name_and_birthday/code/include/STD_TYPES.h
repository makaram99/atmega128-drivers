/***********************************************************************************
 * @file        STD_TYPES.h
 * @brief       Standard data types For AVR Microcontrollers
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @date	    2022-03-20
 * @version     1.0.0
 * @copyright   Copyright (c) 2022
 ***********************************************************************************/
#ifndef STD_TYPES_H				
#define STD_TYPES_H

/*---------------------------------------------------------------------------------*/
/*																			       */
/*						        PRIMITIVE DATA TYPES							   */
/*																			       */
/*---------------------------------------------------------------------------------*/

/* Signed integers	*/
typedef     signed long long int        s64_t;
typedef 	signed long int   	        s32_t;		
typedef 	signed short int 	        s16_t;		
typedef 	signed char                 s8_t;
  
/* Unsigned integers	*/
typedef     unsigned long long int      u64_t;
typedef 	unsigned long int	        u32_t;
typedef 	unsigned short int          u16_t;
typedef 	unsigned char 		        u8_t;

/* Float numbers	*/        
typedef 	float 				        f32_t;
typedef 	double 				        f64_t;
typedef 	long double 		        f96_t;


/*---------------------------------------------------------------------------------*/
/*																			       */
/*						            USER DATA TYPES							       */
/*																			       */
/*---------------------------------------------------------------------------------*/

/* Special types	*/        
 #undef __SIZE_TYPE__      /*!< This is a macro defined in the C standard library <stddef.h> for the size_t type */   
typedef 	u16_t   size_t;   /*!< size_t is an unsigned integer type of the result of the sizeof operator */

#undef HIGH
#undef LOW
typedef enum{
  LOW,
  HIGH,
  NORMAL              /* Used for any normal state */
}STATE_t;

typedef enum{
    ACTIVE_LOW,       /*!< Active low means that the pin is pulled low when the pin is set to high */
    ACTIVE_HIGH       /*!< Active high means that the pin is pulled high when the pin is set to low */
}ACTIVATION_STATUS_t;

/* Boolean type	*/
typedef enum{
    FALSE,
    TRUE
}BOOL_t;

typedef enum{
    ERROR_OK                = 0,            /*!< No error occured */
    ERROR_NOK               = 0x1,          /*!< Error occured */
    ERROR_TIMEOUT           = 0x2,          /*!< Timeout occured */
    ERROR_NULL_POINTER      = 0x4,          /*!< Null pointer occured */
    ERROR_BUSY              = 0x8,          /*!< Busy state occured */
    ERROR_NOT_INITIALIZED   = 0x10,         /*!< Not initialized state occured */
    ERROR_ILLEGAL_PARAM     = 0x20,         /*!< Invalid input state occured */   
    ERROR_OUT_OF_RANGE      = 0x40,         /*!< Out of range state occured */ 
	ERROR_INVALID_PARAMETER = 0x80
}ERROR_t;

/* Pointers	*/
#undef NULL 
#define NULL ((void *)0)  /*!< NULL pointer */

#undef NULL_BYTE
#define NULL_BYTE  ('\0')
 
#endif	  /* STD_TYPES_H */
