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
 * \brief       Functions for character translations and modifications.
 */


#ifndef CHARTOOLS_H_
#define CHARTOOLS_H_

#ifdef __cplusplus
extern "C" {
#endif

// ***** INCLUDES *********************************************************************************
#include <inttypes.h>

// ***** DEFINES **********************************************************************************
// ***** DECLARATIONS *****************************************************************************
// ***** GLOABL VARIABLES *************************************************************************
// ***** PROTOTYPES *******************************************************************************

/**
 * \brief        Transforms decimal ASCII characters to their unsigned integer value.
 *               No checking for correct input is done!
 *
 * \param[in]    decChar        The caracter to be transformed, has to be one of these characters: 0123456789
 *
 * \return       Value of the decimal character as unsigned integer.
 */
uint8_t char_dec2uint(char const decChar);

/**
 * \brief        Transforms hexadecimal ASCII characters to their unsigned integer value.
 *               No checking for correct input is done!
 *
 * \param[in]    hexChar        The caracter to be transformed, has to be one of these characters: 0123456789ABCDEFabcdef
 *
 * \return       Value of the hexadecimal character as unsigned integer.
 */
uint8_t char_hex2uint(char const hexChar);

/**
 * \brief        Transforms the lowest 4 bit of a number into the hexadecimal character.
 *               No checking for correct input is done!
 *
 * \param[in]    nibble     The nibble to be transformed.
 *
 * \return       ASCII character representing the hexadecimal value of this nibble.
 */
char char_nibble2hex(uint8_t const nibble);

inline char char_digit2ascii(uint8_t const digit) {
    return digit + 48;
}

#ifdef __cplusplus
}
#endif

#endif /* CHARTOOLS_H_ */
