//#include <SPI.h>
//#include <SD.h>
#include "Logger.h"

// Set the pins used for sd card
int SD_CARD_SELECT_PIN = 4;
int SD_CARD_WRITE_LED = 8;
int LED_PIN = 13;


int SD_CARD_ERROR_CODE_FAILED_INIT      = 2;
int SD_CARD_ERROR_CODE_CANT_CREATE_FILE = 3;

char* FILE_NAME = "/ANALOG00.TXT";

File logfile;



// This line is not needed if you have Adafruit SAMD board package 1.6.2+
//   #define Serial SerialUSB

void setup() {
  // connect at 115200 so we can read the GPS fast enough and echo without dropping chars
  // also spit it out
  Serial.begin(115200);
  Serial.println("\r\nAnalog logger test");
  sdcardSetup();
}



void loop() {


  Serial.print("A0 = "); Serial.println(analogRead(0));
  sd_print("A0 = "); sd_println((String)analogRead(0));

  delay(100);
}


void sdcardSetup() {
  pinMode(LED_PIN, OUTPUT);


  // see if the card is present and can be initialized:
  if (!SD.begin(SD_CARD_SELECT_PIN)) {
    Serial.println("Card init. failed!");
    Serial.println("Has a sd card been inserted?");
    error(SD_CARD_ERROR_CODE_FAILED_INIT);
  }
  create_file();

  pinMode(LED_PIN, OUTPUT);
  pinMode(SD_CARD_WRITE_LED, OUTPUT);
  Serial.println("Ready!");
}

void create_file() {

  char filename[15];
  strcpy(filename, FILE_NAME);

  for (uint8_t i = 0; i < 100; i++) {
    //if file exits add another one using format <filename><number + 1>.txt
    //ex: if log01.txt exists
    //create log02.txt
    filename[7] = '0' + i / 10;
    filename[8] = '0' + i % 10;
    // create if does not exist, do not open existing, write, sync after write
    if (! SD.exists(filename)) {
      break;
    }
  }

  logfile = SD.open(filename, FILE_WRITE);
  if ( ! logfile ) {
    Serial.print("Couldnt create ");
    Serial.println(filename);
    error(SD_CARD_ERROR_CODE_CANT_CREATE_FILE);
  }
  Serial.print("Writing to ");
  Serial.println(filename);
}

// blink out an error code
void error(uint8_t errno) {
  while (1) {
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
}


void sd_print(String message) {

  //flash sd card write indicator led "SD_CARD_WRITE_LED"
  digitalWrite(SD_CARD_WRITE_LED, HIGH);
  logfile.print(message);
  digitalWrite(SD_CARD_WRITE_LED, LOW);

  //save writen data to sd card
  logfile.flush();
}

void sd_println(String message) {
  digitalWrite(SD_CARD_WRITE_LED, HIGH);
  logfile.println(message);
  digitalWrite(SD_CARD_WRITE_LED, LOW);

  logfile.flush();
}
