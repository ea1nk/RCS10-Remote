Console application for the USB Relay Board
-------------------------------------------

If there are more than one FTDI device attached to the system, it is recommended to get the serial number of the Denkovi board. To get the serial number just plug the board to the raspberry pi and do a dmesg on a terminal. 

This application must ve invoked with one argument like:

    relay_control -rX

where X is the relay to be switched ON/OFF.

-rs returns the status of the relays.

-ra (All On) -rn (All Off) are provided only for testing purposes and should NEVER be used with the RCS10 Antenna Switch. 

RaspberryPi Instructions:
---------------------------------------------

sudo apt-get install libftdi1 libftdi libftdi-dev

gcc -v -o relay_control -lftdi relay_control.c
