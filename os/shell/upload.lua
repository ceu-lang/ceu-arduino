#!/usr/bin/env lua

local FILE, PORT = ...
assert(FILE and PORT, 'missing FILE or PORT')

io.write('Uploading '..FILE..': ')
io.flush()

local i = 0
for line in io.lines(FILE) do
    os.execute('/bin/echo -ne "'..line..'\n'..'" > '..PORT)
    --print(line)
    io.write('.')
    io.flush()
    os.execute('sleep 0.1')     -- TODO: shouldn't be required
    local n, tp = string.match(line, ':(..)....(..)')
    n = tonumber(n, 16)
    if tp == '00' then
        i = i + n
        if i == 256 then
            os.execute('sleep 0.5')
            i = 0
        end
    end
end
print()
