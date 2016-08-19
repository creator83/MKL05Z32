#include "spi.h"

//CS,SCK,MISO,MOSI
uint8_t spi::pins_d[3][4]={{4,5,6,7},{0,1,2,3},{16,17,18,19}};

SPI_MemMapPtr spi::spiAdr [2]={SPI0_BASE_PTR, SPI1_BASE_PTR};

PotMemFn spi::ptr_receive[2] = {};

PotMemF spi::ptr_transmite[2] = {};
ptr_ex spi::ptr_exchange[2] =  {};

spi::spi(Division d_, Cpol cpol_, Cpha cpha_, Size s, Role r)
:pin (gpio::D)
{
  
  //===Settings pins===//

  //Settings pins SCK, MOSI, MISO as ALT2
  	pin.setOutPort((1 << 4|1 << 5|1 << 6|1 << 7), gpio::Alt2);
  
  	n_spi = 1;
  //Turn on tacting SPI1
  SIM->SCGC4 |= SIM_SCGC4_SPI1_MASK;

  //===Settings SPI1===//
  SPI_S_REG(SPI1) = 0x00;

  	 SPI_BR_REG(SPI1) = SPI_BR_SPR(d_);
  	 SPI_C2_REG(SPI1) |= SPI_C2_MODFEN_MASK|(s<<SPI_C2_SPIMODE_SHIFT);
  	 SPI_C1_REG(SPI1) &= ~(SPI_C1_MSTR_MASK |SPI_C1_CPHA_MASK|SPI_C1_CPOL_MASK);
  	 SPI_C1_REG(SPI1) |= (r << SPI_C1_MSTR_SHIFT|cpol_ << SPI_C1_CPOL_SHIFT |cpha_ << SPI_C1_CPHA_SHIFT|SPI_C1_SSOE_MASK | SPI_C1_SPE_MASK);
}

spi::spi(PORT p, Division d_,  Cpol cpol_, Cpha cpha_, Size s, Role r)
:pin (p)
{
	pins_ = p-2;
	//Settings pins SCK, MOSI, MISO as ALT2
	pin.setOutPort((1 << pins_d [pins_][CS]|1 << pins_d [pins_][SCK]|1 << pins_d [pins_][MOSI]|1 << pins_d [pins_][MISO]), gpio::Alt2);


	//===Settings SPI===//
	//Turn on tacting SPI0
	SIM->SCGC4 |= SIM_SCGC4_SPI0_MASK;
	n_spi = 0;
	//Settings division
	 SPI_S_REG(SPI0) = 0x00;

	 SPI_BR_REG(SPI0) = SPI_BR_SPR(d_);
	 SPI_C2_REG(SPI0) |= SPI_C2_MODFEN_MASK|(s<<SPI_C2_SPIMODE_SHIFT);
	 SPI_C1_REG(SPI0) &= ~(SPI_C1_MSTR_MASK |SPI_C1_CPHA_MASK|SPI_C1_CPOL_MASK);
	 SPI_C1_REG(SPI0) |= (r << SPI_C1_MSTR_SHIFT|cpol_ << SPI_C1_CPOL_SHIFT |cpha_ << SPI_C1_CPHA_SHIFT|SPI_C1_SSOE_MASK | SPI_C1_SPE_MASK);
}


void spi::transmit_8 (uint16_t data)
{
	while(!(SPI_S_REG(spiAdr[n_spi]) & SPI_S_SPTEF_MASK));
	SPI_DL_REG(spiAdr[n_spi]) = (uint8_t)data;
}

void spi::transmit_16 (uint16_t data)
{
	while(!(SPI_S_REG(spiAdr[n_spi]) & SPI_S_SPTEF_MASK));
	SPI_DH_REG(spiAdr[n_spi]) = (uint8_t)(data >> 8);
	SPI_DL_REG(spiAdr[n_spi]) = (uint8_t)data;
}

void spi::transmit (uint16_t data)
{
	(this->*(spi::ptr_transmite[size_]))(data);
}

uint16_t spi::receive_8 ()
{
	while(!(SPI_S_REG(spiAdr[n_spi]) & SPI_S_SPTEF_MASK));
	SPI_DL_REG(spiAdr[n_spi]) = 0;
	while (!(SPI0->S & SPI_S_SPRF_MASK));
	uint8_t result = SPI_DL_REG(spiAdr[n_spi]);
	return result;

}

uint16_t spi::receive_16 ()
{
	while(!(SPI_S_REG(spiAdr[n_spi]) & SPI_S_SPTEF_MASK));
	SPI_DH_REG(spiAdr[n_spi]) = 0;
	SPI_DL_REG(spiAdr[n_spi]) = 0;
	while (!(SPI0->S & SPI_S_SPRF_MASK));
	uint16_t result = SPI_DH_REG(spiAdr[n_spi]) << 8;
	result |= SPI_DL_REG(spiAdr[n_spi]) << 8;
	return result;
}

uint16_t spi::receive ()
{
	 return (this->*(spi::ptr_receive[size_]))();
}


uint16_t spi::exchange_8 (uint16_t data)
{
	while(!(SPI_S_REG(spiAdr[n_spi]) & SPI_S_SPTEF_MASK));
	SPI_DL_REG(spiAdr[n_spi]) = (uint8_t)data;
	while (!(SPI0->S & SPI_S_SPRF_MASK));
	uint8_t result = SPI_DL_REG(spiAdr[n_spi]);
	return result;
}
uint16_t spi::exchange_16 (uint16_t data)
{
	while(!(SPI_S_REG(spiAdr[n_spi]) & SPI_S_SPTEF_MASK));
	SPI_DH_REG(spiAdr[n_spi]) = (uint8_t)data >> 8;
	SPI_DL_REG(spiAdr[n_spi]) = (uint8_t)data;
	while (!(SPI0->S & SPI_S_SPRF_MASK));
	uint16_t result = SPI_DH_REG(spiAdr[n_spi]) << 8;
	result |= SPI_DL_REG(spiAdr[n_spi]) << 8;
	return result;
}
uint16_t spi::exchange (uint16_t data)
{
	return (this->*(spi::ptr_exchange[size_]))(data);
}


void spi::put_data_dh (uint8_t data)
{
	SPI_DH_REG(spiAdr[n_spi]) = data;
}

void spi::put_data_dl (uint8_t data)
{
	SPI_DL_REG(spiAdr[n_spi]) = data;
}
uint8_t spi::get_data_dh ()
{
	return SPI_DH_REG(spiAdr[n_spi]);
}
uint8_t spi::get_data_dl ()
{
	return SPI_DL_REG(spiAdr[n_spi]);
}
bool spi::flag_sptef ()
{
	return SPI_S_REG(spiAdr[n_spi]) & SPI_S_SPTEF_MASK;
}
bool spi::flag_sprf ()
{
	return SPI0->S & SPI_S_SPRF_MASK;
}
