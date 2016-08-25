#include "MKL05Z4.h"
#include "i2c.h"

i2c::i2c()
:pin (gpio::B)
{
	SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;
	pin.setOutPort ((1 << SCL)|(1 << SDA), gpio::Alt2);

	I2C0->F = 0;
	I2C0->F = I2C_F_ICR(0x1F);
	I2C0->C1 |= I2C_C1_IICEN_MASK;
	//I2C0->C1 |= I2C_C1_IICEN_MASK;
}

bool i2c::start ()
{
	uint16_t timeout;
	I2C0->C1 |= I2C_C1_TX_MASK;
	I2C0->C1 |= I2C_C1_MST_MASK;
	timeout=0;
	while ((!(I2C0->S&I2C_S_BUSY_MASK)) && (timeout<10000))
	    timeout++;
	if (timeout >= 10000) return false;
	else return true;
}
/*
void i2c::start ()
{
	I2C0->C1 |= I2C_C1_TX_MASK;
	I2C0->C1 |= I2C_C1_MST_MASK;

	while (!(I2C0->S&I2C_S_BUSY_MASK));
}
*/
void i2c::restart ()
{
	I2C0->C1 |= I2C_C1_RSTA_MASK;
}

bool i2c::stop ()
{
	uint16_t timeout;
	I2C0->C1 &= ~ I2C_C1_MST_MASK;
	timeout = 0;
	while ( (I2C0->S&I2C_S_BUSY_MASK) && (timeout<10000))
	timeout++;
	if (timeout >= 10000) return false;
	else return true;
	//проба git
}

/*
void i2c::stop ()
{
	I2C0->C1 &= ~ I2C_C1_MST_MASK;
	I2C0->C1 &= ~ I2C_C1_TX_MASK;
	while (I2C0->S&I2C_S_BUSY_MASK);
}
*/

void i2c::wait ()
{
	//ожидание установки флага прерывания
	while ((I2C0->S&I2C_S_IICIF_MASK)==0);
	//сброс флага прерывания
	I2C0->S |= I2C_S_IICIF_MASK;
}

void i2c::write_byte (uint8_t data)
{
	I2C0->D = data;
}

uint8_t i2c::read_byte ()
{
	return I2C0->D;
}

void i2c::give_nack ()
{
	I2C0->C1 |= I2C_C1_TXAK_MASK;
}

void i2c::give_ack ()
{
	I2C0->C1 &= ~ I2C_C1_TXAK_MASK;
}

bool i2c::get_ack ()
{
	if ((I2C0->S&I2C_S_RXAK_MASK)==0) return true;
	else return false;
}


