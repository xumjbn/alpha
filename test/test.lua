#!/usr/bin/lua

require 'std'
u = require 'util'

syslog.openlog("xujns")
syslog.syslog(syslog.LOG_EMERG, "hi xujns")
syslog.close()
