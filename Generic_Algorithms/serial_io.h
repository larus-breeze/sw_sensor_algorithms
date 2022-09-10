/***********************************************************************//**
 * @file		serial_io.h
 * @brief		serial input output abstract class (interface)
 * @author		Dr. Klaus Schaefer
 * @copyright 		Copyright 2021 Dr. Klaus Schaefer. All rights reserved.
 * @license 		This project is released under the GNU Public License GPL-3.0

    <Larus Flight Sensor Firmware>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

**************************************************************************/

#ifndef SERIAL_IO_H_
#define SERIAL_IO_H_

#include "ascii_support.h"

class serial_input
{
public:
	int  geti( void);
	virtual bool input_ready(void)
	{
	  return false; // ... just a stub
	}
	virtual char get( void)
	{
	  asm("bkpt 0"); // doesn't make sense
	}
	virtual char get_blocking( void)
	{
	  return get(); // default if blocking not supported
	}
};
class serial_output
{
public:
	virtual void put( char) // another stub
	{
	}
	void puti( int value, int base=10);
	void putx( int32_t value, uint8_t digits = 8);
	void putf( float value);
	virtual void puts( const char * data);
	void newline( void);
	void blank( void);
};

class serial_io: public serial_output, public serial_input
{
};

template <unsigned size> class ascii_string_writer : public serial_output
{
public:
  ascii_string_writer(void)
  : p(buf)
  {
    *p=0;
  }
  void put( char c)
  {
    if(( buf+size-p) < 2)
      return; // buffer full, give up silently
    *p++ = c;
    *p = 0;
  }
  void puts( char *c)
  {
    while( (buf+size-p) >= 2)
      *p++=*c++;
    *p=0;
  }
  void putf( float value)
  {
    if( (buf+size-p) <10)
      return;
    ftoa( value, p);
    while( *p)
      ++p;
  }
    const char *get_content(void)
  {
    return buf;
  }
private:
  char buf[size];
  char *p;
};

#endif /* SERIAL_IO_H_ */
