# Speedometer
Arduino project using an Arduino Uno and a Arduino 1.8" TFT LCD Screen

This arduino project will serve as a speedometer for any vehicle with round wheels when given the tire's circumference.

Logic:
1 mile = 5280 feet = 63360 inches
1 hr = 60 minutes = 3600 seconds

**diameter needs to be given in mile
Circumference = 2*radius*pi = diameter*pi
Rate = number of rotations per second
Speed(in mph) = Rate*Circumference*3600
