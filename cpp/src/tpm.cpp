#include "tpm.h"

TPM_MemMapPtr tpm::tpm_ptr[3]={TPM0_BASE_PTR, TPM1_BASE_PTR};



tpm::tpm(N_TPM n_, channel ch, division d)
{
	num_tpm = n_;
	n_ch = ch;

	SIM->SCGC6 |= (SIM_SCGC6_TPM0_MASK << num_tpm);
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(3);
	TPM_SC_REG(tpm_ptr [num_tpm]) &= ~TPM_SC_PS_MASK;
	TPM_SC_REG(tpm_ptr [num_tpm]) |= TPM_SC_PS(d);

}

void tpm::Set_MOD (uint16_t val)
{
	TPM_MOD_REG(tpm_ptr [num_tpm]) = val;
}

void tpm::Set_CNV (uint16_t val)
{
	TPM_CnV_REG(tpm_ptr [num_tpm],n_ch) = val;
}

void tpm::start ()
{
	TPM_SC_REG(tpm_ptr [num_tpm]) |= TPM_SC_CMOD(1);
}

void tpm::stop ()
{
	TPM_SC_REG(tpm_ptr [num_tpm]) &= ~TPM_SC_CMOD_MASK;
}

void tpm::clear_flag ()
{
	TPM_SC_REG(tpm_ptr [num_tpm]) |= TPM_SC_TOF_MASK;
}

void tpm::init_output_togle(Port p_, alt_mode alt_, uint8_t pin_, toggle_mode t_mode)
{
	pin.setPort (p_);
	pin.setOutPin (pin_, alt_);
	TPM_SC_REG(tpm_ptr [num_tpm]) &= ~TPM_SC_CPWMS_MASK;
	TPM_CnSC_REG(tpm_ptr [num_tpm],n_ch) &= ~(TPM_CnSC_ELSA_MASK|TPM_CnSC_ELSB_MASK|TPM_CnSC_MSA_MASK|TPM_CnSC_MSB_MASK);
	TPM_CnSC_REG(tpm_ptr [num_tpm],n_ch) |= TPM_CnSC_MSA_MASK|(t_mode << TPM_CnSC_ELSA_SHIFT);
}

void tpm::init_output_pulse(Port p_, alt_mode alt_, uint8_t pin_, pulse_mode p_mode)
{
	pin.setPort (p_);
	pin.setOutPin (pin_, alt_);
	TPM_SC_REG(tpm_ptr [num_tpm]) &= ~TPM_SC_CPWMS_MASK;
	TPM_CnSC_REG(tpm_ptr [num_tpm],n_ch) &= ~(TPM_CnSC_ELSA_MASK|TPM_CnSC_ELSB_MASK|TPM_CnSC_MSA_MASK|TPM_CnSC_MSB_MASK);
	TPM_CnSC_REG(tpm_ptr [num_tpm],n_ch) |= TPM_CnSC_MSA_MASK|TPM_CnSC_MSB_MASK|(p_mode << TPM_CnSC_ELSA_SHIFT) ;
}

void tpm::init_edge_pwm(Port p_, alt_mode alt_, uint8_t pin_, e_pwm_mode e_mode)
{
	pin.setPort (p_);
	pin.setOutPin (pin_, alt_);
	TPM_SC_REG(tpm_ptr [num_tpm]) &= ~TPM_SC_CPWMS_MASK;
	TPM_CnSC_REG(tpm_ptr [num_tpm],n_ch) &= ~(TPM_CnSC_ELSA_MASK|TPM_CnSC_ELSB_MASK|TPM_CnSC_MSA_MASK|TPM_CnSC_MSB_MASK);
	TPM_CnSC_REG(tpm_ptr [num_tpm],n_ch) |= TPM_CnSC_MSB_MASK|(e_mode << TPM_CnSC_ELSA_SHIFT) ;

}

void tpm::init_center_pwm(Port p_, alt_mode alt_, uint8_t pin_, e_pwm_mode e_mode)
{
	pin.setPort (p_);
	pin.setOutPin (pin_, alt_);
	TPM_SC_REG(tpm_ptr [num_tpm]) |= TPM_SC_CPWMS_MASK;
	TPM_CnSC_REG(tpm_ptr [num_tpm],n_ch) &= ~(TPM_CnSC_ELSA_MASK|TPM_CnSC_ELSB_MASK|TPM_CnSC_MSA_MASK|TPM_CnSC_MSB_MASK);
	TPM_CnSC_REG(tpm_ptr [num_tpm],n_ch) |= TPM_CnSC_MSB_MASK|(e_mode << TPM_CnSC_ELSA_SHIFT) ;
}


