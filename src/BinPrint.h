/*
  BinPrint.h - Library for enhanced binary printing.
  Created by roquatorus, August 28, 2021.
  GNU General Public License v3.0
*/

#ifndef BinPrint_h
#define BinPrint_h

#include "Arduino.h"

class BinPrint
{
  public:
    BinPrint();

    void print(uint32_t val, uint8_t nibbles, bool newline, bool noindent);

    void printByteNoIndent(uint8_t val);
    void printlnByteNoIndent(uint8_t val);
    void printByte(uint8_t val);
    void printlnByte(uint8_t val);

    void print3NibblesNoIndent(uint16_t val);
    void println3NibblesNoIndent(uint16_t val);
    void print3Nibbles(uint16_t val);
    void println3Nibbles(uint16_t val);

    void printWordNoIndent(uint16_t val);
    void printlnWordNoIndent(uint16_t val);
    void printWord(uint16_t val);
    void printlnWord(uint16_t val);

    void printDwordNoIndent(uint32_t val);
    void printlnDwordNoIndent(uint32_t val);
    void printDword(uint32_t val);
    void printlnDword(uint32_t val);

    void printLeadingZeros(uint32_t val, int8_t numberlength);
};

#endif
