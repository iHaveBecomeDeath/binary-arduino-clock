#include "TimerOne.h"
int ticks = 0;
int minutes = 0;
int hours = 0;
const int hourPins[] = {2, 3, 4, 5};
const int minutePins[] = {7, 8, 9, 10, 11};
const int secondPin = 12;

void setup() {
  // TODO: save sizeOf as variables
  int i;
  for (i = 0; i < (sizeof(hourPins)/sizeof(int)) ; i++){
    initOutputPin(hourPins[i]);
   }
  for (i = 0; i < (sizeof(minutePins)/sizeof(int)) ; i++){
    initOutputPin(minutePins[i]);
   }
  initOutputPin(secondPin);
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(clockTick);
}

void loop() {
  
}

void clockTick(){
  toggleSecondPin();
  ticks++;  
  if (ticks >= 60){
    ticks = 0; 
    minutes++;
    if (minutes >= 60) {
      minutes = 0;
      hours++;
      if (hours >= 24) {
       hours = 0;
      }
     }
   }
   updateClockDisplay();
}

void updateClockDisplay(){
  String binMinutes = String(minutes, BIN);
  String binHours = String(hours, BIN);
  
  //TODO: general function for looping these arrays
  for (int i = 0; i < 4; i++){
    if (binMinutes[i] == '1'){
      pinOn(minutePins[i]);
    } else {
      pinOff(minutePins[i]); 
    }
  }
  for (int i = 0; i < 5; i++){
    if (binHours[i] == '1'){
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
