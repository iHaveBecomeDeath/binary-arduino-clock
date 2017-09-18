# Binary Arduino clock
A binary clock for use with Arduino/Genuino (Uno) and clones.  I've tried to make it relatively general and configurable so as to make it useful for more developers, but my first priority here has been the needs of my own experiment and its hardware centric design.

The clock itself is relatively simple, housed in a wooden frame, but I've made some steps towards making it almost as user friendly as a "normal" 12/24h clock.

![Example of the finished build](https://image.ibb.co/fosMM5/31477952966_4b40465376_o.jpg)

Requirements: 
- Arduino (any model will do, really)
- [Time library](https://github.com/PaulStoffregen/Time)
- 11 little LEDs (12 if you want a light for seconds passing as well), 5mm worked well for me
- An RTC module (if you want things to be accurate), 1307, 3231 or anything similar will do
- lots of little cables and resistors (220ohm or so)
- preferrably a breadboard (I built mine in a wooden box)
- A charger or other power supply if you want to leave it on

![Fritzing breadboard layout](https://image.ibb.co/chZFEQ/Binary_clock_prototype_fzz_Fritzing_Breadboard_View.png)

Future modifications include NTP, buttons for settings, possibly an LCD display for human readable time. Using the timer library NTP support should be doable, or 433mhz setting of time, or why not over WiFi?
