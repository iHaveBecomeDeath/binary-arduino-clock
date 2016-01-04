# Binary Arduino clock
A binary clock for use with Arduino/Genuino (Uno) and clones.  I've tried to make it relatively general and configurable so as to make it useful for more developers, but my first priority here has been the needs of my own experiment and it's hardware centric design.

The clock itself is relatively simple, housed in a wooden frame, but I've made some steps towards making it almost as user friendly as a "normal" 12/24h clock.

Requirements: 
- Arduino
- [Timer1 library](http://playground.arduino.cc/Code/Timer1)
- 11 little LEDs (12 if you want a light for seconds passing as well)
- lots of little cables
- preferrably a breadboard

Future modifications include RTC module and buttons for settings, possibly an LCD display for human readable time. Using the timer library NTP support should be doable, or 433mhz setting of time, if other requirements are fulfilled.
