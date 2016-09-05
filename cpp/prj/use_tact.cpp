#include "MKL05Z4.h"                    // Device header
#include "tact.h"
#include "delay.h"
#include "i2c.h"

tact frq;

const uint16_t N = 400;

uint8_t source [] =
{

};

void init_dma ();

int main()
{


	delay_ms(1000);
	while (1)
	{

	}
}

void init_dma ()
{
	//Tact DMA & DMAMUX
	SIM->SCGC7 |= SIM_SCGC7_DMA_MASK;
	SIM->SCGC6 |= SIM_SCGC6_DMAMUX_MASK;

	//Settings DMAMUX Channel 0, 17 - SPI0 transmit
	DMAMUX0->CHCFG [0] = DMAMUX_CHCFG_ENBL_MASK  | DMAMUX_CHCFG_SOURCE(17);

	//settings DMA
	DMA0->DMA[0].DAR = (uint32_t)&SPI0->D;
	DMA0->DMA[0].SAR = (uint32_t)source;
	DMA0->DMA[0].DSR_BCR = DMA_DSR_BCR_BCR(N);
	DMA0->DMA[0].DCR = (DMA_DCR_EINT_MASK|DMA_DCR_SINC_MASK|DMA_DCR_SSIZE(1)|DMA_DCR_DSIZE(1));


	//settings SPI

	SPI0->C2 |= SPI_C2_TXDMAE_MASK;



}

