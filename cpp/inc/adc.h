#include "MKL17Z4.h"                 // Device header
#include "gpio.h"


#ifndef LIB_ADC_H_
#define LIB_ADC_H_

class adc
{
public:
	enum channel {SE0, SE1, SE2, SE3, SE4a, SE5a, SE6a, SE7a, SE8, SE9, SE11=11, SE12, SE13, SE14, SE15, SE23=23};
	enum Port {B=1, C, D, E};
	enum resolution {bit8, bit12, bit10, bit16};
private:
	static const uint8_t pin_def [10][2];
	gpio pin;
	uint8_t n_channel;
	uint8_t res;
	union {

		unsigned error :1;
	}flags;
public:
	adc(channel ch_, resolution r_);
	uint16_t convert ();
};

#endif /* LIB_ADC_H_ */
