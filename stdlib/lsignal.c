
#include <signal.h>
#include <errno.h>

#include "lstd.h"


typedef void (*handler)(int);

static handler sig_handler;
static lua_State *globalL = NULL;


static void sig_hook(lua_State *L, lua_Debug *ar)
{
    UNUSED(ar);
	lua_sethook(L, NULL, 0, 0);  
    lua_pushstring(L, "signal.handler");
	lua_rawget(L, LUA_REGISTRYINDEX);
    lua_pcall(L, 0, 0, 0);
}

static void laction(int signo)
{
	UNUSED(signo);
    lua_sethook(globalL, sig_hook, LUA_MASKCALL | LUA_MASKRET | LUA_MASKCOUNT, 0);
}

/*
 * err = signal.signal(signo, handler)
 * @signo: signal.SIGINT ...
 * @handler: lua function 
 */
static int lsignal_signal(lua_State *L)
{
    globalL = L;
    lstd_checknargs(L, 2);
    int signo = luaL_checkint(L, 1);

	const char *s = NULL;
	if (lua_isstring(L, 2)) {
		s = lua_tostring(L, 2);
		if (strncmp(s, "SIG_IGN", 7) == 0)
			sig_handler = SIG_IGN;
		else if(strncmp(s, "SIG_DFL", 7) == 0)
			sig_handler = SIG_DFL;
		else 
			luaL_error(L, "%s", "bad argument #2!");
	} else if(lua_isfunction(L, 2)) {
		lua_pushstring(L, "signal.handler");
		lua_pushvalue(L, 2);
		lua_rawset(L, LUA_REGISTRYINDEX);	
		sig_handler = laction;
	} else {
		luaL_error(L, "%s", "bad argument #2!");
	}
	
	if (signal(signo, sig_handler) == SIG_ERR) {
		lua_pushnumber(L, errno);
	} else {
		lua_pushnumber(L, 0);
	}
    return 1;
}

/*
 * err = signal.kill(pid, signo)
 * @pid: process ID
 * @signo SIG_XX
 */
static int lsignal_kill(lua_State *L)
{
    lstd_checknargs(L, 2);
    pid_t pid = luaL_checkint(L, 1);
    int signo = luaL_checkint(L, 2);
    int err = kill(pid, signo);
    lua_pushnumber(L, err? errno: 0);
    return 1;
}

/*
 * err = signal.raise(signo)
 */
static int lsignal_raise(lua_State *L)
{
    lstd_checknargs(L, 1);
    int signo = luaL_checkint(L, 1);
    int err = raise(signo);
    lua_pushnumber(L, err? errno: 0);
    return 1;
}

static void lsignal_const_register(lua_State *L)
{
    LENUMS(SIGALRM);
    LENUMS(SIGBUS);
    LENUMS(SIGCHLD);
    LENUMS(SIGCONT);
    LENUMS(SIGFPE);
    LENUMS(SIGHUP);
    LENUMS(SIGILL);
    LENUMS(SIGINT);
    LENUMS(SIGIO);
    LENUMS(SIGIOT);
    LENUMS(SIGKILL);
    LENUMS(SIGPIPE);
    LENUMS(SIGPOLL);
    LENUMS(SIGPROF);
    LENUMS(SIGPWR);
    LENUMS(SIGQUIT);
    LENUMS(SIGSEGV);
    LENUMS(SIGSTOP);
    LENUMS(SIGSYS);
    LENUMS(SIGTERM);
    LENUMS(SIGTRAP);
    LENUMS(SIGTSTP);
    LENUMS(SIGTTIN);
    LENUMS(SIGTTOU);
    LENUMS(SIGURG);
    LENUMS(SIGUSR1);
    LENUMS(SIGUSR2);
    LENUMS(SIGVTALRM);
    LENUMS(SIGWINCH);
    LENUMS(SIGXCPU);
    LENUMS(SIGXFSZ);
}

static const struct luaL_Reg signal_funcs[] = {
    {"signal",  lsignal_signal},
    {"kill",    lsignal_kill},
    {"raise",   lsignal_raise},
    {NULL,      NULL},
};

int lstd_opensignal(lua_State *L)
{
    luaL_register(L, "signal", signal_funcs);
	lsignal_const_register(L);
	lua_pushstring(L, "SIG_IGN");
	lua_pushstring(L, "SIG_IGN");
	lua_rawset(L, -3);
	lua_pushstring(L, "SIG_DFL");
	lua_pushstring(L, "SIG_DFL");
	lua_rawset(L, -3);
    return 0;
}
