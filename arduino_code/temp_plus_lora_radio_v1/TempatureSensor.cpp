
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

bool TempatureSensor::isUpdated(){
  return updated;
}
//NOTE :DHT11 sampling rate is 1HZ.
void TempatureSensor::_update()
{
  Serial.println("Reading temperature");
  byte temperature = 0;
  byte humidity = 0;
  //note: the sensor only reads every 1 second, so dont set 
  //tempature_val untill it gets a new reading,(just return out of 
  //the function 
  if (tempsensor.read(_pin, &temperature, &humidity, NULL)) {
    updated = true;
    return ;
  }
  updated = false;
  temp =  (int)temperature;
}
bool TempatureSensor::update()
{
  _update();
  return updated;
}
