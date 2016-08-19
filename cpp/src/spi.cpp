#include "spi.h"

//CS(A),SCK(B),MOSI(A), MISO(A)
uint8_t spi::pins_d[4]={5,0,6,7};


spi::spi(Division d_, Cpol cpol_, Cpha cpha_, Mode m, Role r)
:pin_A (gpio::A), pin_B (gpio::B)
{
  
  //===Settings pins===//

  //Settings pins SCK, MOSI, MISO as ALT3
	pin_A.setOutPort (((1 << pins_d[CS])|(1 << pins_d[MOSI])|(1 << pins_d[MISO])), gpio::Alt3);
	pin_B.setOutPin (pins_d[SCK], gpio::Alt3);

  //Turn on tacting SPI1
  SIM->SCGC4 |= SIM_SCGC4_SPI0_MASK;

  //===Settings SPI1===//

  //Settings baudrate
  SPI0->BR = SPI_BR_SPPR(d_);

  //Settings hardware mode
  SPI0->C2 &= ~SPI_C2_MODFEN_MASK;

  SPI0->C2 |= m << SPI_C2_MODFEN_SHIFT;

  //

  SPI0->C1 &= ~(SPI_C1_MSTR_MASK |SPI_C1_CPHA_MASK|SPI_C1_CPOL_MASK|SPI_C1_SSOE_MASK);

  SPI0->C1 |= (r << SPI_C1_MSTR_SHIFT|cpol_ << SPI_C1_CPOL_SHIFT|cpha_ << SPI_C1_CPHA_SHIFT|m << SPI_C1_SSOE_SHIFT | SPI_C1_SPE_MASK);
}


void spi::transmit (uint8_t data)
{
	while(!(SPI0->S & SPI_S_SPTEF_MASK));
	SPI0->D = data;
}


uint8_t spi::receive ()
{
	while(!(SPI0->S & SPI_S_SPTEF_MASK));
	SPI0->D = 0;
	while (!(SPI0->S & SPI_S_SPRF_MASK));
	return SPI0->D;
}

uint8_t spi::exchange (uint8_t data)
{
	while(!(SPI0->S & SPI_S_SPTEF_MASK));
	SPI0->D = data;
	while (!(SPI0->S & SPI_S_SPRF_MASK));
	return SPI0->D;
}
void spi::put_data (uint8_t data)
{
	SPI0->D = data;
}

uint8_t spi::get_data ()
{
	return SPI0->D;
}

bool spi::flag_sptef ()
{
	return SPI0->S & SPI_S_SPTEF_MASK;
}

bool spi::flag_sprf ()
{
	return SPI0->S & SPI_S_SPRF_MASK;
}

void spi::set_CS (PORT p, uint8_t pin)
{
	pin_CS.setPort (p);
	pin_CS.setOutPin (pin);
	p_CS = pin;
}

void spi::assert_CS()
{
	pin_CS.clearPin (p_CS);
}

void spi::disassert_CS()
{
	pin_CS.setPin (p_CS);
}
