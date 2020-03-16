
#include "Arduino.h"
#include "TempatureSensor.h"
#include "SimpleDHT_LOCAL_VERSION.h"

TempatureSensor::TempatureSensor(int pin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
  //instancate temperature sensor, and set to local variable
  SimpleDHT11 dht11;
  tempsensor =  dht11;

}
int TempatureSensor::read(){
  return temp;
}

bool TempatureSensor::onChange(){
  if( ((prevTemp >= temp)   && ((prevTemp - temp) > 1))  || ( (prevTemp < temp) && (temp - prevTemp) > 1 )  ){
      prevTemp = temp;
      return true;
  }
  return false;
}

//NOTE :DHT11 sampling rate is 1HZ.
void TempatureSensor::_update()
{
  //Reading temperature
  // Serial.print(".");
  byte temperature = 0;
  byte humidity = 0;
  //note: the sensor only reads every 1 second, so dont set 
  //tempature_val untill it gets a new reading,(just return out of 
  //the function 
  if (tempsensor.read(_pin, &temperature, &humidity, NULL)) {
    // updated = true;
    return ;
  }
  // updated = false;
  temp =  (int)temperature;
}

//wrapper around reading the sensor & if the sensor value changed
bool TempatureSensor::update()
{
  _update();
  return onChange();
}
