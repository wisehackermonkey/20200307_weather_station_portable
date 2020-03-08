//#include <SimpleDHT.h>
#include "TempatureSensor.h"

//arduino
// for DHT11,
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2

//use with adafruit adalogger
// for DHT11,
//      VCC: 3.3V or 3V
//      GND: GND
//      DATA: 5

//uses pin 5 for temp sensor
int pinDHT11 = 5;


// DHT11 sampling rate is 1HZ.

TempatureSensor sensor(pinDHT11);

void setup() {
  Serial.begin(9600);
  Serial.println("=================================");
  Serial.println("Reading from temp sensor DHT11...");
  Serial.println("=================================");
  sensor.read();
}

void loop() {

  if (sensor.update()) {
    Serial.print("\nTempature, Humitity: ");
    Serial.print(sensor.read()); Serial.print(" *C, ");
  }
}
