#include "Time.h"
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
 // Serial.begin(9600);
  int i;
  for (i = 0; i < amountOfHourPins ; i++){
    initOutputPin(hourPins[i]);
   }
  for (i = 0; i < amountOfMinutePins ; i++){
    initOutputPin(minutePins[i]);
   }
  initOutputPin(secondPin);
  setTime(1, 22, 55, 1, 1, 1999); // For testing. Should probably initialize to 0,0,0. Or get from NTP or what not.
  updateMinutes(minute());
  updateHours(hour());
}

void loop() {
  int curSec = second();
    if ((previousSecond < curSec) ||  (previousSecond > curSec && previousSecond == 59)){
      toggleSecondPin();
      previousSecond = curSec;
      //updateMinutes(curSec); // Only for testing, minutes are slow :)
    } 
  int curMin = minute();
  if (previousMinute < curMin || (previousMinute > curMin && previousMinute == 59)){
    updateMinutes(curMin);
    //updateHours(curMin); // Only for testing, hours are slow :)
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
  //Serial.println("orig bm: " + bm + ", mins: " + mins);
  if (bm.length() < amountOfMinutePins){
   for (int i = bm.length(); i < amountOfMinutePins; i++){
     bm = '0' + bm;
   } 
  }
  
  //Serial.println("bm: " + bm);
  
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
