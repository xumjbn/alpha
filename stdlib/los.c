#include <unistd.h>
#include "lualib.h"
#include "lauxlib.h"

#include "lstd.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


static int los_open(lua_State *L)
{
    int n = lua_gettop(L);
    if (n < 2) {
        perror("args its too short");
        return -1;
    }
/*
    int oflag = 0;
    char *pathname = lua_tostring(luaL_checkstring(L, 1), 1);
    char *flag = lua_tostring(luaL_checkstring(L, 2), 2);
    if (strncmp(flag, "r", 1) == 0) {
        oflag = O_RDONLY;        
    } else if (strncmp(flag, "w", 1) == 0) {
        oflag = O_WRONLY;
    }

    int res = open(pathname, oflag);
    if (res > 0) {
        lua_pushnumber(L, 0);
        lua_pushnumber(L, res);
    } else {
        lua_pushnil(L);
        lua_pushnumber(L, res);
    }
    */
    return 2;
}

static int los_getpid(lua_State *L)
{
    lua_pushnumber(L, getpid());
    return 1;
}

static int los_getppid(lua_State *L)
{
    lua_pushnumber(L, getppid());
    return 1;
}

static int los_getuid(lua_State *L)
{
    lua_pushnumber(L, getuid());
    return 1;
}

static int los_geteuid(lua_State *L)
{
    lua_pushnumber(L, geteuid());
    return 1;
}

static int los_getgid(lua_State *L)
{
    lua_pushnumber(L, getgid());
    return 1;
}

static int los_getegid(lua_State *L)
{
    lua_pushnumber(L, getegid());
    return 1;
}

static int los_sleep(lua_State *L)
{
    usleep(luaL_checkint(L, 1) * 1000000);
    return 0;
}

static int los_usleep(lua_State *L)
{
    usleep(luaL_checkint(L, 1));
    return 0;
}

static int los_sync(lua_State *L)
{
    sync();
    return 0;
}

static const struct luaL_Reg os_funcs[] = {
    {"open",    los_open},
    {"getpid",  los_getpid},
    {"getppid", los_getppid},
    {"getuid",  los_getuid},
    {"geteuid", los_geteuid},
    {"getgid",  los_getgid},
    {"getegid", los_getegid},
    {"sleep",   los_sleep},
    {"usleep",  los_usleep},
    {"sync",    los_sync},
    {NULL,      NULL},
};

int lstd_openos(lua_State *L)
{
    luaL_register(L, "os", os_funcs);
    return 0;
}
