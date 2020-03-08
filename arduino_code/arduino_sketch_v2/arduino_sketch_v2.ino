#include <SimpleDHT.h>
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

void setup() {
  Serial.begin(9600);
  Serial.println("=================================");
  Serial.println("Sample DHT11...");
}

void loop() {
  // start working...


//  // read without samples.
//  byte temperature = 0;
//  byte humidity = 0;
//  if (dht11.read(pinDHT11, &temperature, &humidity, NULL)) {
//    Serial.print("");
//    return;
//  }
s
  Serial.print("\nTempature, Humitity: ");
  Serial.print(read_tempature()); Serial.print(" *C, ");
//  Serial.print((int)humidity); Serial.print(" %");

  // DHT11 sampling rate is 1HZ.
  delay(1000);
}

int read_tempature() {
  byte temperature = 0;
  byte humidity = 0;

  if (dht11.read(pinDHT11, &temperature, &humidity, NULL)) {
    Serial.print("Data Not read");
    return -9000;
  }

 return (int)temperature;
}
