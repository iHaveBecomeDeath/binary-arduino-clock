int ticks = 0;
int minutes = 0;
int hours = 0;
const int hourPins = {2, 3, 4, 5};
const int minutePins = {6, 7, 8, 9, 10};
const int secondPin = 11;

void setup() {
  // init hourPins
  // TODO: save sizeOf as variables
  for (int i = 0; i < sizeOf(hourPins)/sizeOf(int)) - 1; i++){
    initOutputPin(hourPins[i];
   }
  for (int i = 0; i < sizeOf(minutePins)/sizeOf(int)) - 1; i++){
    initOutputPin(minutePins[i];
   }
  initOutputPin(secondPin);
}

void loop() {
  toggleSecondPin();
  delay(1000);
  if (ticks < 60){
    ticks++;  
  } else {
    if (minutes < 60) {
      minutes++;  
    } else {
      minutes = 0;
      if (hours < 24) {
       hours++;
       else{
         hours = 0;
       }
      }
    }
   ticks = 0; 
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
     pinOff(pinNumber);
}
