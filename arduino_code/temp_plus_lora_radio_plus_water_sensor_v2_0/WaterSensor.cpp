//water sensor level library 
// by oran collins
// 20200315

//simple water sensor reading library
//basically a wrapper for analogRead(A0) 
//where A0 is the pin used by the water sensor 
//connected to the arduino

#include "Arduino.h"
#include "WaterSensor.h"
//what im going for interms of the api
//WaterSensor watersensor(0);
// watersensor.update();

//if(watersensor.isUpdated()){
// watersensor.read();
//}

WaterSensor::WaterSensor(int pin)
{
  _pin = pin;
}
int WaterSensor::read()
{
  return level;
}

//only return true if the value has changed by +- 10 \
//from the last value last read
bool WaterSensor::isUpdated()
{
  if (((HistoryValue >= level) && ((HistoryValue - level) > 10)) || ((HistoryValue < level) && ((level - HistoryValue) > 10)))
  {
    HistoryValue = level;
    return true;
  }
  return false;
}

void WaterSensor::update()
{
  // the water level value from the sensor the analogRead
  level = analogRead(_pin);
}

//used to convert the int
char *  WaterSensor::toCharArray(){
   sprintf(printBuffer,"%d", level);
   return printBuffer;
}