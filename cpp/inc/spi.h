#include "MKL17Z4.h"                 // Device header
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
  enum SPI_N {SPI_0 = 22, SPI_1};
  enum Role {slave , master};
  enum Cpol {neg, pos};
  enum Cpha {first, second};
  static uint8_t pins_d[3][4];
  enum Size {bit8, bit16};
  enum PORT {C=2,D,E};

	
  enum pin_def {CS, SCK , MOSI, MISO};
  uint8_t port_;
  uint8_t size_;
  uint8_t n_spi;
  uint8_t pins_;
private:
  gpio pin;
  static PotMemFn ptr_receive[2];
  static PotMemF ptr_transmite[2];
  static ptr_ex ptr_exchange[2];
  static SPI_MemMapPtr spiAdr [2];

//functions
public:
  //constructor for SPI1
  spi(Division d_, Cpol cpol_=neg, Cpha cpha_=first, Size s=bit8, Role r=master);

  //constructor for SPI0
  spi(PORT p, Division d_, Cpol cpol_=neg, Cpha cpha_=first, Size s=bit8, Role r=master );

  void transmit_8 (uint16_t data);
  void transmit_16 (uint16_t data);
  void transmit (uint16_t data);
  uint16_t receive_8 ();
  uint16_t receive_16 ();
  uint16_t receive ();

  uint16_t exchange_8 (uint16_t data);
  uint16_t exchange_16 (uint16_t data);
  uint16_t exchange (uint16_t data);

  void put_data_dh (uint8_t data);
  void put_data_dl (uint8_t data);
  uint8_t get_data_dh ();
  uint8_t get_data_dl ();
  bool flag_sptef ();
  bool flag_sprf ();

private:
};



#endif

