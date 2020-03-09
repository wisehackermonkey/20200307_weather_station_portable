//Temperature and radio sending sketch
//by oran c
//20200308

//this sketch goes on the sending arduino (nano in my case),
//which has attached a DHT11 temperature&humidity sensor, and a lora RFM9x radio 
//module from adafruit.com
//
//This sketch read the DHT11 temperature module and sends the value
//over the lora RFM9x radio as two numbers repersenting temperature in degrees Celcius 


//original sketch notes
// LoRa 9x_TX
// -*- mode: C++ -*-
// Example sketch showing how to create a simple messaging client (transmitter)
// with the RH_RF95 class. RH_RF95 class does not provide for addressing or
// reliability, so you should only use RH_RF95 if you do not need the higher
// level messaging abilities.
// It is designed to work with the other example LoRa9x_RX



#include <SPI.h>
#include <RH_RF95.h>
#include "TempatureSensor.h"

#define RFM95_CS 4
#define RFM95_INT 3
#define RFM95_RST 2

//aarduino pinout for the DHT11,
//      VCC: 5V or 3V
//      GND: GND
//      DATA: pin 5

//Current pinout
//----------------------------
// 13 - SCK (RFM9x)
// 12 - MISO (RFM9x)
// 11 - MOSI (RFM9x)
// 06 - LED (+) indecator (used for flashing codes)
// 05 - USED by humidiy sensor
// 04 - CS (RFM9x)
// 03 - G0 (RFM95_INT is a interrupt pin) (RFM9x)
// 02 - RST (RFM9x)
//----------------------------

// Change to 434.0 or other frequency, must match RX's freq!
#define RF95_FREQ 915.0

// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);

int LED_PIN = 6;
int pinDHT11 = 5;//used with the temperature sensor



//notes the DHT11 temperature sensor only reads every 1 second
//sampling rate is 1HZ.
TempatureSensor sensor(pinDHT11);
void setup()
{

  pinMode(LED_PIN, OUTPUT);
  blink_code(4);
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);

  Serial.begin(9600);
  delay(100);

  Serial.println("Temperature Sensor Radio: SEND");
  Serial.println("Starting up Lora RFM9x radio");

  // manual reset
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);

  while (!rf95.init()) {
    Serial.println("LoRa radio init failed");
    while (1);
  }
  Serial.println("LoRa radio init OK!");

  // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM
  if (!rf95.setFrequency(RF95_FREQ)) {
    Serial.println("setFrequency failed");
    while (1);
  }
  Serial.print("Set Freq to: "); Serial.println(RF95_FREQ);

  // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on

  // The default transmitter power is 13dBm, using PA_BOOST.
  // If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then
  // you can set transmitter powers from 5 to 23 dBm:
  rf95.setTxPower(23, false);
}

int16_t packetnum = 99;  // packet counter, we increment per xmission

void loop()
{
  if (sensor.update()) {
    int temp = sensor.read(); 

    const int PACKET_LENGTH = 20;
    char radiopacket[PACKET_LENGTH] = "70  100            ";
    itoa(temp, radiopacket, 10);

    blink_code(2);
    Serial.println();
    Serial.print("Sending: "); Serial.println(radiopacket);
    delay(10);
    rf95.send((uint8_t *)radiopacket, 20);

    delay(10);
    rf95.waitPacketSent();
    delay(2000);
  }
}


// blink out an error code
void blink_code(uint8_t errno) {

  uint8_t i;
  for (i = 0; i < errno; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
  }
  for (i = errno; i < 10; i++) {
    delay(200);
  }
}
