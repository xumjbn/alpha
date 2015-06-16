#!/usr/bin/lua

require 'std'
u = require 'util'

optlong = {
    {"help", "none", "h"},
    {"debug", "none", "d"},
    {"info", "required", "i"},
    {"list", "required", "l"},
}

local args = arg

---[[
local list;
local opts, err = getopt.getopt(args, "hvl:", 1)
--print(opts, err)
--u.dump(opts)
if not err then  
    for k, v in pairs(opts) do 
        if k == "v" then 
            print("Version 5.14 lua");
        elseif k == "h" then 
            print("usage: -h -v -l xx")
        elseif k == "l" then 
            list = v;
            print(list)
        end
    end
else 
    for k, v in pairs(err) do 
        local s = string.match("hvl:", k); 
        if s then
            print(string.format("option requires an argument -- \'%s\'", k))
        else 
            print(string.format("invalid option -- \'%s\'", k))
        end
    end
end
---]]

--[[
opts, err = getopt.getopt_long(args, "hvl:", optlong)
--print(opts, err)
--u.dump(opts)
if not err then  
    for k, v in pairs(opts) do 
        if k == "v" then 
            print("Version 5.14 lua");
        elseif k == "h" then 
            print("usage: -h -v -l xx")
        elseif k == "l" then 
            list = v;
            print(list)
        end
    end
else 
    for k, v in pairs(err) do 
        local s = string.match("hvl:", k); 
        if s then
            print(string.format("option requires an argument -- \'%s\'", k))
        else 
            print(string.format("invalid option -- \'%s\'", k))
        end
    end
end
--]]
