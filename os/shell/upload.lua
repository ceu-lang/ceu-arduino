#!/usr/bin/env lua

local file = ...

local i = 0
for line in io.lines(file) do
    os.execute('/bin/echo -ne "'..line..'\n'..'" > /dev/ttyUSB0')
    os.execute('/bin/echo -ne "'..line..'\n'..'"')
    local n, tp = string.match(line, ':(..)....(..)')
    n = tonumber(n, 16)
    if tp == '00' then
        i = i + n
        if i == 256 then
            os.execute('sleep 1')
            i = 0
        end
    end
end
