
#include "lstd.h"


void lstd_stackdump(lua_State *L)
{
    int n = lua_gettop(L);
    if (n > 0) {
        printf("stack_duamp: tatol element is %d\n", n);
    }
    for (int i = n; i >= 1; i--) {
        int type = lua_type(L, i);
        switch (type) {
        case LUA_TNUMBER:
            printf("index %d value is %f\n", i, lua_tonumber(L, i));
            break;
        case LUA_TBOOLEAN:
            printf("index %d value %s\n", i, lua_toboolean(L, i) ? "true": "fasle");
            break;
        case LUA_TSTRING:
            printf("index %d value is \"%s\"\n", i, lua_tostring(L, i));
            break;
        default:
            printf("index %d type  is [%s]\n", i, lua_typename(L, type));
            break;
        }
    }
}

void lstd_checknargs(lua_State *L, int maxargs)
{
    int nargs = lua_gettop(L);
    lua_pushfstring(L, "no more than %d argument%s expected, got %d",
            maxargs, maxargs <= 1? "": "s", nargs);
    luaL_argcheck(L, nargs >= maxargs, maxargs + 1, lua_tostring(L, -1));
    lua_pop(L, 1);
}

void lstd_rawsetnumber(lua_State *L, const char *key, int value)
{
    lua_pushstring(L, key);
    lua_pushnumber(L, value);
    lua_rawset(L, -3);
}

void lstd_rawsetstring(lua_State *L, const char *key, const char *value)
{
    lua_pushstring(L, key);
    lua_pushstring(L, value);
    lua_rawset(L, -3);
}

int lstd_rawgetnumber(lua_State *L, const char *key)
{
    int res = 0;

    lua_pushstring(L, key);
    lua_rawget(L, -2);
    if (lua_isnil(L, -1) != 1) 
        res = luaL_checknumber(L, -1);
    lua_pop(L, 1);
    return res;
}

const char *lstd_rawgetistring(lua_State *L, int key)
{
    const char *str = "nil";

    lua_pushnumber(L, key);
    lua_rawget(L, -2);
    if (lua_isnil(L, -1) != 1) 
       str = luaL_checkstring(L, -1);
    lua_pop(L, 1);
    return str;
}


int luaopen_std(lua_State *L)
{
    lstd_openos(L);
    lstd_openfs(L);
    lstd_opentime(L);
    lstd_openerr(L);
    lstd_openopt(L);
    lstd_openarr(L);
	lstd_opensocket(L);
    lstd_opensyslog(L);
    return 1;
}

