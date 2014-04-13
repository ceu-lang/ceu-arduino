#!/bin/sh

PORT=$@

if [ -z "$PORT" ]
then
echo "ERROR: missing PORT"
exit 1
fi

stty -F $PORT 9600 cs8 -cstopb
sleep 0.1

# TST0 (LED 13)
../shell/upload.lua tst0_13.hex.ok $PORT
sleep 0.1
echo "load 0 0x2000"
echo "load 0 0x2000"    > $PORT
sleep 0.1
echo "start 0"
echo "start 0"          > $PORT
sleep 4.5
echo "stop 0"
echo "stop 0"           > $PORT
sleep 0.1

# TST0 (LED 12)
../shell/upload.lua tst0_12.hex.ok $PORT
sleep 0.1
echo "load 0 0x2000"
echo "load 0 0x2000"    > $PORT
sleep 0.1
echo "start 0"
echo "start 0"          > $PORT
sleep 4.5
echo "stop 0"
echo "stop 0"           > $PORT
