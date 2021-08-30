/*
  Examples of using the functions included in the BinPrint library

  The BinPrint library functions are designed to work with the Serial Monitor of the Arduino Software (IDE).
  All functions are designed to perform well-formatted printing in binary, 
  except one that prints leading zeros for positive decimal numbers.
  The list of all available functions can be found in the header file - BinPrint.h

  Hardware Required:
  - Arduino Board

  The circuit:
  - None, but the board has to be connected to the computer through the serial port or the USB port.
  
  Created 30 August 2021
  By roquatorus

  https://github.com/roquatorus/BinPrint

*/

#include <BinPrint.h>

BinPrint bin;

const uint32_t BAUDRATE = 115200;
const uint32_t TENBITSDELAY = 10000000 / BAUDRATE + 10;

void setup() {
  Serial.setTimeout(200);                         // sets the maximum milliseconds to wait for serial data. It defaults to 1000 milliseconds.
  Serial.begin(BAUDRATE);                         // opens serial port, sets data rate to 115200 bps
  while (!Serial) {                               // wait for serial port to connect. Needed for native USB
    continue;
  }
  randomSeed(analogRead(0));                      // shuffle the random function
}

void loop() {
  
  byte datagram[8];
  for (int i = 0; i < 8; i++)
    datagram[i] = (byte)random(256);
  newline();
  Serial.print(F("Let there be some randomly generated datagram (eight bytes - Qword): 0x"));
  for (int i = 0; i < 8; i++)
    Serial.print(datagram[i], HEX);
  Serial.println(F("  Attention! In this hex number leading zeros are omitted."));

  // For the clarity of an example:
  byte           firstByte    = datagram[0];
  byte           secondByte   = datagram[1];
  byte           thirdByte    = datagram[2];
  byte           fourthByte   = datagram[3];
  byte           fifthByte    = datagram[4];
  byte           sixthByte    = datagram[5];
  byte           seventhByte  = datagram[6];
  byte           eighthByte   = datagram[7];
  unsigned int   firstWord    = ((unsigned int)firstByte << 8) + secondByte;
  unsigned int   secondWord   = ((unsigned int)thirdByte << 8) + fourthByte;
  unsigned int   thirdWord    = ((unsigned int)fifthByte << 8) + sixthByte;
  unsigned int   fourthWord   = ((unsigned int)seventhByte << 8) + eighthByte;
  unsigned long  firstDword   = ((unsigned long)firstWord << 16) + secondWord;
  unsigned long  secondDword  = ((unsigned long)thirdWord << 16) + fourthWord;
  
  newline();
  Serial.println(F("Printout of the first byte in binary without indentation - you can use printByteNoIndent() or printlnByteNoIndent():"));
  bin.printlnByteNoIndent(firstByte);

  newline();
  Serial.println(F("Printout of the second byte in binary with indentation - you can use printByte() or printlnByte():"));
  bin.printlnByte(secondByte);

  newline();
  Serial.println(F("The same, but in one line - the printByteNoIndent()function was used followed by printlnByte():"));
  bin.printByteNoIndent(firstByte);
  bin.printlnByte(secondByte);

  newline();
  Serial.println(F("Same, but the printlnWordNoIndent() function was used:"));
  bin.printlnWordNoIndent(firstWord);

  newline();
  Serial.println(F("Printout of the last byte in binary without indentation - printlnByteNoIndent() function was used:"));
  bin.printlnByteNoIndent(eighthByte);

  newline();
  Serial.println(F("Printout of the last word in binary with indentation - printlnWord() function was used:"));
  bin.printlnWord(fourthWord);

  newline();
  Serial.println(F("A printout of the last one and a half byte (12 bits) in binary - you can use print3Nibbles form (nibble == half-byte)"));
  Serial.println(F("This function is very useful for testing analog inputs, especially for testing the voltage ripple Vref of the ADC"));
  Serial.print(F("ADC:"));
  bin.println3Nibbles(fourthWord);
  
  newline();
  Serial.print(F("Printout of the first Dword in binary - you can use "));
  Serial.println(F("printDwordNoIndent() or printlnDwordNoIndent() or printDword() or printlnDword():"));
  bin.printlnDwordNoIndent(firstDword);
  
  newline();
  Serial.println(F("Printout of the entire datagram - Qword - the printDwordNoIndent()function was used followed by printlnDword():"));
  bin.printDwordNoIndent(firstDword);
  bin.printlnDword(secondDword);
    
  newline();
  Serial.print(F("For special requirements an example of using the main print() function. "));
  Serial.println("A printout of five nibbles from the third to the seventh:");
  bin.print((firstDword & 0x00FFFFFF) >> 4, 5, true, true);
    
  newline();
  Serial.println(F("Formatting output with printLeadingZeros() function:"));
  unsigned int val;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 10; j++) {
      Serial.print(F("   value"));
      Serial.print(j, DEC);
      Serial.print(F(": "));
      val = (byte)random(256);
      bin.printLeadingZeros(val, 3);
      Serial.print(val, DEC);
    }
    newline();
  }

  newline();
  Serial.print(F("Send anything to view the new datagram"));
  while (!Serial.available()) {
    continue;
  }
  newline();
  while (Serial.available()) {
    Serial.read();
    delayMicroseconds(TENBITSDELAY);
  }
}

void newline() {
  Serial.write('\n');
}

