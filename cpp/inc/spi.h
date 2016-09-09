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

#ifndef SPI_H
#define SPI_H

class spi;

typedef uint16_t(spi::*PotMemFn)() ;
typedef uint16_t(spi::*ptr_ex)(uint16_t) ;

typedef void(spi::*PotMemF)(uint16_t) ;

class spi
{
//variables
public:
  enum Division {div2 , div4 , div8 , div16 , div32 , div64 , div128 , div256, div512};
  enum Role {slave , master};
  enum Mode { software, hardware};
  enum Cpol {neg, pos};
  enum Cpha {first, second};
  static uint8_t pins_d[4];
  enum PORT {A,B};

	
  enum pin_def {CS, SCK , MOSI, MISO};
  uint8_t port_;
  uint8_t size_;
  uint8_t n_spi;
  uint8_t p_CS;

private:
  Gpio pin_A;
  Gpio pin_B;
  Gpio pin_CS;



//functions
public:
  //constructor for SPI1
  spi(Division d_, Cpol cpol_=neg, Cpha cpha_=first, Mode m = hardware, Role r=master);

  void set_CS (PORT p, uint8_t pin);
  void transmit (uint8_t data);
  uint8_t receive ();
  uint8_t exchange (uint8_t data);

  void assert_CS();

  void disassert_CS();

  void put_data (uint8_t data);
  uint8_t get_data ();
  bool flag_sptef ();
  bool flag_sprf ();

private:
};



#endif

