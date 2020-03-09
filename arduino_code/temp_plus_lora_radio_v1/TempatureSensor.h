
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
    bool update();
    int read();
    bool isUpdated();
  private:
    void _update();
    int _pin;
    int temp;
    bool updated;
    SimpleDHT11 tempsensor;
};

#endif
