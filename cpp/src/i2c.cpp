#include "i2c.h"

i2c::i2c()
:pin (gpio::B)
{
	pin.setOutPort ((1 << SCL)|(1 << SDA), gpio::Alt2);

}

void i2c::start ()
{

}
