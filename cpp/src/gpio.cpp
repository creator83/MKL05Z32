#include "gpio.h"


GPIO_MemMapPtr gpio::portAdr [2] = {PTA_BASE_PTR, PTB_BASE_PTR};
PORT_MemMapPtr gpio::portAdrSet [2] = {PORTA_BASE_PTR, PORTB_BASE_PTR};


gpio::gpio()
{

}

gpio::gpio (Port p)
{
  prt = p;
//takt port
  SIM_SCGC5 |= (0x200 << p);
}

gpio::gpio(uint8_t p )
{
  prt = p;
//takt port
  SIM_SCGC5 |= (0x200 << p);
}


void gpio::setPort (uint8_t p)
{
	prt = p;
	//takt port
	SIM_SCGC5 |= (0x200 << p);
}

void gpio::setOutPin (uint8_t pin, mode m, dir d)
{
	PORT_PCR_REG(portAdrSet[prt],pin) |= m << 8;
	GPIO_PDDR_REG(portAdr[prt]) &= ~(1 << pin);
	GPIO_PDDR_REG(portAdr[prt]) |= (d << pin);
}

void gpio::setOutPin (uint8_t pin, uint8_t m)
{
	PORT_PCR_REG(portAdrSet[prt],pin) |= m << 8;
}

void gpio::setPin (uint8_t pin)
{
	GPIO_PSOR_REG(portAdr[prt]) |= 1 << pin;
}

void gpio::clearPin (uint8_t pin)
{
	GPIO_PCOR_REG(portAdr[prt]) |= (1 << pin);
}

void gpio::ChangePinState (uint8_t pin)
{
	GPIO_PTOR_REG(portAdr[prt]) |= 1 << pin;
}

void gpio::SetPinState (uint8_t pin , uint8_t state)
{
  if (state)setPin (pin);
  else clearPin (pin);  
}

void gpio::setOutPort (uint32_t value, mode m)
{
	union
	{
		uint32_t full;
		uint16_t half[2];
	}val;
	val.full = value;
	PORT_GPCLR_REG(portAdrSet[prt]) = (val.half[0]<<16| 0x80 << m);
	PORT_GPCHR_REG(portAdrSet[prt]) = (val.half[1]<<16| 0x80 << m);
	if (m == 1)
	{
		GPIO_PDDR_REG(portAdr[prt]) |= value;
	}
}

void gpio::setValPort (uint32_t value)
{
	GPIO_PSOR_REG(portAdr[prt])  |= value;
}

void gpio::clearValPort (uint32_t value)
{
	GPIO_PCOR_REG(portAdr[prt]) |= value;
}

bool gpio::PinState (uint8_t pin)
{
  return (GPIO_PDIR_REG(portAdr[prt])&(1 << pin));
}
