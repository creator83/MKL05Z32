#include "gpio.h"


GPIO_MemMapPtr Gpio::portAdr [2] = {PTA_BASE_PTR, PTB_BASE_PTR};
PORT_MemMapPtr Gpio::portAdrSet [2] = {PORTA_BASE_PTR, PORTB_BASE_PTR};


Gpio::Gpio()
{

}

Gpio::Gpio (Port p)
{
  prt = p;
//takt port
  SIM_SCGC5 |= (0x200 << p);
}

Gpio::Gpio(uint8_t p )
{
  prt = p;
//takt port
  SIM_SCGC5 |= (0x200 << p);
}


void Gpio::setPort (uint8_t p)
{
	prt = p;
	//takt port
	SIM_SCGC5 |= (0x200 << p);
}

void Gpio::setOutPin (uint8_t pin, mode m, dir d)
{
	PORT_PCR_REG(portAdrSet[prt],pin) |= m << 8;
	GPIO_PDDR_REG(portAdr[prt]) &= ~(1 << pin);
	GPIO_PDDR_REG(portAdr[prt]) |= (d << pin);
}

void Gpio::setOutPin (uint8_t pin, uint8_t m)
{
	PORT_PCR_REG(portAdrSet[prt],pin) |= m << 8;
}

void Gpio::setPin (uint8_t pin)
{
	GPIO_PSOR_REG(portAdr[prt]) |= 1 << pin;
}

void Gpio::clearPin (uint8_t pin)
{
	GPIO_PCOR_REG(portAdr[prt]) |= (1 << pin);
}

void Gpio::ChangePinState (uint8_t pin)
{
	GPIO_PTOR_REG(portAdr[prt]) |= 1 << pin;
}

void Gpio::SetPinState (uint8_t pin , uint8_t state)
{
	clearPin (pin);
	GPIO_PDOR_REG(portAdr[prt]) = (state << pin);
}

void Gpio::setOutPort (uint32_t value, mode m)
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

void Gpio::setValPort (uint32_t value)
{
	GPIO_PSOR_REG(portAdr[prt])  |= value;
}

void Gpio::clearValPort (uint32_t value)
{
	GPIO_PCOR_REG(portAdr[prt]) |= value;
}

bool Gpio::PinState (uint8_t pin)
{
  return (GPIO_PDIR_REG(portAdr[prt])&(1 << pin));
}
