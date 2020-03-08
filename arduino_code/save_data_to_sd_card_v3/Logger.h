/*
  SD card writing  wrapper around the SD.h library
  to write logs to and sd card
  Created by Oran C, 2020/03/07 
  Released into the public domain.
*/
#ifndef Logger_h
#define Logger_h

#include "Arduino.h"

 #include <SPI.h>
 #include <SD.h>

class Logger
{
  public:
    Logger(String filename, int SD_CARD_SELECT_PIN, int SD_CARD_WRITE_LED);
    void sd_print(String message);
    void sd_println(String message); 
  private:
    File logfile;
    void create_file(String FILE_NAME);
    void error(uint8_t errno);
    int LED_PIN = 13;
    uint8_t i;
    int SD_CARD_SELECT_PIN;
    int SD_CARD_WRITE_LED;
    
    int SD_CARD_ERROR_CODE_FAILED_INIT      = 2;
    int SD_CARD_ERROR_CODE_CANT_CREATE_FILE = 3;
};

#endif
