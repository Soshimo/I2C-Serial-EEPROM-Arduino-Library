/*
  i2cEEPROM.cpp - I2C Serial EEPROM library
  Copyright (c) 2012 Scott R. McCain.  All right reserved.

  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
  associated documentation files (the "Software"), to deal in the Software without restriction, including
  without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the
  following conditions:

  The above copyright notice and this permission notice shall be included in all copies or substantial portions
  of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
  TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
  CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
  IN THE SOFTWARE.

*/

#include "i2cEEPROM.h"
#include <Wire.h>

i2cEEPROMClass::i2cEEPROMClass() {
	init();
}

void i2cEEPROMClass::begin(int deviceid) {
	m_deviceid = deviceid;
	Wire.begin(); // wake up, I2C!
}

void i2cEEPROMClass::writeByte(unsigned int add, byte data) {
	Wire.beginTransmission(m_deviceid);

	Wire.write((int)(add >> 8));   // left-part of pointer address
	Wire.write((int)(add & 0xFF)); // and the right
	Wire.write(data);
	Wire.endTransmission();
	
	delay(10);
}

byte i2cEEPROMClass::readByte(unsigned int add) // reads a byte of data from memory location 'add' in chip at I2C address 'device'
{
	byte result;  // returned value
	
	Wire.beginTransmission(m_deviceid); //  these three lines set the pointer position in the EEPROM
	Wire.write((int)(add >> 8));   // left-part of pointer address
	Wire.write((int)(add & 0xFF)); // and the right
	
	Wire.endTransmission();
	Wire.requestFrom(m_deviceid, 1); // now get the byte of data...
	result = Wire.read();  
	
	return result; // and return it as a result of the function readData
}

void i2cEEPROMClass::writeBuffer(unsigned int add, byte *buffer, int offset, unsigned int count) {
	byte * p = buffer + offset;
	for(int idx = 0;idx < count; p++, idx++) {
		writeByte(add + idx, *p);
	}
}

int i2cEEPROMClass::readBuffer(unsigned int add, byte *buffer, int offset, unsigned int count) {
	byte * p = buffer + offset;
	int idx = 0;
	for(int idx = 0;idx < count; p++, idx++) {
		*p = readByte(add + idx);
	}
	
	return idx;
}

	// write the string pointed to by str
void i2cEEPROMClass::writeString(unsigned int add, char *str) {
	char * p = str;
	
	while(*p) {
		writeByte(add + (p - str), *((byte *)p));
	}
}
	
	// returns the string written at add, maximum characters limited
	// have to free the string when done or leakage
char * i2cEEPROMClass::readString(unsigned int add, int max) {
	char * str = (char *)malloc(sizeof(char) * max);
	
	int idx = 0;
	
	while(idx < max) {
		str[idx] = (char)readByte(add + idx);
		
		if( !str[idx] )
			break;
			
		idx++;
	}

	return str;
}
	
// Preinstantiate Objects //////////////////////////////////////////////////////

i2cEEPROMClass i2cEEPROM = i2cEEPROMClass();