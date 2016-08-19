#include "MKL05Z4.h"                 // Device header
#include "gpio.h"


/*
 SPI0
 C: CS-4, SCK-5, MOSI-6,MISO-7
 D: CS-0, SCK-1, MOSI-2,MISO-3
 E: CS-16, SCK-17, MOSI-18,MISO-19


 SPI1
 D:CS-4, SCK-5, MOSI-6,MISO-7
*/

#ifndef I2C_H
#define I2C_H


class i2c
{
//variables
public:


	
  enum pin_def { SCL=3, SDA};
  uint8_t port_;
  uint8_t size_;
  uint8_t n_spi;
  uint8_t p_CS;

private:
  gpio pin;



//functions
public:
  //constructor for SPI1
  i2c();
  void start ();
  void transmit_adress(uint8_t add);

private:
};



#endif

