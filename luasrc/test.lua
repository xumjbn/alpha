#!/usr/bin/lua

local function rec(n)
    cnt = 0
    if n > 0 then 
        cnt = cnt + 1
        n = n - 1
        print(cnt, n)
        rec(n)
    end
end

rec(5)
