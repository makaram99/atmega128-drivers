/*********************************************************************************
 * @file        MATH.h
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Common math functions and constants.
 * @version     1.0.0
 * @date        2022-03-19
 * @copyright   Copyright (c) 2022
 **********************************************************************************/
#ifndef MATH_H
#define MATH_H

/*--------------------------------------------------------------------------------*/
/*                                                                                */
/*                          Mathematical Functions                                */
/*                                                                                */
/*--------------------------------------------------------------------------------*/

/*********************************************************************************
 * @brief The value of PI constant.
 * @note This value is used in the trigonometric functions. 
 **********************************************************************************/
#define PI      3.14159265358979323846

/*********************************************************************************
 * @brief Get the <b>Clamp value between min and max. </b>
 * @param[in] value: The value to clamp.
 * @param[in] min: The minimum value.
 * @param[in] max: The maximum value.
 * @return The clamped value.
 * @par Example:
 *  @code 
 *  CLAMP(1.0f, 0.0f, 1.0f);    // returns 1.0f    
 *  CLAMP(0.0f, 0.0f, 1.0f);    // returns 0.0f    
 *  CLAMP(-1.0f, 0.0f, 1.0f);   // returns 0.0f    
 *  CLAMP(2.0f, 0.0f, 1.0f);    // returns 1.0f    
 *  @endcode
 **********************************************************************************/
#define CLAMP(x, min, max)      ((x) < (min) ? (min) : ((x) > (max) ? (max) : (x)))

/*********************************************************************************
 * @brief Convert degrees to radians.
 * @param[in] degrees: The degrees to convert.
 * @return The radians.
 * @par Example:
 *  @code 
 *  DEG2RAD(180.0f);      // returns PI           
 *  DEG2RAD(0.0f);              // returns 0.0f   
 *  DEG2RAD(-180.0f);           // returns -PI    
 *  DEG2RAD(360.0f);            // returns 2*PI   
 *  DEG2RAD(-360.0f);           // returns -2*PI  
 *  DEG2RAD(720.0f);            // returns 4*PI   
 *  DEG2RAD(-720.0f);           // returns -4*PI  
 *  DEG2RAD(255.0f);            // returns 4.45059 
 *  @endcode
 **********************************************************************************/
#define DEG_TO_RAD(x)       ((x) * PI / 180.0f)

/*********************************************************************************
 * @brief Convert radians to degrees.
 * @param[in] radians: The radians to convert.
 * @return The degrees.
 * @par Example:
 *  @code 
 *  RAD2DEG(PI);          // returns 180.0f 
 *  RAD2DEG(0.0f);        // returns 0.0f   
 *  RAD2DEG(-PI);         // returns -180.0f
 *  RAD2DEG(2*PI);        // returns 360.0f 
 *  RAD2DEG(-2*PI);       // returns -360.0f
 *  RAD2DEG(4*PI);        // returns 720.0f 
 *  RAD2DEG(-4*PI);       // returns -720.0f
 *  RAD2DEG(4.45059);     // returns 255.0f
 *  @endcode
 **********************************************************************************/
#define RAD_TO_DEG(x)       ((x) * 180.0f / PI)

/*********************************************************************************
 * @brief Get the < b>minimum </b> value between two values.
 * @param[in] a: The first value.
 * @param[in] b: The second value.
 * @return The minimum value of the first and second values.
 * @par Example:
 *  @code 
 *  MIN(1.0f, 2.0f);        // returns 1.0f
 *  MIN(2.0f, 1.0f);        // returns 1.0f
 *  MIN(1.0f, 1.0f);        // returns 1.0f
 *  MIN(2.0f, 2.0f);        // returns 2.0f
 *  MIN(0.0f, -1.0f);       // returns -1.0f
 *  MIN(-1.0f, 0.0f);       // returns -1.0f
 *  MIN(-1.0f, -1.0f);      // returns -1.0f
 *  MIN(-2.0f, -1.0f);      // returns -2.0f
 *  MIN(-1.0f, -2.0f);      // returns -2.0f 
 *  @endcode
 **********************************************************************************/
#define MIN(a, b)   ((a) < (b) ? (a) : (b))

/*********************************************************************************
 * @brief Get the < b>maximum </b> value between two values.
 * @param[in] a: The first value.
 * @param[in] b: The second value.
 * @return The maximum value of the first and second values.
 * @par Example:
 *  @code 
 *  MAX(1.0f, 2.0f);            // returns 2.0f 
 *  MAX(2.0f, 1.0f);            // returns 2.0f 
 *  MAX(1.0f, 1.0f);            // returns 1.0f 
 *  MAX(2.0f, 2.0f);            // returns 2.0f 
 *  MAX(0.0f, -1.0f);           // returns 0.0f 
 *  MAX(-1.0f, 0.0f);           // returns 0.0f 
 *  MAX(-1.0f, -1.0f);          // returns -1.0f
 *  MAX(-2.0f, -1.0f);          // returns -1.0f
 *  MAX(-1.0f, -2.0f);          // returns -1.0f
 *  @endcode
 **********************************************************************************/
