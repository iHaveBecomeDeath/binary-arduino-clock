#include <Time.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include <Wire.h>

const int hourPins[] = {2, 3, 4, 5, 6};
const int minutePins[] = {7, 8, 9, 14, 15, 16};
const int secondRed = 10;
const int secondGreen = 11;
const int secondBlue = 12;
const bool blinkSecondPins = true;
int amountOfMinutePins = 6;
int amountOfHourPins = 5;
int previousSecond = 0;
int previousMinute = 0;
int previousHour = 0;

void setup() {
  Serial.begin(9600);
  setSyncProvider(RTC.get);
  setSyncInterval(100);

  int i;
  for (i = 0; i < amountOfHourPins ; i++){
    initOutputPin(hourPins[i]);
   }
  for (i = 0; i < amountOfMinutePins ; i++){
    initOutputPin(minutePins[i]);
   }
  pinMode(secondRed, OUTPUT);
  pinMode(secondGreen, OUTPUT);
  pinMode(secondBlue, OUTPUT);
  
  updateMinutes(minute());
  updateHours(hour());
  updateSecondColor(second());
}

void loop() {
  int curSec = second();
    if ((previousSecond < curSec) ||  (previousSecond > curSec && previousSecond == 59)){
      toggleSecondPins(curSec);
      previousSecond = curSec;
    } 
  int curMin = minute();
  if (previousMinute < curMin || (previousMinute > curMin && previousMinute == 59)){
    updateMinutes(curMin);
    previousMinute = curMin;
  }  
  int curHr = hour();
  if (previousHour < curHr || (previousHour > curHr && previousHour == 23)){
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

void toggleSecondPins(int seconds){
  if (seconds % 2 == 0) {
    writeSecondColor(0,0,0);
  } else {
    updateSecondColor(seconds);
  }
}

void updateSecondColor(int seconds){
  int red = 0;
  int green = 0;
  int blue = 0;
  if (seconds <= 21){
    blue = seconds*2;
  } else if (seconds <= 41){
    red = seconds;
    blue = 41 - seconds;
  } else {
    red = 60 - seconds;
    green = seconds;
  }
   Serial.print("Second: ");
   Serial.print(seconds);
   Serial.print(", red: ");
   Serial.print(red);
   Serial.print(", green: ");
   Serial.print(green);
   Serial.print(", blue: ");
   Serial.print(blue);
   Serial.println("");

  writeSecondColor(red, green, blue);
}

void writeSecondColor(int red, int green, int blue){
  analogWrite(secondRed, red);
  analogWrite(secondGreen, green);
  analogWrite(secondBlue, blue);
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

