#include "MKL05Z4.h"
#include "tact.h"



#ifndef PIT_H
#define PIT_H

class pit;
typedef void (pit::*ptr)(uint16_t);


class pit
{
  //variables
public:
	enum channel {ch0, ch1};
	enum mode {khz, hz, ms, us};
private:
	const uint8_t irq_n = 68;
	uint8_t n_ch;
	static ptr set_func [4];
public:
	pit(channel ch, uint16_t n, mode m = ms);
	void clear_flag ();
private:
	void khz_set (uint16_t val);
	void hz_set (uint16_t val);
	void ms_set (uint16_t val);
	void us_set (uint16_t val);
};

#endif /* PIT_H */
