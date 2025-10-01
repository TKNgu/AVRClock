#!/bin/bash

BOAD=arduino:avr:uno
PROJECT=ArduinoClock

if [ "$1" == "chmod" ]
then
    sudo chmod 0666 /dev/ttyACM0
fi

if [ "$1" == "clean" ] || [ "$1" == "c" ]
then
  arduino-cli compile -b $BOAD $PROJECT --clean
elif [ "$1" == "upload" ] || [ "$1" == "u" ]
then
  arduino-cli compile -b $BOAD $PROJECT 
  arduino-cli upload -b $BOAD $PROJECT -p /dev/ttyACM0
else
  arduino-cli compile -b $BOAD $PROJECT 
fi
