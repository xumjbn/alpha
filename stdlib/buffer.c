
#include "lstd.h"

static int lbuff_new(lua_State *L)
{	
}

static int lbuff_putc(lua_State *L)
{	
}

static int lbuff_putstr(lua_State *L)
{
	
}

static int lbuff_getc(lua_State *L)
{
	
}

static int lbuff_getline(lua_State *L)
{
	
}

static const struct luaL_Reg buff_funcs[] = {
	{"new",		lbuff_new},
	{"putc",	lbuff_putc},
	{"putstr",	lbuff_putstr},
	{"getc",	lbuff_getc},
	{"getline",	lbuff_getline},
	{NULL, 		NULL},
};

int lstd_openbuff(lua_State *L)
{
    luaL_register(L, "buff", buff_funcs);
    return 0;
}