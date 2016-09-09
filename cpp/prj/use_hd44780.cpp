#include "MKL05Z4.h"                    // Device header
#include "hd44780.h"


uint8_t array [10]= {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

uint8_t number[5];

void numtostr (uint16_t number, uint8_t * arr);

int main ()
{
	Hd44780 display;
	display.set_position(0,0);
	display.send_string ((uint8_t*)"Hello!!!");
	display.set_position(1,0);
	numtostr (6543, number);
	display.send_string (number);
	while (1)
	{
		
	}
}

void numtostr (uint16_t number, uint8_t * arr)
{
	char tousand=0, hundr=0, dec=0, ones = 0;
	uint16_t temp = number;

	for (hundr=0;temp>=1000;++tousand)temp -=1000;

	for (hundr=0;temp>=100;++hundr)temp -=100;

	for (dec=0;temp>=10;++dec)temp -=10;

	for (ones=0;temp>=1;++ones)temp--;
		arr [0] = array [tousand];
		arr [1] = array [hundr];
		arr [2] = array [dec];
		arr [3] = array [ones];
}

