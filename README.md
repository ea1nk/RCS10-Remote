# RCS10-Remote
2012 - SCQ Devices - EA1NK
Remote control for Ameritron RCS10 Antenna Switch

This project features a remote control to be used with the Ameritron RCS10 Antenna Switch.

Based on Node.js and using HTML5 and WebSockets technology a simple web interface is provided.

WARNING:
----------------------------------------------------------------

The RCS10 controller will be connected to the relay board using the 8 inputs located at the back of the controller, one input to one relay of the USB relay board. 

The RCS10 controller MUST NOT be connected to the mains. Power switch at the front panel MUST be OFF.

The 18v will be feeded trough the relays to the desired input, in this way we are using only the BCD encoding circuit. 

Feeding the 18v through the back inputs is the same as using the frontal knob with the front panel switch turned ON.

+++ Remember RCS10 controller switched OFF and disconnected from the mains +++


Hardware:
----------------------------------------------------------------

RaspberryPi board (any flavour) with GNU Linux OS installed.

Easy Rotor Control ERC board

https://www.schmidt-alba.de/eshop/

----------------------------------------------------------------

Software and Libraries:
----------------------------------------------------------------

NodeJS

serialport node library

JQuery

Bootstrap4


