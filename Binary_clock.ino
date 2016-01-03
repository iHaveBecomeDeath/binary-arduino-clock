#include <Wire.h>
#include "Time.h"
#define DS3231_I2C_ADDRESS 0x68
const int hourPins[] = {2, 3, 4, 5, 6};
const int minutePins[] = {7, 8, 9, 10, 11, 12};
const int secondPin = 13;
const bool blinkSecondPin = true;
int amountOfMinutePins = 6;
int amountOfHourPins = 5;
int previousSecond = 0;
int previousMinute = 0;
int previousHour = 0;

void setup() {
  Wire.begin();
  setSyncProvider(getRTCTime());
  setSyncInterval(100);

  int i;
  for (i = 0; i < amountOfHourPins ; i++){
    initOutputPin(hourPins[i]);
   }
  for (i = 0; i < amountOfMinutePins ; i++){
    initOutputPin(minutePins[i]);
   }
  initOutputPin(secondPin);
  updateMinutes(minute());
  updateHours(hour());
}

void loop() {
  int curSec = second();
    if ((previousSecond < curSec) ||  (previousSecond > curSec && previousSecond == 59)){
      toggleSecondPin();
      previousSecond = curSec;
      displayTime();
    } 
  int curMin = minute();
  if (previousMinute < curMin || (previousMinute > curMin && previousMinute == 59)){
    updateMinutes(curMin);
    previousMinute = curMin;
  }  
  int curHr = hour();
  if (previousHour < curHr || (previousHour > curHr && previousHour == 24)){
    updateHours(curHr);
    previousHour = curHr; 
  }
}

void updateMinutes(int mins){
  String bm = String(mins, BIN);
  if (bm.length() < amountOfMinutePins){
   for (int i = bm.length(); i < amountOfMinutePins; i++){
     bm = '0' + bm;
   } 
  }
  
  for (int j = 0; j < bm.length(); j++){
   if (bm.charAt(j) == '1'){
     pinOn(minutePins[j]);
   } else {
     pinOff(minutePins[j]);
   }
  }
}

void updateHours(int hrs){
  String bh = String(hrs, BIN);
  if (bh.length() < amountOfHourPins){
   for (int i = bh.length(); i < amountOfHourPins; i++){
     bh = '0' + bh;
   } 
  }
  
  for (int j = 0; j < bh.length(); j++){
   if (bh.charAt(j) == '1'){
     pinOn(hourPins[j]);
   } else {
     pinOff(hourPins[j]);
   }
  }  
}

void toggleSecondPin(){
  if (blinkSecondPin){
    togglePin(secondPin);
  }
}

void togglePin(int pinNumber){
   if (digitalRead(pinNumber) == HIGH){
     pinOff(pinNumber);
   } else {
     pinOn(pinNumber);
   }
}

void pinOff(int pinNumber){
    digitalWrite(pinNumber, LOW); 
}

void pinOn(int pinNumber){
    digitalWrite(pinNumber, HIGH); 
}
void initOutputPin(int pinNumber){
     pinMode(pinNumber, OUTPUT);
     pinOn(pinNumber);
     delay(120);
     pinOff(pinNumber);
}


/***********/
/* RTC stuff for rs3231 */
/* borrowed with thanks from tronixstuff.com */
/**********/

// Convert normal decimal numbers to binary coded decimal
byte decToBcd(byte val)
{
  return( (val/10*16) + (val%10) );
}
// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val)
{
  return( (val/16*10) + (val%16) );
}

void setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year)
{
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set next input to start at the seconds register
  Wire.write(decToBcd(second)); // set seconds
  Wire.write(decToBcd(minute)); // set minutes
  Wire.write(decToBcd(hour)); // set hours
  Wire.write(decToBcd(dayOfWeek)); // set day of week (1=Sunday, 7=Saturday)
  Wire.write(decToBcd(dayOfMonth)); // set date (1 to 31)
  Wire.write(decToBcd(month)); // set month
  Wire.write(decToBcd(year)); // set year (0 to 99)
  Wire.endTransmission();
}

void readDS3231time(byte *second, byte *minute, byte *hour, byte *dayOfWeek, byte *dayOfMonth, byte *month, byte *year)
{
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set DS3231 register pointer to 00h
  Wire.endTransmission();
  Wire.requestFrom(DS3231_I2C_ADDRESS, 7);
  // request seven bytes of data from DS3231 starting from register 00h
  *second = bcdToDec(Wire.read() & 0x7f);
  *minute = bcdToDec(Wire.read());
  *hour = bcdToDec(Wire.read() & 0x3f);
  *dayOfWeek = bcdToDec(Wire.read());
  *dayOfMonth = bcdToDec(Wire.read());
  *month = bcdToDec(Wire.read());
  *year = bcdToDec(Wire.read());
}
