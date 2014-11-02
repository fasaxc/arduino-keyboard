arduino-keyboard
================

Arduino to serial keyboard and python app to simulate X Server input

Arduino sketch implements a simple read loop and debouncer then sends 
characters '0' - '7' over the serial port when the digital inputs are 
grounded.

Python reader app reads the serial port and uses xte to simulate keyboard
events.
