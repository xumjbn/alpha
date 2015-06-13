
#include <unistd.h>
#include <sys/time.h> /* gettimeofday */
#include <time.h>
#include <errno.h>
#include <string.h>

#include "lstd.h"

static void setfield_number(lua_State *L, const char *key, int value)
{
    lua_pushstring(L, key);
    lua_pushnumber(L, value);
    lua_rawset(L, -3);
}

static void settime_to_table(lua_State *L, struct tm *tm)
{
    setfield_number(L, "sec", tm->tm_sec);
    setfield_number(L, "min", tm->tm_min);
    setfield_number(L, "hour", tm->tm_hour);
    setfield_number(L, "mday", tm->tm_mday);
    setfield_number(L, "mon", tm->tm_mon);
    setfield_number(L, "year", tm->tm_year);
    setfield_number(L, "wday", tm->tm_wday);
    setfield_number(L, "yday", tm->tm_yday);
    setfield_number(L, "isdst", tm->tm_isdst);
}

static int getfield_number(lua_State *L, const char *key)
{
    int res = 0;
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_pushstring(L, key);
    lua_rawget(L, -2);
    if (lua_isnil(L, -1)) 
        res = 0;
    else
        res = luaL_checknumber(L, -1);
    lua_pop(L, 1);
    return res;
}

static void gettime_from_table(lua_State *L, struct tm *tm)
{
    tm->tm_sec = getfield_number(L, "sec");
    tm->tm_min = getfield_number(L, "min");
    tm->tm_hour = getfield_number(L, "hour");
    tm->tm_mday = getfield_number(L, "mday");
    tm->tm_mon = getfield_number(L, "mon");
    tm->tm_year = getfield_number(L, "year");
    tm->tm_wday = getfield_number(L, "wday");
    tm->tm_yday = getfield_number(L, "yday");
    tm->tm_isdst = getfield_number(L, "isdst");
}

/*
 * sec = time.time() or nil, errorno = time.time()
 */
static int ltime_time(lua_State *L)
{
    struct timeval tv;
    int res = gettimeofday(&tv, NULL);
    if (res == 0) {
        lua_Number sec = tv.tv_sec + tv.tv_usec / 1000; 
        lua_pushnumber(L, sec);
        return 1;
    } else {
        lua_pushnil(L);
        lua_pushnumber(L, errno);
        return 2;
    }
}

/*
 * strtime = time.ctime(sec) like "Wed Jun 20 21:00:00 2012\n" 25?
 */
static int ltime_ctime(lua_State *L)
{
    time_t tp = luaL_checknumber(L, 1);
    char buf[32];
    memset(buf, 0x00, sizeof(buf));
    ctime_r(&tp, buf);
    lua_pushlstring(L, buf, strlen(buf));
    return 1;
}

/*
 *  epoch time since 1970.01.01 UTC
 *  {sec=, min=, hour=, mday=, mon, year=, wday=, yday=, isdst=} = time.gmtime(sec)
 */
static int ltime_gmtime(lua_State *L)
{
    time_t tp = luaL_checknumber(L, 1);
    struct tm tm;
    gmtime_r(&tp, &tm);
    lua_newtable(L);
    settime_to_table(L, &tm);
    return 1;
}

/*
 * UTC + Time Zone
 */ 
static int ltime_localtime(lua_State *L)
{
    time_t tp = luaL_checknumber(L, 1);
    struct tm tm;
    localtime_r(&tp, &tm);
    lua_newtable(L);
    settime_to_table(L, &tm);
    return 1;
}

/* 
 *  tp = time.mktime({sec=, min=, ...})
 */
static int ltime_mktime(lua_State *L)
{
    struct tm tm;
    lua_settop(L, 1);
    gettime_from_table(L, &tm);
    int tp = mktime(&tm);
    lua_pushnumber(L, tp);
    return 1;
}

/*
 * strtime = time.asctime({sec=, min=, ...}) like "Wed Jun 20 21:00:00 2012\n" 25?
 */
static int ltime_asctime(lua_State *L)
{
    struct tm tm;
    gettime_from_table(L, &tm);
    char buf[32];
    asctime_r(&tm, buf);
    lua_pushlstring(L, buf, strlen(buf));
    return 1;
}

/*
 * elapsed = time.difftime(old, new)
 */
static int ltime_difftime(lua_State *L)
{
    time_t tp1 = luaL_checknumber(L, 1); 
    time_t tp2 = luaL_checknumber(L, 2); 
    int diff = difftime(tp1, tp2);
    lua_pushnumber(L, diff);
    return 1; 
}

static const struct luaL_Reg os_funcs[] = {
    {"time",        ltime_time},
    {"ctime",       ltime_ctime},
    {"gmtime",      ltime_gmtime},
    {"localtime",   ltime_localtime},
    {"mktime",      ltime_mktime},
    {"asctime",     ltime_asctime},
    {"difftime",    ltime_difftime},
    {NULL,          NULL},
};

int lstd_opentime(lua_State *L)
{
    luaL_register(L, "time", os_funcs);
    return 0;
}
