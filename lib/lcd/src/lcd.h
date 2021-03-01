// abstraction library to using the Nokia 5110 LCD display
// what i'm using it for is to display signal strength of th antenna and
// for displaying data being sent, also for debugging in the field
// by oran collins
// github.com/wisehackermonkey
// oranbusiness@gmail.com
// 20210228

#ifndef lcd_h
#define lcd_h
#include "Arduino.h"
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

/*
Example useage

how to display text

LCD lcd();

//setup()
lcd.init();

*/
// ![](https://lastminuteengineers.com/wp-content/uploads/arduino/Wiring-Connecting-Nokia-5110-LCD-module-with-Arduino-UNO.png)
class LCD
{
private:
    String current_text = "";
    // set default nokia 5110 LCD pinout
    // fallowing this example
    int _CLK_PIN = 7;
    int _DIN_PIN = 6;
    int _DC_PIN = 5;
    int _CE_PIN = 4;
    int _RST_PIN = 3;
    Adafruit_PCD8544 &display;

public:
    LCD();
    void init();
    void setPins(int, int, int, int, int);
    void show();
    void print(String);
};

// Declare LCD object for software SPI
// Adafruit_PCD8544(CLK,DIN,D/C,CE,RST);
LCD::LCD() {}

// setup pins and other configuation to use the nokia 5110 lcd
/*
Example useage
lcd.init();
*/
void LCD::init()
{
    display = Adafruit_PCD8544(_CLK_PIN,
                               _DIN_PIN,
                               _DC_PIN,
                               _CE_PIN,
                               _RST_PIN);

    //Initialize Display
    display.begin();

    // you can change the contrast around to adapt the display for the best viewing!
    display.setContrast(57);

    // Clear the buffer.
    display.clearDisplay();

    // setup styling
    //see photo of example 
    // ![](https://lastminuteengineers.com/wp-content/uploads/arduino/Displaying-Text-On-Nokia-5110-Display-Module.jpg)
    // Display Text
    display.setTextSize(1);
    display.setTextColor(BLACK);
    display.setCursor(0, 0);
}

// sends data to display 
/*
Example:
lcd.init();
lcd.print("hello world!");
*/

void LCD::print(String message){
    display.setCursor(0,0);
    display.clearDisplay(); //clean the lcd so i can display new data
    display.print(message);//write text to lcd
    display.display();//send display buffer bytes to lcd
}

// allows for setting arbitrary pinouts incase your pins 7-3 are taken in your project
/*
Example useage
NOTE: IMPORTANT! setPins is called befor init!
lcd.setPins(12,11,10,9,8);
lcd.init();
*/
void LCD::setPins(int CLK_PIN = 7,
                  int DIN_PIN = 6,
                  int DC_PIN = 5,
                  int CE_PIN = 4,
                  int RST_PIN = 3)
{
    _CLK_PIN = CLK_PIN;
    _DIN_PIN = DIN_PIN;
    _DC_PIN = DC_PIN;
    _CE_PIN = CE_PIN;
    _RST_PIN = RST_PIN;
}

#endif