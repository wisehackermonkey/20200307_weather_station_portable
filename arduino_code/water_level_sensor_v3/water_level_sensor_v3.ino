//water sensor level library example
// by oran collins
// 20200315
// mesure the level of water from the elegoo water sensor

//simple water sensor reading library
//basically a wrapper for analogRead(A2) 
//where A0 is the pin used by the water sensor 
//connected to the arduino
#include "WaterSensor.h"

//pinout
//sensor | arduino uno/nano
// S  - A2
//(+) - v5
//(-) - GND

int WATER_SENSOR_PIN = 2;
WaterSensor watersensor = WaterSensor(WATER_SENSOR_PIN);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  watersensor.update();

  //if waterlevel is false that means a new value has not been read
  if (watersensor.isUpdated())
  {

    // sprintf(printBuffer, "ADC level is %d\n", watersensor.read());
    Serial.println(watersensor.read());
    //if you need a character array version of the number
    Serial.println(watersensor.toCharArray());
  }
}
