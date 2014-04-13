#!/bin/sh

PORT=$@

if [ -z "$PORT" ]
then
echo "ERROR: missing PORT"
exit 1
fi

stty -F $PORT 9600 cs8 -cstopb
sleep 0.1

# GPIO
echo "upload GPIO 0x2000"
read xxx
../shell/upload.lua gpio.hex.ok $PORT
sleep 0.1
echo "load 0 0x2000"
read xxx
echo "load 0 0x2000"    > $PORT
sleep 0.1
echo "start 0"
read xxx
echo "start 0"          > $PORT
sleep 0.1

# APP1
echo "upload APP1 0xC000"
read xxx
../shell/upload.lua app1.hex.ok $PORT
sleep 0.1
echo "load 1 0xC000"
read xxx
echo "load 1 0xC000"    > $PORT
sleep 0.1
echo "link 1 1 0 243"
read xxx
echo "link 1 1 0 243"   > $PORT
sleep 0.1
echo "link 1 2 0 242"
read xxx
echo "link 1 2 0 242"   > $PORT
sleep 0.1
echo "start 1"
read xxx
echo "start 1"          > $PORT
#sleep 4.5

# APP2
echo "upload APP2 0xC800"
read xxx
../shell/upload.lua app2.hex.ok $PORT
sleep 0.1
echo "load 2 0xC800"
read xxx
echo "load 2 0xC800"    > $PORT
sleep 0.1
echo "link 2 1 0 243"
read xxx
echo "link 2 1 0 243"   > $PORT
sleep 0.1
echo "link 2 2 0 242"
read xxx
echo "link 2 2 0 242"   > $PORT
sleep 0.1
echo "start 2"
read xxx
echo "start 2"          > $PORT
#sleep 4.5

echo "stop 1"
read xxx
echo "stop 1"           > $PORT
#sleep 2
echo "stop 2"
read xxx
echo "stop 2"           > $PORT
