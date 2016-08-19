#include "MKL17Z4.h"                    // Device header
#include "gpio.h"
#include "delay.h"


int main ()
{
  Gpio E (Gpio::E);
	Gpio D (Gpio::D);
 // E.setOutPin (16);
	/*PORTE->GPCHR |= (1 << 16) |(1 << 8);
	PTE->PDDR |= 1 << 16;*/
	
  E.setOutPort (0xF0000);
	D.setOutPort (0xFF);
	//E.test();

  while (1)
  {
    E.setPin (16);
    delay_ms (1000);
    E.clearPin (16);
    delay_ms (1000);
  }
}
