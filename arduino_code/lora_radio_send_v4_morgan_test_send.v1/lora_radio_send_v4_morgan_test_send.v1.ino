// LoRa 9x_TX
// -*- mode: C++ -*-
// Example sketch showing how to create a simple messaging client (transmitter)
// with the RH_RF95 class. RH_RF95 class does not provide for addressing or
// reliability, so you should only use RH_RF95 if you do not need the higher
// level messaging abilities.
// It is designed to work with the other example LoRa9x_RX

#include <SPI.h>
#include <RH_RF95.h>

// used in other board which has the actual weather sensors on it
// #define RFM95_CS 4
// #define RFM95_INT 3
// #define RFM95_RST 2
// -----------------------------------------

// the board that is attached to the computer
#define RFM95_CS 10
#define RFM95_RST 9
#define RFM95_INT 2

//OLD pinout
//----------------------------
// 13 - SCK
// 12 - MISO
// 11 - MOSI
// 10 - G0
// 09 - CS
// 06 - RST
// 05 - USED by humidiy sensor
//----------------------------

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

// Change to 915.0 or other frequency, must match RX's freq!
#define RF95_FREQ 915.0

// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);

int LED_PIN = 6;

#define PACKET_LENGTH 20
void setup()
{

    pinMode(LED_PIN, OUTPUT);

    blink_code(4);

    // setup pins for radio
    pinMode(RFM95_RST, OUTPUT);
    digitalWrite(RFM95_RST, HIGH);

    //  while (!Serial);
    Serial.begin(9600);
    delay(100);

    Serial.println("Arduino LoRa TX and listen morgan Test!");

    // manual reset
    digitalWrite(RFM95_RST, LOW);
    delay(10);
    digitalWrite(RFM95_RST, HIGH);
    delay(10);

    while (!rf95.init())
    {
        Serial.println("LoRa radio init failed");
        while (1)
            ;
    }
    Serial.println("LoRa radio init OK!");

    // Defaults after init are 915.0MHz, modulation GFSK_Rb250Fd250, +13dbM
    if (!rf95.setFrequency(RF95_FREQ))
    {
        Serial.println("setFrequency failed");
        while (1)
            ;
    }
    Serial.print("Set Freq to: ");
    Serial.println(RF95_FREQ);

    //--------SETing up configuration settings to match morgans experimental lora network

    // Defaults after init are 915.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on

    // The default transmitter power is 13dBm, using PA_BOOST.
    // If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then
    // you can set transmitter powers from 5 to 23 dBm:
    // rf95.setTxPower(23, false);
    rf95.setTxPower(5, false); //im doing this so is much more powerfull than a weak 23dBm

    //--------this settings im not totally sure what they are for but they are required to connect to morgans network
    // https://www.airspayce.com/mikem/arduino/RadioHead/classRH__RF95.html#abea770963212a64b35169f0f0c35c14d
    // void 	setSpreadingFactor (uint8_t sf)
    rf95.setSpreadingFactor(11);

    // [(No Title)](https://www.airspayce.com/mikem/arduino/RadioHead/classRH__RF95.html#a02ba623bba31f200e50e46686ec61176)
    // void 	setSignalBandwidth (long sbw)
    rf95.setSignalBandwidth(7);

    // [(No Title)](https://www.airspayce.com/mikem/arduino/RadioHead/classRH__RF95.html#ad7edba1cc8e33512c0b1721758bd0077)
    //void 	setCodingRate4 (uint8_t denominator)
    rf95.setCodingRate4(5);
}

int8_t packetnum = 0; // packet counter, we increment per xmission

void loop()
{
    //  Serial.println("Sending to rf95_server");
    // Send a message to rf95_server
    packetnum+=1;
    char radiopacket[PACKET_LENGTH] = {packetnum, 0, 0, 0, 'x', 'x', 'x', 0, 6, 'o', 'r', 'a', 'n', 'i', 's', 'h', 'e', 'r', 'e', ' '};
    /*
   {173, packet id 0-255 used to identify the packet and allow for retransmition
    0, unused can be anything between 0-255
    0,
    0,
    255,
    255,
    255,
    0, this means the packet is in TEXT mode the following number is the length of the message which can be 0-255 in length 
    4, length of message 
    'o','r','a','n' char characters can be length between 0-255 chars
    };

  */

    //increments the packet id (index 0), NOTE: , 10); means do it in base 10
    // itoa(packetnum++, radiopacket+5, 10);
    // radiopacket[0] = radiopacket[0] + 1;
    blink_code(2);
    Serial.print("Sending: ");
    

    for (int i = 0; i < PACKET_LENGTH; i += 1)
    {
        // if (i < 7)
        // {
        //     // convert the fist 7 headers of the packet to numbers instead
        //     // of unprintable char's
        //     Serial.print(radiopacket[i]);
        // }
        // else
        // {
            Serial.print((char)radiopacket[i]);
        // }
        Serial.print(" | ");
    }
    Serial.println(",");

    Serial.println((String)radiopacket);
    delay(10);

    //------SEND PACKET --------
    rf95.send((uint8_t *)radiopacket, PACKET_LENGTH);
    //--------------------------
    delay(10);

    //-------receive packet response------
    rf95.waitPacketSent();
    //------------------------------------
    // Now wait for a reply
    //put content
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
        delay(1000);

    if (rf95.waitAvailableTimeout(3000))
    {
        // Should be a message for us now
        uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
        uint8_t len = sizeof(buf);

        if (rf95.recv(buf, &len))
        {
            blink_code(2);
            //looks like
            //"Recieved (-37 db): <message here>"
            Serial.print("Recieved : ");
            // Serial.print(rf95.lastRssi(), DEC);
            // Serial.print("db): ");
            Serial.println((char *)buf);
            blink_code(2);
        }
        else
        {
            Serial.println("Receive failed");
        }
    }else{
        Serial.println("Radio not availble");
        blink_code(3);
    }
    // delay(2000);
}

// blink out an error code
void blink_code(uint8_t errno)
{

    uint8_t i;
    for (i = 0; i < errno; i++)
    {
        digitalWrite(LED_PIN, HIGH);
        delay(100);
        digitalWrite(LED_PIN, LOW);
        delay(100);
    }
    for (i = errno; i < 10; i++)
    {
        delay(200);
    }
}
