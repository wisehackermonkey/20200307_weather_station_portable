//www.elegoo.com
//2016.12.9
//modified by oran collins
// 20200315
//mesure the level of water from the elegoo water sensor

//pinout
//sensor | arduino uno/nano
// S  - A0
//(+) - v5
//(-) - GND

int adc_id = 0;
int HistoryValue = 0;
char printBuffer[128];

void setup()
{
  Serial.begin(9600);
}

void loop()
{
    // int value = analogRead(adc_id); // get adc value

    //only reports change water level change
    //when a change larger/smaller than 10 units has occured
    // if(((HistoryValue>=value) && ((HistoryValue - value) > 10)) || ((HistoryValue<value) && ((value - HistoryValue) > 10)))
    // {
    //   sprintf(printBuffer,"ADC%d level is %d\n",adc_id, value);
    //   Serial.print(printBuffer);
    //   HistoryValue = value;
    // }
    int waterLevel = readWaterSensor(HistoryValue);
    
    //if waterlevel is not equal to -1, aka a new value has not been read
    if( waterLevel >=0 ){

      sprintf(printBuffer,"ADC level is %d\n", waterLevel);
      Serial.print(printBuffer);    

    }
}

int readWaterSensor(int HistoryValue){
  int value = analogRead(adc_id); // get adc value

    //only reports change water level change
    //when a change larger/smaller than 10 units has occured
    if(((HistoryValue>=value) && ((HistoryValue - value) > 10)) || ((HistoryValue<value) && ((value - HistoryValue) > 10)))
    {
      // sprintf(printBuffer,"ADC%d level is %d\n",adc_id, value);
      // Serial.print(printBuffer);
      HistoryValue = value;
      return value;
    }

    return -1;
}