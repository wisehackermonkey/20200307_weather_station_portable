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

#define RFM95_CS 9
#define RFM95_RST 6
#define RFM95_INT 10

//Current pinout
//----------------------------
//SCK - SCK
//MISO - MISO
//MOSI - MOSI
// 12 - +LED indecator
// 10 - G0 (INT a interrupt pin)
// 09 - CS
// 06 - RST
// 05 - USED by humidiy sensor
//----------------------------

// Change to 434.0 or other frequency, must match RX's freq!
#define RF95_FREQ 915.0

// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);

int LED_PIN = 6;
int pinDHT11 = 5;//used with the temperature sensor


char * set_packet_message(String message, int packet_length) {
  if (message.length() > packet_length) {
    blink_code(6);
    Serial.print("Error: message is larger than packet size. must be under : in size");
    Serial.print(packet_length);
    Serial.print("in size");
    return "error";
  } else {
    const int PACKET_LENGTH = packet_length;
    char radiopacket[PACKET_LENGTH] = "70  100            ";
    //    itoa(packetnum++, radiopacket + 4, 10);
    //  Serial.print("Sending ");
    String message = "70";
    for (int i = 0; i < message.length() - 1; i++) {
      radiopacket[i] = message[i];
    }
    radiopacket[message.length()] = '\0';
    return radiopacket;
  }
}

// DHT11 sampling rate is 1HZ.

TempatureSensor sensor(pinDHT11);
void setup()
{

  pinMode(LED_PIN, OUTPUT);
  blink_code(4);
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);

  //  while (!Serial);
  Serial.begin(9600);
  delay(100);

  Serial.println("Arduino LoRa TX Test!");

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
    //  Serial.print("Sending ");
//    String message = "70";
//    for (int i = 0; i <= message.length() - 1; i++) {
//      radiopacket[i] = message[i];
//    }

    blink_code(2);
    Serial.print("Sending: "); Serial.println(radiopacket);
    delay(10);
    rf95.send((uint8_t *)radiopacket, 20);

    //  Serial.print(".");
    delay(10);
    rf95.waitPacketSent();
    // Now wait for a reply
    //  uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    //  uint8_t len = sizeof(buf);

    //  Serial.println("."); delay(10);

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
