#!/usr/bin/lua

require 'std'
util = require 'util'

local sec = time.time()
print(sec)

local tm = time.gmtime(sec)  
util.dump(tm)

local tp = time.mktime(tm)
print(tp)

local str = time.ctime(sec)
print(str)

str = time.asctime(tm)
print(str)

str = time.strftime("%c", sec)
print(str)

local tp1 = time.time()
os.sleep(1)
local tp2 = time.time()
local elapsed = time.difftime(tp2, tp1)
print(elapsed)

