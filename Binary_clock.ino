#include "Time.h"
const int hourPins[] = {2, 3, 4, 5};
const int minutePins[] = {7, 8, 9, 10, 11};
const int secondPin = 12;
const bool blinkSecondPin = false;
int amountOfMinutePins = 5;
int amountOfHourPins = 4;
int previousSecond = 0;
int previousMinute = 0;
int previousHour = 0;

void setup() {
  Serial.begin(9600);
  int i;
  for (i = 0; i < amountOfHourPins ; i++){
    initOutputPin(hourPins[i]);
   }
  for (i = 0; i < amountOfMinutePins ; i++){
    initOutputPin(minutePins[i]);
   }
  initOutputPin(secondPin);
  setTime(1, 5, 10, 1, 1, 1999); 
}

void loop() {
  int curSec = second();
    if ((previousSecond < curSec) ||  (previousSecond == 60)){
      toggleSecondPin();
      previousSecond = curSec;
      updateMinutes(curSec);
    } 
  int curMin = minute();
  if (previousMinute < curMin || previousMinute == 60){
    updateMinutes(curMin);
    previousMinute = curMin;
  }  
  int curHr = hour();
  if (previousHour < curHr || previousHour == 24){
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
  
  Serial.println("bm: " + bm);
  
  for (int j = 0; j < bm.length(); j++){
   if (bm.charAt(j) == '1'){
     pinOn(minutePins[j]);
   } else {
     pinOff(minutePins[j]);
   }
  }
}
void updateHours(int hrs){
  
}
//void clockTick(){
////  ticks++;
////  if (ticks == 60){
////    ticks = 0;
////  }
////  if (ticks == 0){
////    minutes++;
////  }
////  if (minutes == 60){
////    minutes = 0;
////  }
////  if (minutes == 0){
////    hours++;
////  }
////  if (hours == 24){
////    hours = 0;
////  }
////  Serial.println("Ticks: ");
//// Serial.println(ticks);
//  if (++ticks == 60){
//    ticks = 0; 
////  Serial.println("Mins: ");
//// Serial.println(minutes);
//    if (++minutes == 60) {
//      minutes = 0;
////  Serial.println("Hrs: ");
//// Serial.println(hours);
//      if (++hours == 24) {
//       hours = 0;
//      }
//     }
//   }
//  updateClockDisplay();
//}
//
//void updateClockDisplay(){
//  if (blinkSecondPin){
//    toggleSecondPin();
//  }
////  String mins = String(minutes, BIN);
////  int i;
////  
////  for (i = mins.length() i >0; i--){
////    
////  }
//  String binMinutes = String(minutes, BIN);
//  String binHours = String(hours, BIN);
//  int binLength;
//  int i;
//  
//  //TODO: general function for looping these arrays
//  binLength = binMinutes.length();
//  for (i = 0; i < amountOfMinutePins; i++){
//    if (binLength <= amountOfMinutePins && binMinutes.charAt(i) == '1'){
//      pinOn(minutePins[i]);
//    } else {
//      pinOff(minutePins[i]); 
//    }
//  }
//
//  binLength = binHours.length();
//  for (i = 0; i <= amountOfHourPins; i++){
//    if (binLength <= amountOfHourPins  && binHours.charAt(i) == '1'){
//      pinOn(hourPins[i]);
//    } else {
//      pinOff(hourPins[i]); 
//    }
//  }
//}

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
