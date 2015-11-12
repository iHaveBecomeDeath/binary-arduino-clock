#include "TimerOne.h"
int ticks = 0;
int minutes = 0;
int hours = 0;
const int hourPins[] = {2, 3, 4, 5};
const int minutePins[] = {7, 8, 9, 10, 11};
const int secondPin = 12;
const long int lengthOfSecond = 5000; // 1 000 000 is "normal"
const bool blinkSecondPin = false;
int amountOfMinutePins = 0;
int amountOfHourPins = 0;

void setup() {
  amountOfHourPins = sizeof(hourPins)/sizeof(int);
  amountOfMinutePins = sizeof(minutePins)/sizeof(int);
  int i;
  for (i = 0; i < amountOfHourPins ; i++){
    initOutputPin(hourPins[i]);
  }
  for (i = 0; i < amountOfMinutePins ; i++){
    initOutputPin(minutePins[i]);
  }
  initOutputPin(secondPin);
  Timer1.initialize(lengthOfSecond);
  Timer1.attachInterrupt(clockTick);
}

void loop() {
  
}

void clockTick(){
  if (blinkSecondPin){
    toggleSecondPin();
  }
  if (++ticks >= 60){
    ticks = 0; 
    if (++minutes >= 60) {
      minutes = 0;
      if (++hours >= 24) {
       hours = 0;
      }
     }
   }
   updateClockDisplay();
}

void updateClockDisplay(){
  String binMinutes = getTimeArray(minutes, amountOfMinutePins);
  String binHours = String(hours, BIN);
  int binLength;
  
  //TODO: general function for looping these arrays
  for (int i = 0; i < amountOfMinutePins; i++){
    if (binMinutes[i] == '1'){
      pinOn(minutePins[i]);
    } else {
      pinOff(minutePins[i]); 
    }
  }
  binLength = binHours.length();
  for (int i = 0; i < amountOfHourPins; i++){
    if (binLength < amountOfHourPins  && binHours[amountOfHourPins-i-1] == '1'){
      pinOn(hourPins[i]);
    } else {
      pinOff(hourPins[i]); 
    }
  }
}

String getTimeArray(int timespan, int numberOfObjects){
  String temp = String(timespan, BIN);
  char retArr[numberOfObjects+1];
  int binLength = temp.length();
  
  for (int i = 0; i < numberOfObjects; i++){
    if (binLength <= i) {
      retArr[i] = temp[i];
    } else {  
      retArr[i] = '0';
    }
  }
  
  return String(retArr);
}

void toggleSecondPin(){
  togglePin(secondPin);
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
     delay(130);
     pinOff(pinNumber);
}
