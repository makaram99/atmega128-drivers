#ifndef SSEGMENT_H       
#define SSEGMENT_H    

typedef enum{
    SEGMENT0,
    SEGMENT1,
    SEGMENT2,
    SEGMENT3,
    SEGMENT4,
    SEGMENT5,
    SEGMENT6,
    SEGMENT7,
    NUM_OF_SEGMENTS
}SSEGMENT_t;

/*******************************************************************************
 * @brief   Initialize the SSEGMENT module.
 * @return  ERROR_t: error code. See ERROR_t \ref enum.
 ******************************************************************************/
ERROR_t SSEGMENT_Init(void);

/*******************************************************************************
 * @brief   Write a digit on the selected seven segment. 
 * @note    If the POV_ENABLE is enabled, the function will turn off the enable
 *          pin of all segments, before writing the digit, then turn on the enable
 *          pin of the selected segment.
 * @param[in] digit: The digit to be written on the seven segment:
 *                   From 0 to 15: 0 to 9, A to F.
 * @return  ERROR_t: error code. See ERROR_t \ref enum.
 ******************************************************************************/
ERROR_t SSEGMENT_WriteDigit(const SSEGMENT_t segment, const u8_t digit);

/*******************************************************************************
 * @brief   Write a character on the selected seven segment. 
 * @note    If the POV_ENABLE is enabled, the function will turn off the enable
 *          pin of all segments, before writing the digit, then turn on the enable
 *          pin of the selected segment.
 * @param[in] ch: The character to be written on the seven segment: From A to F.
 * @return  ERROR_t: error code. See ERROR_t \ref enum.
 ******************************************************************************/
ERROR_t SSEGMENT_WriteChar(const SSEGMENT_t segment, const char ch);

/*******************************************************************************
 * @brief   Write the number on the seven segments. 
 * @note    The number is written on the seven segments in the following way:
 *          - The first digit is written on the first segment.
 *          - The second digit is written on the second segment.
 *          - The third digit is written on the third segment.
 *          - And so on.
 * @note    If the POV_ENABLE is enabled, the number will be written on the 
 *          segments in for 1 second.
 * @param[in] number: The number to be written on the seven segments.
 * @return  ERROR_t: error code. See ERROR_t \ref enum.
 ******************************************************************************/
ERROR_t SSEGMENT_WriteNumber(const u32_t number);

#endif                  