#define MAX(a, b)   ((a) > (b) ? (a) : (b))

/*********************************************************************************
 * @brief Absolute value of a number.
 * @param[in] x: The number to take the absolute value of.
 * @return The absolute value of x.
 * @par Example:
 *  @code 
 *  ABS(-1.0f);           // returns 1.0f
 *  ABS(1.0f);            // returns 1.0f
 *  ABS(0.0f);            // returns 0.0f
 *  ABS(-0.0f);           // returns 0.0f
 *  @endcode
 **********************************************************************************/
#define ABS(x)      ((x) < 0 ? -(x) : (x))

/*********************************************************************************
 * @brief Get the sign of a number.
 * @param[in] x: The number to get the sign of.
 * @return -1 if x is negative, 1 if x is positive, 0 if x is zero.
 * @par Example:
 *  @code 
 *  SIGN(-5);             // returns -1
 *  SIGN(5);              // returns 1
 *  @endcode
 **********************************************************************************/
#define SIGN(x)     ((x) < 0 ? -1 : 1)

/*********************************************************************************
 * @brief Check if the number is positive (greater than zero).
 * @param[in] x: The number to check.
 * @return TRUE if x is positive, FALSE otherwise.
 **********************************************************************************/
#define IS_POSITIVE(x)  ((x) > 0)

/*********************************************************************************
 * @brief Check if the number is negative (less than zero).
 * @param[in] x: The number to check.
 * @return TRUE if x is negative, FALSE otherwise.
 **********************************************************************************/
#define IS_NEGATIVE(x)  ((x) < 0)

/*********************************************************************************
 * @brief Get the floor value of a number. It is the largest integer that is less than or equal to x.
 * @param[in] x: The number to get the floor value of.
 * @return The floor value of x.
 * @par Example:
 *  @code 
 *  FLOOR(5.6f);          // returns 5 
 *  FLOOR(-5.3f);         // returns -6
 *  FLOOR(1.33f);         // returns 1 
 *  FLOOR(-1.33f);        // returns -2
 *  @endcode
 **********************************************************************************/
#define FLOOR(x)    ((int)(x) + ( (x) > 0 ? 0 : -1))

/*********************************************************************************
 * @brief Get the Ceil value of a number. It is the smallest integer that is greater than or equal to x.
 * @param[in] x: The number to get the Ceil value of.
 * @return The Ceil value of x.
 * @par Example:
 *  @code 
 *  CEIL(5.5f);   // returns 6 
 *  CEIL(-5.5f);  // returns -5
 *  CEIL(1.33f);  // returns 2
 *  @endcode
 **********************************************************************************/
#define CEIL(x)     ((int)(x) + ( (x) > 0 ? 1 : 0) )

/*********************************************************************************
 * @brief Get the round value of a number. It is the nearest integer to x.
 * @param[in] x: The number to get the round value of.
 * @return The round value of x.
 * @par Example:
 *  @code 
 *  ROUND(1.6f);      // returns 2.0f
 *  ROUND(-1.6f);     // 1.6f -2.0f  
 *  ROUND(1.33);      // returns 1.0f
 *  ROUND(-1.33f);    // returns -1.0f
 *  @endcode
 **********************************************************************************/
#define ROUND(x)    ( (int) ( (x) + ( (x) > 0 ? 0.5f : -0.5f) ) )

/*********************************************************************************
 * @brief Get the fractional part of a floating point number.
 * @param[in] x: The number to get the fractional part of.
 * @return The fractional part of x.
 * @par Example:
 *  @code 
 *  FRACTION(1.6f);           // returns 0.6f  
 *  FRACTION(-1.6f);          // returns -0.6f 
 *  FRACTION(1.33f);          // returns 0.33f 
 *  FRACTION(-1.33f);         // returns -0.33f
 *  FRACTION(1.0f);           // returns 0.0f  
 *  FRACTION(-1.0f);          // returns 0.0f  
 *  FRACTION(0.0f);           // returns 0.0f
 *  @endcode
 **********************************************************************************/
#define FRACTION(x)     ((x) - (int)(x))

