#include "pit.h"

ptr pit::set_func [4] = {&pit::khz_set, &pit::hz_set, &pit::ms_set, &pit::us_set};



pit::pit (channel ch, uint16_t n, mode m)
{
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
	PIT->MCR = 0;
	n_ch = ch;
	(this->*(pit::set_func[m]))(n);
	PIT->CHANNEL[n_ch].TCTRL |= PIT_TCTRL_TIE_MASK|PIT_TCTRL_TEN_MASK;


	//enable interrupt
	NVIC_EnableIRQ (PIT_IRQn);

}

void pit::khz_set (uint16_t val)
{
	PIT->CHANNEL[n_ch].LDVAL = tact::get_frq_bus ()*1000/val;
}
void pit::hz_set (uint16_t val)
{
	PIT->CHANNEL[n_ch].LDVAL = tact::get_frq_bus ()*1000000/val;
}
void pit::ms_set (uint16_t val)
{
	PIT->CHANNEL[n_ch].LDVAL = tact::get_frq_bus ()*1000*val;
}

void pit::us_set (uint16_t val)
{
	PIT->CHANNEL[n_ch].LDVAL = tact::get_frq_bus ()*val;
}

void pit::clear_flag ()
{
	PIT->CHANNEL[n_ch].TFLG |= PIT_TFLG_TIF_MASK;
}

