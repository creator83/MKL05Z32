#include "tact.h"

uint8_t tact::cpu_clock;
uint8_t tact::bus_clock;
uint8_t tact::mcgir_clock;


tact::tact ()
{

	cpu_clock = 41;
	bus_clock = 20;
	init_FEI ();
}
/*
tact::tact (src_tact s)
{
  src = s;
  f_cpu = 48;
}*/

tact::tact (mode m, uint8_t frq)
{

}

void tact::init_FEI (cpu_div cpu_d, bus_div bus_d)
{
	SIM->COPC = (uint32_t)0x00u;

	// ��������� ��������� ������� OUTDIV1=0 (�������� core clock=1), OUTDIV4=1 (�������� bus clock = 2)
	SIM->CLKDIV1 = (SIM_CLKDIV1_OUTDIV1(cpu_d) | SIM_CLKDIV1_OUTDIV4(bus_d)); /* Update system prescalers */

	// Switch to FEI Mode
	/* MCG->C1: CLKS=0 (�������� FLL), FRDIV=0 (�������� = 1),IREFS=1 (��������� �������� ������������ 32kHz),
	 IRCLKEN=1 (������������ mcgirckl �� ����������� ���������),IREFSTEN=0 */
	MCG->C1 = MCG_C1_CLKS(0x00)|MCG_C1_FRDIV(0x00)|MCG_C1_IREFS_MASK|MCG_C1_IRCLKEN_MASK;

	// MCG->C2: RANGE0=0 (�������������� �������� ������������),HGO0=0,EREFS0=0,LP=0,IRCS=0
	MCG->C2 = MCG_C2_RANGE0(0x00);
	/* MCG_C4: DMX32=0(ocs=31.25-39.0625),DRST_DRS=1 (��������� = 1280) */
	MCG->C4 = (uint8_t)((MCG->C4 & (uint8_t)~(uint8_t)(MCG_C4_DMX32_MASK|MCG_C4_DRST_DRS(0x02)))|(uint8_t)(MCG_C4_DRST_DRS(0x01)));

	 /* OSC0->CR: ERCLKEN=1,??=0,EREFSTEN=0,??=0,SC2P=0,SC4P=0,SC8P=0,SC16P=0 */
	//  OSC0->CR = OSC_CR_ERCLKEN_MASK;

	//��������, ��� FLL ����������� �� ����������� ���������
	while((MCG->S & MCG_S_IREFST_MASK) == 0x00U);

	//�������� ������������ �� FLL
	while((MCG->S & MCG_S_CLKST(0x03)) != 0x00U);


}

void tact::init_FEE (cpu_div cpu_d, bus_div bus_d)
{
	//������������ ����� � ��� ������
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;

	// ��������� ��������� ������� OUTDIV1=0 (�������� core clock=1), OUTDIV4=1 (�������� bus clock = 2)
	SIM->CLKDIV1 = (SIM_CLKDIV1_OUTDIV1(cpu_d) | SIM_CLKDIV1_OUTDIV4(bus_d)); /* Update system prescalers */

	//��������� ����� 3 � 4 ��� ����������� ������
	PORTA->PCR[3] &= (uint32_t)~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));
	PORTA->PCR[4] &= (uint32_t)~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));

	// Switch to FEE Mode
	// MCG->C2: LOCRE0=0,??=0,RANGE0=0(�������������� �������� ������������ 32768kHz),EREFS0=1 (������� �����)
	MCG->C2 = (MCG_C2_RANGE0(0x00) | MCG_C2_EREFS0_MASK);

	// OSC0->CR: ERCLKEN=1(���������� ��������� ������)
	OSC0->CR = OSC_CR_ERCLKEN_MASK;

	/* MCG->C1: CLKS=0 (�������� FLL), FRDIV=0 (�������� = 1),IREFS=1 (��������� �������� ������������ 32kHz),
	IRCLKEN=1 (������������ mcgirckl �� ����������� ���������)*/
	MCG->C1 = (MCG_C1_CLKS(0x00) | MCG_C1_FRDIV(0x00) | MCG_C1_IRCLKEN_MASK);

	//MCG->C4: DMX32=1 (�������� ������������ = 32768Hz),DRST_DRS=1(��������� = 1464) */
	MCG->C4 = (uint8_t)((MCG->C4 & (uint8_t)~(uint8_t)(MCG_C4_DRST_DRS(0x02)))|(uint8_t)(MCG_C4_DMX32_MASK|MCG_C4_DRST_DRS(0x01)));

	//��������, ��� FLL ����������� �� �������� ������
	while((MCG->S & MCG_S_IREFST_MASK) != 0x00U);

	//�������� ������������ �� FLL
	while((MCG->S & MCG_S_CLKST(0x03)) != 0x00U);
}

void tact::init_BLPI (cpu_div cpu_d, bus_div bus_d)
{
	// ��������� ��������� ������� OUTDIV1=0 (�������� core clock=1), OUTDIV4=1 (�������� bus clock = 2)
	SIM->CLKDIV1 = (SIM_CLKDIV1_OUTDIV1(cpu_d) | SIM_CLKDIV1_OUTDIV4(bus_d)); /* Update system prescalers */

	/* MCG->SC: FCRDIV=0(�������� ������� fast int osc=1) */
	MCG->SC &= (uint8_t)~(uint8_t)(MCG_SC_FCRDIV(0x07));

	/* Switch to FBI Mode */
	/* MCG->C1: CLKS=1(������������ �� ����������� ���������),FRDIV=0,
	IREFS=1 (������������ FLL �� ����������� ���������),IRCLKEN=1(������������ mcgirckl �� ����������� ���������)*/
	MCG->C1 = MCG_C1_CLKS(0x01)|MCG_C1_FRDIV(0x00)|MCG_C1_IREFS_MASK|MCG_C1_IRCLKEN_MASK;

	// MCG->C2: LOCRE0=0,??=0,RANGE0=0,HGO0=0,EREFS0=0,LP=0,IRCS=1(������������ mcgirckl �� fast int osc(4MHz)
	MCG->C2 = (MCG_C2_RANGE0(0x00) | MCG_C2_IRCS_MASK);

	// MCG->C4: ��� ����������
	MCG->C4 &= (uint8_t)~(uint8_t)((MCG_C4_DMX32_MASK | MCG_C4_DRST_DRS(0x03)));

	/* OSC0->CR: ERCLKEN=1,??=0,EREFSTEN=0,??=0,SC2P=0,SC4P=0,SC8P=0,SC16P=0 */
	  OSC0->CR = OSC_CR_ERCLKEN_MASK;

	//��������, ��� FLL ����������� �� ����������� ������
	while((MCG->S & MCG_S_IREFST_MASK) == 0x00U);

	//�������� ������������ �� ����������� ���������
	while((MCG->S & MCG_S_CLKST(0x03)) != 0x01U);

	/* Switch to BLPI Mode */
	// MCG->C2: LP=1 (���������� FLL � bypass ������),IRCS=1 (������������ �� fast int osc (4MHz))
	MCG->C2 = (MCG_C2_RANGE0(0x00) | MCG_C2_LP_MASK | MCG_C2_IRCS_MASK);

	//��������, ��� FLL ����������� �� ����������� ���������
	while((MCG->S & MCG_S_IREFST_MASK) == 0x00U);

	//��������, ��� ����������� �� fast int osc (4MHz)
	while((MCG->S & MCG_S_IRCST_MASK) == 0x00U);

}


void tact::Set_frq (uint8_t frq)
{


}