/*********************************************************************************
 * @brief Gets the Linear Interpolation between two values.
 * @param[in] a: The first value.
 * @param[in] b: The second value.
 * @param[in] t: The interpolation value.
 * @return The interpolated value.
 * @par Example:
 *  @code 
 *  LERP(1.0f, 2.0f, 0.5f);           // returns 1.5f
 *  LERP(1.0f, 2.0f, 0.0f);           // returns 1.0f
 *  LERP(1.0f, 2.0f, 1.0f);           // returns 2.0f
 *  LERP(1.0f, 2.0f, 2.0f);           // returns 2.0f
 *  LERP(1.0f, 2.0f, -1.0f);          // returns 1.0f
 *  LERP(1.0f, 2.0f, -2.0f);          // returns 1.0f
 *  LERP(1.0f, 2.0f, 3.0f);           // returns 2.0f
 *  LERP(1.0f, 2.0f, -3.0f);          // returns 1.0f
 *  @endcode
 **********************************************************************************/
#define LERP(a, b, t) ((a) + (t) * ((b) - (a))) /* Linear interpolation */

/* TODO: Not implemented yet */
#define SQRT(x)     
#define POW(x, y)  
#define LOG(x)  
#define LOG2(x)
#define LOG10(x)
#define EXP(x)







/*--------------------------------------------------------------------------------*/
/*                                                                                */
/*                          Trigonometric Functions                               */
/*                                                                                */
/*--------------------------------------------------------------------------------*/

/*********************************************************************************
 * @brief Arc Cosine of an angle in radians. 
 * @param[in] x: The value to find the Arc Cosine of.
 * @note It has a range of [0, PI].
 * @note It is the inverse of the Cosine function.
 * @note It has a maximum error of 0.18 radians.
 **********************************************************************************/
#define ACOS(x)     ( (-0.69813170079773212 * (x) * (x) - 0.87266462599716477) * (x) + 1.5707963267948966 )

/*********************************************************************************
 * @brief Arc Sine of an angle in radians. 
 * @param[in] x: The value to find the Arc Sine of.
 * @note It has a range of [-PI/2, PI/2].
 * @note It is the inverse of the Sine function.
 * @note It has a maximum error of 0.18 radians.
 **********************************************************************************/
#define ASIN(x)     ( (0.69813170079773212 * (x) * (x) + 0.87266462599716477) * (x) + 1.5707963267948966 )

/*********************************************************************************
 * @brief Arc Tangent of an angle in radians. 
 * @param[in] x: The value to find the Arc Tangent of.
 * @note It has a range of [-PI/2, PI/2].
 * @note It is the inverse of the Tangent function.
 * @note It has a maximum error of 0.18 radians.
 **********************************************************************************/
#define ATAN(x)     ( (0.55228474983079331 * (x)) + 1.5707963267948966 )

/*********************************************************************************
 * @brief Cosine of an angle in radians. 
 * @param[in] x: The value to find the Cosine of.
 * @note It has a range of [0, 2*PI].
 * @note It is the inverse of the Arc Cosine function.
 * @note It has a maximum error of 0.18 radians.
 **********************************************************************************/
#define COS(x)      ( (0.87266462599716477 * (x)) + 1.5707963267948966 )

/*********************************************************************************
 * @brief Sine of an angle in radians. 
 * @param[in] x: The value to find the Sine of.
 * @note It has a range of [-PI/2, PI/2].
 * @note It is the inverse of the Arc Sine function.
 * @note It has a maximum error of 0.18 radians.
 **********************************************************************************/
#define SIN(x)      ( (0.69813170079773212 * (x)) + 1.5707963267948966 )

/*********************************************************************************
 * @brief Tangent of an angle in radians. 
 * @param[in] x: The value to find the Tangent of.
 * @note It has a range of [-PI/2, PI/2].
 * @note It is the inverse of the Arc Tangent function.
 * @note It has a maximum error of 0.18 radians.
 **********************************************************************************/
#define TAN(x)      ( (0.87266462599716477 * (x)) + 1.5707963267948966 )







/*--------------------------------------------------------------------------------*/
/*                                                                                */
/*                          General Functions                                     */
/*                                                                                */
/*--------------------------------------------------------------------------------*/

/***********************************************************************************
 * @brief This is a macro like function to get the size of an array in bytes
 * @param[in] array: The name of the array
 * @return The size of the array in bytes
 * @warning This macro is not intended to be used to get the size of a dynamic array. 
 *          The array must be declared at compile time. This is because the sizeof operator 
 *          is a compile time operator and cannot be used to get the size of a dynamic array.
 * @par Example:
 *  @code
 *  SIZE_OF_ARRAY(arrayName);   // returns the size of the array <arrayName> in bytes
 *  @endcode
 ***********************************************************************************/
#define SIZE_OF_ARRAY(array) ( sizeof(array) / sizeof(array[0]) )

#endif  /* MATH_H */