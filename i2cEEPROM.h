/*
  i2cEEPROM.h - I2C Serial EEPROM library
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

#ifndef _I2CEEPROM_H
#define _I2CEEPROM_H

#include <Arduino.h>

class i2cEEPROMClass {


private:
	int m_deviceid;

public:
	i2cEEPROMClass();

	void begin(int deviceId);

	int getDeviceId() const { return m_deviceid; }

	// writes a byte of data 'data' to the chip at I2C address 'device', in memory location 'add'
	void writeByte(unsigned int add, byte data);

	// reads a byte of data from memory location 'add' in chip at I2C address 'device'
	byte readByte(unsigned int add);

	void writeBuffer(unsigned int add, byte *buffer, int offset, unsigned int count);
	int readBuffer(unsigned int add, byte *buffer, int offset, unsigned int count);

	// write the string pointed to by str
	void writeString(unsigned int add, char *str);

	// returns the string written at add, maximum characters limited
	// have to free the string when done or leakage
	char * readString(unsigned int add, int max);
};

extern i2cEEPROMClass i2cEEPROM;

#endif