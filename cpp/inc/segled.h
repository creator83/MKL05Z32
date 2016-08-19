#include "MKL17Z4.h"                 // Device header
#include "gpio.h"
#include "spi.h"

#ifndef SEGLED_H
#define SEGLED_H

#define USE_SPI




class segled
{
//variables
public:	
	enum Port {A , B , C , F=5};
	//enum Segment {a=0, b=1, c=3, d, e, f, g, dp};
	#ifdef USE_SPI
	enum Digit {first=0, second=1, third=2, fourth=3};
	
	#else
	enum Segment {a=0, b, c, d, e, f, g};
	enum Digit {first=10, second, third, fourth=15};
	
	#endif
	char buffer [4];
private:
	#ifdef USE_SPI
	spi shift_reg;
	static char pins [4];
	#else
	Gpio pin_segment;
	static char pins [4];
	#endif
	gpio pin_digit;
	static char number [11];
	static char numberdp [11];
	char n;
//functions

public:	
	#ifdef USE_SPI
	segled (Port dig);
	void segment (uint8_t val);
	#else
	segled (Port seg, Port dig);
	#endif
	void OFF ();
	void get_buffer (uint16_t val);
	void digit ();
	void frame (uint8_t dig);
private:
	
	
};


#endif
