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
   updateClockDisplay();
  if (++ticks >= 60){
    ticks = 0; 
    if (++minutes >= 60) {
      minutes = 0;
      if (++hours >= 24) {
       hours = 0;
      }
     }
   }
}

void updateClockDisplay(){
  String binMinutes = String(minutes, BIN);
  String binHours = String(hours, BIN);
  int binLength;
  
  //TODO: general function for looping these arrays
  binLength = binMinutes.length();
  for (int i = 0; i < amountOfMinutePins; i++){
    if (binLength <= amountOfMinutePins && binMinutes[i] == '1'){
      pinOn(minutePins[i]);
    } else {
      pinOff(minutePins[i]); 
    }
  }
  binLength = binHours.length();
  for (int i = 0; i < amountOfHourPins; i++){
    if (binLength <= amountOfHourPins  && binHours[i] == '1'){
      pinOn(hourPins[i]);
    } else {
      pinOff(hourPins[i]); 
    }
  }
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
