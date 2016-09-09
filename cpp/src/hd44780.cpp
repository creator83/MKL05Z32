#include "hd44780.h"


Hd44780::Hd44780()
:pinData (Gpio::A), pinCommand1(Gpio::A), pinCommand2(Gpio::B)
{
	pinData.setOutPort ((0x0F<<shift_data), Gpio::Alt1);
	pinCommand1.setOutPin (E);
	pinCommand2.setOutPin (RS);

}

void Hd44780::init ()
{
	delay_ms (15);
	tetra (0x03);
	delay_ms (4);
	tetra (0x03);
	delay_us (100);
	tetra (0x03);
	delay_ms (1);
	tetra (0x02);
	delay_ms (1);

	// 2 strings
	send_byte (0x28, command);
	delay_ms (1);
	//turn on display
	send_byte (0x0C, command);
	delay_ms (1);
	send_byte (0x06, command);
	delay_ms (1);
}

void Hd44780::tetra (uint8_t t)
{
	E_assert ();
	delay_us (50);
	pinData.clearValPort (0x0F<<shift_data);
	t &= 0x0F;
	pinData.setValPort(t<<shift_data);
	E_disassert ();
	delay_us (50);
}

void Hd44780::send_byte (uint8_t b, instruction i)
{
	uint8_t hb = 0;
	hb = b >> 4;
	pinCommand1.SetPinState (RS, i);
	tetra (hb);
	tetra (b);
}

void Hd44780::send_data (uint8_t b)
{
	uint8_t hb = 0;
	hb = b >> 4;
	RS_assert ();
	tetra (hb);
	tetra (b);
}

void Hd44780::send_string (uint8_t *str)
{
	while (*str)send_data (*str++);
}

void Hd44780::clear ()
{
	send_byte (clear_dram, command);
	delay_us (1500);
}

void Hd44780::set_position (uint8_t col, uint8_t row)
{
	uint8_t addr = second_col*col + row;
	send_byte (addr|set_dram_addr, command);
}

void Hd44780::newChar (uint8_t *ch, uint8_t addr)
{
	send_byte ((set_cgram_addr+addr*8),command);
	for (uint8_t i=0;i<8;++i, ch++) send_data (*ch);
	//send_byte (set_dram_addr, command);
}





