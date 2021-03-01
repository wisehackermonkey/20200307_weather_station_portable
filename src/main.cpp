#include <Arduino.h>
#include <lcd.h>
LCD lcd;
void setup() {
  Serial.begin(9600);

  lcd.setPins(8,7,/*6 is used by led*/ 5,4,3);
  lcd.init();
  Serial.println("Rssi: -12");
  lcd.print("RSSI: -12");
}

void loop() {

}