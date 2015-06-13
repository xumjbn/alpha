#!/usr/bin/lua

local fmt = string.format 

local function dump_fmt(n, str)
    for i = 1, n do 
        io.stdout:write("   ")
    end
    if not str then
        local s = ''
    end
    io.stdout:write(tostring(str))
end

--for no share child table and loop table
local function __dump(t, depth)
    depth = depth + 1
    if type(t) == "number" then
        io.stdout:write(t)
    elseif type(t) == "string" then
        io.stdout:write(fmt("%q", t));
    elseif type(t) == "table"  then
        dump_fmt(0, "{\n")
        for k, v in pairs(t) do
            dump_fmt(depth, "[ ")
            __dump(k, depth)
            io.stdout:write(fmt(" ]%8s%8s", "=", " "))
            __dump(v, depth)
            io.stdout:write(",\n")
        end
        dump_fmt(depth - 1, "}")
    else 
        error("unknown type")
    end
end

local function dump(t)
    __dump(t, 0)
    dump_fmt(0, "\n")
end

util = {
    dump = dump,
}
return util
