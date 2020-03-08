
//  TempatureSensor wrapper around the dhll library
//   Created by Oran C, 2020/03/07 
//   Released into the public domain.

#ifndef TempatureSensor_h
#define TempatureSensor_h

#include "Arduino.h"
#include "SimpleDHT_LOCAL_VERSION.h"

class TempatureSensor
{
  public:
    TempatureSensor(int pin);
    void read();
  private:
    int _pin;
//    int tempature_val;
};

#endif
