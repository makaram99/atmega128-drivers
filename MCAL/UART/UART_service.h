/**************************************************************************
 * @file        UART_service.h
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       UART services interfaces file
 * @version     1.0.0
 * @date        2022-03-03
 * @copyright   Copyright (c) 2022
 **************************************************************************/
#ifndef UART_SERVICE_H
#define UART_SERVICE_H

/******************************************************************************
 * @brief Send a string using UART module 0
 * @par   For Example: UART0_SendString("Hello World"); will send string "Hello World" to UART module 0
 ******************************************************************************/
void UART0_SendString(const u8_t * const string);

void UART0_SendString_Checksum(const u8_t * const string);

/******************************************************************************
 * @brief Send a string using UART module 1
 * @par   For Example: UART1_SendString("Hello World"); will send string "Hello World" 
 *        to UART module 1.
 * @note  String must be null terminated: "Hello World\0". So, the last 
 *        character must be '\0'.
 * @note  Sending "Hello World" will send "Hello World\0" because it is null terminated 
 *        implicitly. But if you are sending an array of characters, you must 
 *        explicitly null terminate it by adding '\0' at the end of the array.
 *        --> string[lenght-1] = '\0'
 ******************************************************************************/
void UART1_SendString(const u8_t * const string);

/******************************************************************************
 * @brief Send a sequence of elements, each element has 9 bits, using UART module 0
 * @param[in] string: Pointer to the first element of the sequence
 * @note Size of each element should be 2 Bytes to be able to send 9 bits data
 * @par  For Example: UART0_Send9BitDataSequence(string); will send elements of 9 bits 
 *       each to UART module 0.
 * @note The sequence should be ended with a NULL pointer(0): The last element of the sequence
 *       should be a NULL pointer.
 * @note But if you are sending an array, you must explicitly null terminate it 
 *       by adding '\0' at the end of the array --> string[lenght-1] = '\0'
 ******************************************************************************/
void UART0_Send9BitString(const u16_t * const string);

/********************************************************************************
 * @brief Send a sequence of elements, each element has 9 bits, using UART module 1
 * @param[in] string: Pointer to the first element of the sequence
 * @note Size of each element should be 2 Bytes to be able to send 9 bits data
 * @par  For Example: UART1_Send9BitDataSequence(string); will send elements of 9 bits
 *      each to UART module 1.
 * @note The sequence should be ended with a NULL pointer(0): The last element of the sequence
 *      should be a NULL pointer.
 * @note But if you are sending an array, you must explicitly null terminate it
 *     by adding '\0' at the end of the array --> string[lenght-1] = '\0'
 ********************************************************************************/
void UART1_Send9BitString(const u16_t * const string);

/************************************************************************
 * @brief Write Integer to UART0 as a string
 * @param[in] integer: The integer to be written
 * @par For Example: 
 *          * UART0_WriteInt(123) will write the string "123" to UART0
 *          * UART0_WriteInt(-123) will write the string "-123" to UART0
 ************************************************************************/
void UART0_SendInteger(s32_t integer);

/************************************************************************
 * @brief Write Integer to UART1 as a string
 * @param[in] integer: The integer to be written
 * @par For Example: 
 *          * UART1_WriteInt(123) will write the string "123" to UART1
 *          * UART1_WriteInt(-123) will write the string "-123" to UART1
 ************************************************************************/
void UART1_SendInteger(s32_t integer);

/************************************************************************
 * @brief Write Float to UART0 as a string
 * @param[in] number: The number to be written
 * @par For Example:
 *         * UART0_WriteFloat(123.456, 3) will write the string "123.456" to UART0
 *         * UART0_WriteFloat(123.456, 2) will write the string "123.45" to UART0
 *         * UART0_WriteFloat(123.456, 5) will write the string "123.45600" to UART0
 *         * UART0_WriteFloat(-123.456, 3) will write the string "-123.456" to UART0
 *         * UART0_WriteFloat(-123.456, 2) will write the string "-123.45" to UART0
 *         * UART0_WriteFloat(-123.456, 5) will write the string "-123.45600" to UART0
 ************************************************************************/
void UART0_SendFloat(float number, const u8_t precision);

/************************************************************************
 * @brief Write Float to UART1 as a string
 * @param[in] number: The number to be written
 * @par For Example:
 *         * UART1_WriteFloat(123.456, 3) will write the string "123.456" to UART1
 *         * UART1_WriteFloat(123.456, 2) will write the string "123.45" to UART1
 *         * UART1_WriteFloat(123.456, 5) will write the string "123.45600" to UART1
 *         * UART1_WriteFloat(-123.456, 3) will write the string "-123.456" to UART1
 *         * UART1_WriteFloat(-123.456, 2) will write the string "-123.45" to UART1
 *         * UART1_WriteFloat(-123.456, 5) will write the string "-123.45600" to UART1
 ************************************************************************/
void UART1_SendFloat(float number, const u8_t precision);

/******************************************************************************
 * @brief Receive a string of characters (unsigned 8 bits data) using UART module 0
 * @par   For Example: UART0_ReceiveString(string); will receive a string of characters
 *        from UART module 0 and store it in variable <string>
 * @return The error code: ERROR_NO if no error, ERROR_YES if error
 * @warning  The string will be null terminated. So, the last character will be '\0'.
 *           So, the length of the string should be strlen(string) + 1.
 ******************************************************************************/
ERROR_t UART0_ReceiveString(u8_t * const string);

void UART0_SendString_Asynchronous(const u8_t * const string);

/********************************************************************************
 * @brief Receive a string of characters (unsigned 8 bits data) using UART module 1
 * @par   For Example: UART1_ReceiveString(string); will receive a string of characters
 *        from UART module 1 and store it in variable <string>
 * @return The error code: ERROR_NO if no error, ERROR_YES if error
 * @warning  The string will be null terminated. So, the last character will be '\0'.
 *           So, the length of the string should be strlen(string) + 1.
 ********************************************************************************/
ERROR_t UART1_ReceiveString(u8_t * const string);

void UART1_SendString_Asynchronous(const u8_t * const string);

ERROR_t UART0_ReceiveString_Checksum(u8_t * const string);

/******************************************************************************
 * @brief Receive a string of elements, each element has 9 bits, using UART module 0.
 * @param[in] string: Pointer to the first element of the sequence (pointer to 16 bits)
 * @note Size of each element should be 2 Bytes to be able to receive 9 bits data
 * @par  For Example: UART0_Receive9BitDataSequence(string); will receive elements of 9 bits
 *       each from UART module 0.
 * @warning The sequence will be ended with a NULL pointer(0): The last element of the sequence
 *       will be a NULL pointer. So, consider the length of the sequence as strlen(string) + 1.
 ******************************************************************************/
ERROR_t UART0_Receive9BitString(u16_t * const string);

/******************************************************************************
 * @brief Receive a string of elements, each element has 9 bits, using UART module 1.
 * @param[in] string: Pointer to the first element of the sequence (pointer to 16 bits)
 * @note Size of each element should be 2 Bytes to be able to receive 9 bits data
 * @par  For Example: UART1_Receive9BitDataSequence(string); will receive elements of 9 bits
 *      each from UART module 1.
 * @warning The sequence will be ended with a NULL pointer(0): The last element of the sequence
 *     will be a NULL pointer. So, consider the length of the sequence as strlen(string) + 1.
 ******************************************************************************/
ERROR_t UART1_Receive9BitString(u16_t * const string);

#endif  /* UART_SERVICE_H */
