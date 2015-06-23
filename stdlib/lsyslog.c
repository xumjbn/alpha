
#include <syslog.h>
#include "lstd.h"

/*
 * syslog.openlog(ident, [log_options, [facility]])
 */
static int lsyslog_openlog(lua_State *L)
{
    const char *ident = NULL;
    int log_options = LOG_CONS | LOG_PID;
    int facility = 0;

    int n = lua_gettop(L);
    if (n <= 0) 
        luaL_error(L, "expect one more argument");

    if (n == 1) {
        ident = luaL_checkstring(L, 1);
    } else if (n == 2) {
        ident = luaL_checkstring(L, 1);
        log_options = luaL_checkint(L, 2);
    } else if (n == 3) {
        ident = luaL_checkstring(L, 1);
        log_options = luaL_checkint(L, 2);
        facility = luaL_checkint(L, 3);
    }
    openlog(ident, log_options, facility);
    return 0;
}

/*
 * syslog.syslog([log_level], msg)
 */
static int lsyslog_syslog(lua_State *L)
{
    int level = LOG_ERR;
    const char *msg = NULL;

    int n = lua_gettop(L);
    if (n <= 0) 
        luaL_error(L, "expect one more argument");

    if (n == 1) {
        msg = luaL_checkstring(L, 1);
    } else if(n >= 2) {
        level = luaL_checknumber(L, 1);
        msg = luaL_checkstring(L, 2);
    }
    syslog(level, "%s", msg);
    return 0;
}

/*
 * syslog.closelog()
 */
static int lsyslog_closelog(lua_State *L)
{
    lstd_checknargs(L, 0);
    closelog();
    return 0;
}

static void lsyslog_enum_register(lua_State *L)
{
    /* log_options */
    LENUMS(LOG_CONS);
    LENUMS(LOG_NDELAY);
    LENUMS(LOG_NOWAIT);
    LENUMS(LOG_ODELAY);
    LENUMS(LOG_PERROR);
    LENUMS(LOG_PID);

    /* facility */
    LENUMS(LOG_AUTH);   
    LENUMS(LOG_AUTHPRIV);   
    LENUMS(LOG_CRON);   
    LENUMS(LOG_KERN);   
    LENUMS(LOG_FTP);   
    LENUMS(LOG_LOCAL0);
    LENUMS(LOG_LPR);    
    LENUMS(LOG_MAIL);  
    LENUMS(LOG_NEWS);   
    LENUMS(LOG_SYSLOG);
    LENUMS(LOG_USER);   
    LENUMS(LOG_UUCP);   
    
    /* log level */
    LENUMS(LOG_EMERG);
    LENUMS(LOG_ALERT);
    LENUMS(LOG_CRIT);
    LENUMS(LOG_ERR);
    LENUMS(LOG_WARNING);
    LENUMS(LOG_NOTICE);
    LENUMS(LOG_INFO);
    LENUMS(LOG_DEBUG);
}

static const luaL_Reg syslog_funcs[] = {
    {"openlog",  lsyslog_openlog},
    {"syslog",   lsyslog_syslog},
    {"closelog", lsyslog_closelog},
    {NULL,       NULL},
};

int lstd_opensyslog(lua_State *L)
{
    luaL_register(L, "syslog", syslog_funcs);
    lsyslog_enum_register(L);
    return 0;
}
