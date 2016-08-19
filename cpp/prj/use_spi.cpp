#include "MKL17Z4.h"
#include "gpio.h"
#include "tact.h"
#include "delay.h"
#include "spi.h"


tact frq;
const char CS=4;
const char SCK=5;
const char MOSI=6;
const char MISO=7;

//Tact port C
gpio spi_pin (gpio::C);



int main()
{
	spi spi_0 (spi::SPI_0, spi::C, spi::div32);

  while (1)
  {

	  spi_0.transmit_8(0xF0);
	  delay_ms (500);
	  spi_0.transmit_8(0x0F);
	  delay_ms (500);

<<<<<<< HEAD
	//===Settings SPI0===//
	// div=32
	SPI0->BR |= SPI_BR_SPR(6);
	SPI0->C2 |= SPI_C2_MODFEN_MASK;
	SPI0->C1 |= SPI_C1_MSTR_MASK |SPI_C1_SSOE_MASK | SPI_C1_SPE_MASK ;
=======
>>>>>>> f421c2740bb825a19a056ba5c013110c8570a68d

  }
}


