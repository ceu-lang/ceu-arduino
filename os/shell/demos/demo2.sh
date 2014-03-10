#!/bin/sh

# GPIO
../upload.lua gpio.hex.ok
sleep 0.1
echo "load 0 0x2000"    > /dev/ttyUSB0
sleep 0.1
echo "start 0"          > /dev/ttyUSB0
sleep 0.1

# APP1
../upload.lua app1.hex.ok
sleep 0.1
echo "load 1 0xC000"    > /dev/ttyUSB0
sleep 0.1
echo "link 1 1 0 243"   > /dev/ttyUSB0
sleep 0.1
echo "link 1 2 0 242"   > /dev/ttyUSB0
sleep 0.1
echo "start 1"          > /dev/ttyUSB0
sleep 4.5

# APP2
../upload.lua app2.hex.ok
sleep 0.1
echo "load 2 0xC800"    > /dev/ttyUSB0
sleep 0.1
echo "link 2 1 0 243"   > /dev/ttyUSB0
sleep 0.1
echo "link 2 2 0 242"   > /dev/ttyUSB0
sleep 0.1
echo "start 2"          > /dev/ttyUSB0
sleep 4.5

echo "stop 1"           > /dev/ttyUSB0
sleep 2
echo "stop 2"           > /dev/ttyUSB0
