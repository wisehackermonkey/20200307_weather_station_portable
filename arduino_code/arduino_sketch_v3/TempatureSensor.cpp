
#include "Arduino.h"
#include "TempatureSensor.h"

TempatureSensor::TempatureSensor(int pin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
}

void TempatureSensor::read()
{
  digitalWrite(_pin, HIGH);
  delay(250);
  digitalWrite(_pin, LOW);
  delay(250);  
  Serial.println("works");
}