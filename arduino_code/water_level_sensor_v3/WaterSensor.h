//water sensor level library 
// by oran collins
// 20200315

//simple water sensor reading library
//basically a wrapper for analogRead(A0) 
//where A0 is the analog pin zero used by the water sensor 
//connected to the arduino

// Created by Oran C, 2020/03/07 
// Released into the public domain.

#ifndef WaterSensor_h
#define WaterSensor_h

#include "Arduino.h"

class WaterSensor
{
  public:
    WaterSensor(int pin);
    void update();
    int read();
    bool isUpdated();
    char * toCharArray();
  private:
    void _update();
    int _pin;
    //the actual value used to store the water level
    int level;
    //implmentation variables
    int HistoryValue;
    bool updated;
    char printBuffer[4] = "    ";

};

#endif
