#!/usr/bin/env lua

local file = ...

for line in io.lines(file) do
    os.execute('/bin/echo -ne "'..line..'\n'..'" > /dev/ttyUSB0')
    os.execute('/bin/echo -ne "'..line..'\n'..'"')
    os.execute('sleep 1')
end
