#include "Logger.h"

String FILE_NAME = "/ANALOG00.TXT";

int SD_CARD_SELECT_PIN = 4;
int SD_CARD_WRITE_LED = 8;
//int LED_PIN = 13;


Logger logger(FILE_NAME, SD_CARD_SELECT_PIN, SD_CARD_WRITE_LED);

void setup() {
  // connect at 115200 so we can read the GPS fast enough and echo without dropping chars
  // also spit it out
  Serial.begin(115200);
  Serial.println("\r\nAnalog logger test");
}



void loop() {


  Serial.print("A0 = "); Serial.println(analogRead(0));
  logger.sd_print("A0 = "); logger.sd_println((String)analogRead(0));
 digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(250);
}
