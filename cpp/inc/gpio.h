#include "MKL17Z4.h"


#ifndef GPIO_H
#define GPIO_H

typedef unsigned int* reg;


class gpio
{
//variables
public:
  enum Port {A , B , C , D, E};
  enum mode {Alt0 , Alt1 , Alt2 , Alt3, Alt4 , Alt5 , Alt6};
  enum dir {Input, Output};
  enum speed {Low = 0 , Medium = 1 , High=3};
  enum PP {PullUp , PullDown};

protected:
private:
  static GPIO_MemMapPtr portAdr [5];
  static PORT_MemMapPtr portAdrSet [5];
  unsigned char prt;

//functions
public:
  gpio();
  gpio(Port p );
  gpio(uint8_t p );
  void setOutPin (uint8_t pin, mode m = Alt1, dir d = Output);	
  void setOutPin (uint8_t pin, uint8_t m);
  void setPin (uint8_t pin);
  void clearPin (uint8_t pin);	
  void setValPort (uint32_t value);	
  void clearValPort (uint32_t value);	
  void setOutPort (uint32_t value, mode m = Alt1);
  void setPort (uint8_t p);
  void ChangePinState (uint8_t pin);
  void SetPinState (uint8_t pin , uint8_t state);
  void PuPd (uint8_t pin , PP p);
  bool PinState (uint8_t pin);
}; //gpio


#endif
