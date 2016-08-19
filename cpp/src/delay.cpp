#include "delay.h"

extern "C"
{
  void SysTick_Handler ();
}

uint16_t delay;

void SysTick_Handler (void)
{
	if (delay > 0)delay--;
}

void delay_ms (uint16_t del)
{
	SysTick_Config (tact::get_frq_cpu()*1000);
	delay = del;
	while (delay);
}

void delay_us (uint16_t del)
{
	SysTick_Config (tact::get_frq_cpu()*1000000);
	delay = del;
	while (delay);
}
