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
 * \brief       String translations and modifications.
 */


// SOURCE CODE
// ***** INCLUDES *********************************************************************************
#include <stddef.h>
#include "string_tools.h"
#include "char_tools.h"

// ***** DEFINES **********************************************************************************
// ***** DECLARATIONS *****************************************************************************
// ***** GLOABL VARIABLES *************************************************************************
// ***** LOCAL VARIABLES **************************************************************************

static char const digitLut[] = {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
};

static uint32_t const pow10Lut[] = {
        1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000
};

// ***** PROTOTYPES *******************************************************************************
// ***** FUNCTIONS ********************************************************************************

char* string_uint2str_la_zt(uint32_t i, char b[]) {
    char* p = b;

    uint32_t shifter = i;
    do { //Move to where representation ends
        ++p;
        shifter = shifter / 10;
    } while(shifter);

    char * endOfString = p;

    *p = '\0';
    do { //Move back, inserting digits as u go
        *--p = '0' + (i % 10);
        i = i / 10;
    } while(i);

    return endOfString;
}

/**
 * \brief       Generic integer to char array routine. Converts integer to a string.
 */
bool string_uint2dec_nn(char * dest, uint8_t const destSize, uint32_t const nInput, char const fillChar) {
    // size of buffer - 1 to get the maximum index, not the size
    uint8_t const maxDigitIndex = destSize - 1;
    uint32_t n = nInput;

    // add digits
    uint8_t nDigitsAdded = 0;
    do {
        dest[maxDigitIndex - nDigitsAdded] = digitLut[n % 10];
        nDigitsAdded++;
        n = n / 10;
    } while(n > 0);

    // add leading characterss if necessary
    while(nDigitsAdded < destSize) {
        dest[maxDigitIndex - nDigitsAdded] = fillChar;
        nDigitsAdded++;
    }

    // check inputs
    if(n > pow10Lut[destSize]) return false;

    // return true
    return true;
}


uint32_t string_dec2uint(unsigned char const * decString, uint8_t const decStringLength) {
    uint32_t conversionResult = 0;
    for(uint8_t i = 0; i < decStringLength; i++) {
        conversionResult = conversionResult * 10 + char_dec2uint(decString[i]);
    }
    return conversionResult;
}


uint32_t string_hex2uint(unsigned char const * hexString, uint8_t const hexStringLength) {
    uint32_t volatile conversionResult = 0;
    for(uint8_t i = 0; i < hexStringLength; i++) {
        conversionResult = (conversionResult << 4) + char_hex2uint(hexString[i]);
    }
    return conversionResult;
}

void string_byte2hex(uint8_t const b, char dest[2]) {
    dest[0] = char_nibble2hex(b >> 4);
    dest[1] = char_nibble2hex(b);
}

char * string_byte2hex_zt(uint8_t const b, char dest[3]) {
    dest[0] = char_nibble2hex(b >> 4);
    dest[1] = char_nibble2hex(b);
    dest[2] = 0;
    
    return dest;
}

uint_fast16_t string_byteArray2hex(uint8_t const * byteArray, uint_fast16_t const nBytes, char * dest, uint_fast16_t const destSize) {
    if(destSize < 2 * nBytes) { return 0; }

    for(uint_fast16_t i = 0; i < nBytes; i++) {
        string_byte2hex(byteArray[i], &dest[i*2]);
    }

    return 2*nBytes;
}

uint8_t string_hex2byteArray(unsigned char const * hexString, uint8_t const hexStringLength, uint8_t * dest, uint8_t destSize){
    if(destSize < hexStringLength/2 || hexStringLength&1) { return 0; }

    for(uint_fast16_t i = 0; i < destSize; i++) {
        *(dest+i) = char_hex2uint(*(hexString+2*i))<<4 | char_hex2uint(*(hexString+2*i+1));
    }
    return 1;
}
