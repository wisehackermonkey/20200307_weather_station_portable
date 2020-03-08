/*
  SD card writing  wrapper around the SD.h library
  to write logs to and sd card
  Created by Oran C, 2020/03/07
  Released into the public domain.
*/

#include "Arduino.h"
#include "Logger.h"




Logger::Logger(String filename, int _SD_CARD_SELECT_PIN, int _SD_CARD_WRITE_LED)
{
  SD_CARD_SELECT_PIN = _SD_CARD_SELECT_PIN;
  SD_CARD_WRITE_LED  = _SD_CARD_WRITE_LED;

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN,LOW);
//
//
//  // see if the card is present and can be initialized:
  if (!SD.begin(_SD_CARD_SELECT_PIN)) {
    Serial.println("Card init. failed!");
    Serial.println("Has a sd card been inserted?");
//    error(SD_CARD_ERROR_CODE_FAILED_INIT);
  }
//
//
//  create_file(filename);
//
//  pinMode(LED_PIN, OUTPUT);
  pinMode(_SD_CARD_WRITE_LED, OUTPUT);
//  Serial.println("Ready!");
}


void Logger::create_file(String _filename) {
  //convert string to c-string
  //credit
  //http://www.cplusplus.com/reference/string/string/c_str/
  char * filename_cstring = new char [_filename.length() + 1];
  strcpy (filename_cstring, _filename.c_str());

  char filename[15];
  strcpy(filename, filename_cstring);

//  delete[] filename_cstring;
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
//    error(SD_CARD_ERROR_CODE_CANT_CREATE_FILE);
  }
  Serial.print("Writing to ");
  Serial.println(filename);


}


// blink out an error code
void Logger::error(uint8_t errno) {
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


void Logger::sd_print(String message) {

  //flash sd card write indicator led "SD_CARD_WRITE_LED"
  digitalWrite(SD_CARD_WRITE_LED, HIGH);
  logfile.print(message);
  digitalWrite(SD_CARD_WRITE_LED, LOW);

  //save writen data to sd card
  logfile.flush();
}

void Logger::sd_println(String message) {
  digitalWrite(SD_CARD_WRITE_LED, HIGH);
  logfile.println(message);
  digitalWrite(SD_CARD_WRITE_LED, LOW);

  logfile.flush();
}
