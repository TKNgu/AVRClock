#!/bin/bash

BOAD=arduino:avr:uno
PROJECT=ArduinoClock

if [ "$1" == "clean" ]
then
  arduino-cli compile -b $BOAD $PROJECT --clean
elif [ "$1" == "upload" ]
then
  arduino-cli compile -b $BOAD $PROJECT 
  arduino-cli upload -b $BOAD $PROJECT -p /dev/ttyACM0
else
  arduino-cli compile -b $BOAD $PROJECT 
fi
