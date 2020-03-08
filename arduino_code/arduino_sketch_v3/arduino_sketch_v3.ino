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
int pinDHT11 = 5;
SimpleDHT11 dht11;

int tempature_val = -9000;
TempatureSensor sensor(pinDHT11);//uses pin 5

void setup() {
  Serial.begin(9600);
  Serial.println("=================================");
  Serial.println("Reading from temp sensor DHT11...");
  Serial.println("=================================");

}

void loop() {


  read_tempature();

  if (tempature_val != NULL) {
    Serial.print("\nTempature, Humitity: ");
    Serial.print(tempature_val); Serial.print(" *C, ");

  }
  // DHT11 sampling rate is 1HZ.
  //  delay(1000);
}

void  read_tempature() {
  byte temperature = 0;
  byte humidity = 0;
  //note: the sensor only reads every 1 second, so dont set 
  //tempature_val untill it gets a new reading,(just return out of 
  //the function 
  if (dht11.read(pinDHT11, &temperature, &humidity, NULL)) {
    return ;
  }
  tempature_val =  (int)temperature;
}
