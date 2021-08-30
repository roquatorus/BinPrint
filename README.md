# Roquatorus BinPrint Library #

  A tiny library for enhanced binary printing for the Arduino IDE Serial Monitor interface.
  This library allows the user to print easily and well-formatted in binary format, which makes the output easy to read.

## About the functions ##

  Summary
  The BinPrint library functions are designed to work with the Serial Monitor of the Arduino Software (IDE).
  All functions are designed to perform well-formatted printing in binary, 
  except one that prints leading zeros for positive decimal numbers.
  The list of all available functions can be found in the header file - BinPrint.h

  Features and capabilities:
  - Leading zeros are never omitted in the printout.
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
  - You can also use the general function print(ARGs) to define printing parameters
  - An additional function of printing leading zeros is included
    to greatly simplify the formatting of integers in the printout

## About License ##

  GNU General Public License v3.0 (https://github.com/roquatorus/BinPrint)

## About author ##

  Written by roquatorus.
