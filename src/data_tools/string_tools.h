/**
 * \copyright    Copyright 2019 - 2022 Fraunhofer Institute for Integrated Circuits IIS, Erlangen Germany
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in the
 * Software without restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
 
/**
 * \file
 * \version     1.2.0
 * \brief       Function for string translations and modifications.
 */

#ifndef LIB_C_MODULES_STRINGS_STRING_TOOLS_H_
#define LIB_C_MODULES_STRINGS_STRING_TOOLS_H_

#include <inttypes.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************//**
 *  @brief Function converting an integer to its string representation.
 *
 *  @note la = left align in the target array
 *  @note zt = ZERO TERMINATED string is produced
 *
 *  @param[in]  i input integer
 *  @param[out] b array for the created string, MUST BE BIG ENOUGH to
 *                contain the entire string and ending zero (12B AT MOST)
 *
 *  @return     b is returned for convenience
 *
 *************************************************************************/
char* string_uint2str_la_zt(uint32_t i, char b[]);


/**
 * \brief       Unsigned integer to decimal ascii char array routine. No NULL termination!
 *
 * \param       dest        Memory location the ascii char array will be written to.
 * \param       destSize    Size of the buffer in byte, this will also limit the number of digits.
 * \param       n           integer to convert
 * \param       fillChar    If number is shorter than requested number of digits, the start of the string
 *                          will be filled with this character.
 *
 * \return      True,  if number of digits to represent the numer could fit in the destination.
 *              False, if number could not be fitted into buffer, leading digits will be cut off.
 */
bool string_uint2dec_nn(char * dest, uint8_t const destSize, uint32_t const nInput, char const fillChar);


/**
 * \brief        Transforms a decimal ASCII string to its unsigned integer value.
 *               No checking for correct input is done!
 *
 * \param[in]    decString       The string to be transformed, consisting of the characters: 0123456789
 * \param[in]    decStringLength Length of the decimal string
 *
 * \return       Value of the hexadecimal string as unsigned integer.
 */
uint32_t string_dec2uint(unsigned char const * decString, uint8_t const decStringLength);


/**
 * \brief        Transforms a hexadecimal ASCII string to its unsigned integer value.
 *               No checking for correct input is done!
 *               Most significant nibble first.
 *
 * \param[in]    hexString       The string to be transformed, consisting of the characters: 0123456789ABCDEFabcdef
 * \param[in]    hexStringLength Length of the hexadecimal string
 *
 * \return       Value of the hexadecimal string as unsigned integer.
 */
uint32_t string_hex2uint(unsigned char const * hexString, uint8_t const hexStringLength);

/**
 * \brief       Byte hex ascii char array routine. No NULL termination!
 *
 * \param       b           byte to convert
 * \param[out]  dest        Memory location the ascii hex array will be written to.
 */
void string_byte2hex(uint8_t const b, char dest[2]);

/**
 * \brief       Byte hex ascii char array routine. With NULL termination!
 *
 * \param       b           byte to convert
 * \param[out]  dest        Memory location the ascii hex array will be written to.
 *
 * \return     dest is returned for convenience
 */
char* string_byte2hex_zt(uint8_t const b, char dest[3]);

uint8_t string_hex2byteArray(unsigned char const * hexString, uint8_t const hexStringLength, uint8_t * dest, uint8_t destSize);

#ifdef __cplusplus
}
#endif



uint_fast16_t string_byteArray2hex(uint8_t const * byteArray, uint_fast16_t const nBytes, char * dest, uint_fast16_t const destSize);

#endif /* LIB_C_MODULES_STRINGS_STRING_TOOLS_H_ */
