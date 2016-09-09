#include "MKL05Z4.h"                    // Device header
#include "hd44780.h"


using namespace std;

int main ()
{
	Hd44780 display;
	display.send_string ((uint8_t *)"Hello!!!");
	display.set_position(0,0);

	while (1)
	{

		
	}
}
