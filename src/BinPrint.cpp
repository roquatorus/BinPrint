/*
  BinPrint.cpp - Library for enhanced binary printing.
  Created by roquatorus, August 28, 2021.
  GNU General Public License v3.0
*/

/*
  A tiny library for enhanced binary printing for the Arduino IDE Serial Monitor interface.
  Features and capabilities:
  - It always prints with one space between each nibble and two spaces between each byte
  - Capable to print without indent or with two character length indentation
  - Possibility of ending with a newline character
  - Possibility to choose between a general function and functions with parameters encoded in their names
  - Functions with parameters encoded in their names can print binary: 
    one byte, three nibbles, two bytes (word) or four bytes (double word)
  Benefits:
  - You can easily print any datagram that is easy to read because leading zeros are never omitted
  - You can choose between functions with indentation feature or without and with or without new line
    which makes formatting much easier.
  - You can also use the general function (binprint) to define printing parameters
  - An additional function of printing leading zeros is included
    to greatly simplify the formatting of integers in the printout
*/

#include "Arduino.h"
#include "BinPrint.h"

BinPrint::BinPrint() {}

void BinPrint::print(uint32_t data, uint8_t nibbles, bool newline, bool noindent) {
  const int8_t    SMALLGAP  = 0x03;             // both the bitmask and the pattern for narrow gaps
  const int8_t    LARGEGAP  = 0x07;             // both the bitmask and the pattern for wide gaps
  const int8_t    MSBPOS    = 4 * nibbles - 1;  // position of MSB (0-31) eg for two nibbles (one byte) it is 7
  const uint32_t  MSB       = 1ul << MSBPOS;    // bitmask of MSB eg for two nibbles it is 0x00000080
  if (noindent) {
    for (int8_t i = MSBPOS; i >= 0; i--) {
      if ((i & SMALLGAP) == SMALLGAP && i != MSBPOS) {
        Serial.write(' ');
        if ((i & LARGEGAP) == LARGEGAP && i != MSBPOS)
          Serial.write(' ');
      }
      if (data & MSB)
        Serial.write('1');
      else
        Serial.write('0');
      data <<= 1;
    }
  } else {
    for (int8_t i = MSBPOS; i >= 0; i--) {
      if ((i & SMALLGAP) == SMALLGAP) {
        Serial.write(' ');
        if ((i & LARGEGAP) == LARGEGAP)
          Serial.write(' ');
      }
      if (data & MSB)
        Serial.write('1');
      else
        Serial.write('0');
      data <<= 1;
    }
  }
  if (newline) Serial.write('\n');
}

void BinPrint::printByteNoIndent(uint8_t val)         { print((uint32_t)val, 2, false, true);  }
void BinPrint::printlnByteNoIndent(uint8_t val)       { print((uint32_t)val, 2, true,  true);  }
void BinPrint::printByte(uint8_t val)                 { print((uint32_t)val, 2, false, false); }
void BinPrint::printlnByte(uint8_t val)               { print((uint32_t)val, 2, true,  false); }

void BinPrint::print3NibblesNoIndent(uint16_t val)    { print((uint32_t)val, 3, false, true);  }
void BinPrint::println3NibblesNoIndent(uint16_t val)  { print((uint32_t)val, 3, true,  true);  }
void BinPrint::print3Nibbles(uint16_t val)            { print((uint32_t)val, 3, false, false); }
void BinPrint::println3Nibbles(uint16_t val)          { print((uint32_t)val, 3, true,  false); }

void BinPrint::printWordNoIndent(uint16_t val)        { print((uint32_t)val, 4, false, true);  }
void BinPrint::printlnWordNoIndent(uint16_t val)      { print((uint32_t)val, 4, true,  true);  }
void BinPrint::printWord(uint16_t val)                { print((uint32_t)val, 4, false, false); }
void BinPrint::printlnWord(uint16_t val)              { print((uint32_t)val, 4, true,  false); }

void BinPrint::printDwordNoIndent(uint32_t val)       { print(val, 8, false, true);  }
void BinPrint::printlnDwordNoIndent(uint32_t val)     { print(val, 8, true,  true);  }
void BinPrint::printDword(uint32_t val)               { print(val, 8, false, false); }
void BinPrint::printlnDword(uint32_t val)             { print(val, 8, true,  false); }

// printLeadingZeros - prints the leading zeros for positive number named val
// the input variable named digitsnumber is the total number of digits in the printed number

void BinPrint::printLeadingZeros(uint32_t val, int8_t digitsnumber) {
  while (digitsnumber > 1 && val < pow(10, --digitsnumber))
    Serial.write('0');
}
