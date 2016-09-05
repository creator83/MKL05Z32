#include "MKL05Z4.h"
#include "tact.h"
#include "gpio.h"


#ifndef TPM_H
#define TPM_H


class tpm
{
  //variables
public:
	enum channel {ch0, ch1, ch2, ch3, ch4, ch5};
	enum Port {A, B, C, D, E};
	enum alt_mode {Alt0 , Alt1 , Alt2 , Alt3, Alt4 , Alt5 , Alt6};
	enum N_TPM {TPM_0, TPM_1};
	enum mode_clock {TPM_disable, TPM_inc, TPM_ext};
	enum MODE {Input, Output_toggle, Output_pulse, Edge_Pwm, Center_Pwm, Software_compare};
	enum division {div1, div2, div4, div8, div16, div32, div64, div128};
	enum toggle_mode {toggle=1, clear, set};
	enum pulse_mode {output_high=1, output_low};
	enum e_pwm_mode {low_pulse=1, high_pulse};

	//enum mode {khz, hz, ms, us};
private:
	uint8_t n_ch;
	static TPM_MemMapPtr tpm_ptr[3];
	uint8_t num_tpm;
	gpio pin;

public:
	tpm(N_TPM n_, channel ch, division d);
	void clear_flag ();
	void start ();
	void stop ();
	void init_output_togle(Port p_, alt_mode alt_, uint8_t pin_, toggle_mode t_mode);
	void init_output_pulse(Port p_, alt_mode alt_, uint8_t pin_, pulse_mode p_mode);
	void init_edge_pwm(Port p_, alt_mode alt_, uint8_t pin_, e_pwm_mode e_mode);
	void init_center_pwm(Port p_, alt_mode alt_, uint8_t pin_, e_pwm_mode e_mode);
	void Set_MOD (uint16_t val);
	void Set_CNV (uint16_t val);
private:
	void khz_set (uint16_t val);
	void hz_set (uint16_t val);
	void ms_set (uint16_t val);
	void us_set (uint16_t val);
};

#endif /* PIT_H */
