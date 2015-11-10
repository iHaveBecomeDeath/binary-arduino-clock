int ticks = 0;
int minutes = 0;
int hours = 0;
const int hourPins = {2, 3, 4, 5};
const int hourPins = {6, 7, 8, 9, 10};
const int secondPin = 11;

void setup() {
   for (int i = 0; i < sizeOf(hourPins)/sizeOf(int)) - 1; i++){
     pinMode(hourPins[i], OUTPUT);
   }
}

void loop() {
  toggleSecondPin();
  delay(1000);
  if (ticks < 60)
  ticks++;
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
