#!/bin/sh

# TST0 (LED 13)
../shell/upload.lua tst0_13.hex.ok
sleep 0.1
echo "load 0 0x2000"
echo "load 0 0x2000"    > /dev/ttyUSB0
sleep 0.1
echo "start 0"
echo "start 0"          > /dev/ttyUSB0
sleep 4.5
echo "stop 0"
echo "stop 0"           > /dev/ttyUSB0
sleep 0.1

# TST0 (LED 12)
../shell/upload.lua tst0_12.hex.ok
sleep 0.1
echo "load 0 0x2000"
echo "load 0 0x2000"    > /dev/ttyUSB0
sleep 0.1
echo "start 0"
echo "start 0"          > /dev/ttyUSB0
sleep 4.5
echo "stop 0"
echo "stop 0"           > /dev/ttyUSB0
