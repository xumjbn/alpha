#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include "lstd.h"

/*
 * err, fd = open(path, oflag, [perm])
 * @path: pathname
 * @oflag: eg. os.O_RDONLY os.O_WRONLY
 * @perm: file perimision
 * return 0 and fd if success, or errno and nil if failed
 */
static int los_open(lua_State *L)
{
	mode_t mode = 0644;
	
    lstd_checknargs(L, 2);
    const char *path = luaL_checkstring(L, 1);
	int oflag = luaL_checkint(L, 2);
	if (lua_isnumber(L, 3))
		mode = luaL_checkint(L, 3);
	
    int fd = open(path, oflag, mode);
    if (fd > 0) {
        lua_pushnumber(L, 0);
        lua_pushnumber(L, fd);
    } else {
        lua_pushnumber(L, errno);
		lua_pushnil(L);
    }
    return 2;
}

/*
 * pid = os.getpid()
 */
static int los_getpid(lua_State *L)
{
    lua_pushnumber(L, getpid());
    return 1;
}

/*
 * ppid = os.getppid()
 */
static int los_getppid(lua_State *L)
{
    lua_pushnumber(L, getppid());
    return 1;
}

/*
 * uid = os.getuid()
 */
static int los_getuid(lua_State *L)
{
    lua_pushnumber(L, getuid());
    return 1;
}

/*
 * euid = os.geteuid()
 */
static int los_geteuid(lua_State *L)
{
    lua_pushnumber(L, geteuid());
    return 1;
}

/*
 * gid = os.getgid()
 */
static int los_getgid(lua_State *L)
{
    lua_pushnumber(L, getgid());
    return 1;
}

/*
 * egid = os.getegid()
 */
static int los_getegid(lua_State *L)
{
    lua_pushnumber(L, getegid());
    return 1;
}

/*
 * os.sleep(sec)
 */
static int los_sleep(lua_State *L)
{
    usleep(luaL_checkint(L, 1) * 1000000);
    return 0;
}

/*
 * os.usleep(usec)
 */
static int los_usleep(lua_State *L)
{
    usleep(luaL_checkint(L, 1));
    return 0;
}

/*
 * os.sync()
 */
static int los_sync(lua_State *L)
{
	UNUSED(L);
    sync();
    return 0;
}

/*
 * os.abart()
 */
static int los_abort(lua_State *L)
{
	UNUSED(L);
    abort();
    return 0;
}

/*
 * err = os.pause()
 */
static int los_pause(lua_State *L)
{
    int err = pause();
    lua_pushnumber(L, err? errno: 0);
    return 1;
}

/*
 * sec = os.alarm(sec)
 */
static int los_alarm(lua_State *L)
{
    lstd_checknargs(L, 1);
    int sec = luaL_checkint(L, 1);
    lua_pushnumber(L, alarm(sec));
    return 1;
}

static void los_const_register(lua_State *L)
{
	/* open oflag  */
	LENUMS(O_RDONLY);	
	LENUMS(O_WRONLY);	
	LENUMS(O_RDWR);
	LENUMS(O_APPEND);
	LENUMS(O_CREAT);
	LENUMS(O_EXCL);
	LENUMS(O_TRUNC);
	LENUMS(O_NOCTTY);
	LENUMS(O_NONBLOCK);
	LENUMS(O_SYNC);
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
    {"abort",   los_abort},
    {"pause",   los_pause},
    {"alarm",   los_alarm},
    {NULL,      NULL},
};

int lstd_openos(lua_State *L)
{
    luaL_register(L, "os", os_funcs);
	los_const_register(L);
    return 0;
}
