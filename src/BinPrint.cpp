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

#define SMALLGAPSMASK 0x03
#define LARGEGAPSMASK 0x07

BinPrint::BinPrint() {}

void BinPrint::print(uint32_t data, uint8_t nibbles, bool newline, bool noindent) {
  int8_t    msbpos   = 4 * nibbles - 1;
  uint32_t  msbmask  = 1ul << msbpos;
  if (noindent) {
    for (int8_t i = msbpos; i >= 0; i--) {
      if ((i & SMALLGAPSMASK) == SMALLGAPSMASK && i != msbpos) {
        Serial.write(' ');
        if ((i & LARGEGAPSMASK) == LARGEGAPSMASK && i != msbpos)
          Serial.write(' ');
      }
      if (data & msbmask)
        Serial.write('1');
      else
        Serial.write('0');
      data <<= 1;
    }
  } else {
    for (int8_t i = msbpos; i >= 0; i--) {
      if ((i & SMALLGAPSMASK) == SMALLGAPSMASK) {
        Serial.write(' ');
        if ((i & LARGEGAPSMASK) == LARGEGAPSMASK)
          Serial.write(' ');
      }
      if (data & msbmask)
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

// printLeadingZeros - for unsigned numbers - prints the leading zeros of val. The number length is how many digits should take.

void BinPrint::printLeadingZeros(uint32_t val, int8_t numberlength) {
  for (int8_t i = numberlength - 1; i > 0; i--) {
    if (val >= pow(10, i)) {
      break;
    }
    else {
      Serial.write('0');
    }
  }
}

