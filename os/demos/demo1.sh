#!/bin/sh

# TST0 (LED 13)
../upload.lua tst0_13.hex.ok
sleep 0.1
echo "load 0 0xF000"
echo "load 0 0xF000"    > /dev/ttyUSB0
sleep 0.1
echo "start 0"
echo "start 0"          > /dev/ttyUSB0
sleep 4.5
echo "stop 0"
echo "stop 0"           > /dev/ttyUSB0
sleep 0.1

# TST0 (LED 12)
../upload.lua tst0_12.hex.ok
sleep 0.1
echo "load 0 0xF000"
echo "load 0 0xF000"    > /dev/ttyUSB0
sleep 0.1
echo "start 0"
echo "start 0"          > /dev/ttyUSB0
sleep 4.5
echo "stop 0"
echo "stop 0"           > /dev/ttyUSB0
