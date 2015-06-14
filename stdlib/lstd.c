#include "lualib.h"
#include "lauxlib.h"

#include "lstd.h"

void lstd_stackdump(lua_State *L)
{
    int n = lua_gettop(L);
    if (n > 0) {
        printf("stack_duamp: tatol element is %d\n", n);
    }
    for (int i = 1; i <= n; i++) {
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
    luaL_argcheck(L, nargs <= maxargs, maxargs + 1, lua_tostring(L, -1));
    lua_pop(L, 1);
}

int luaopen_std(lua_State *L)
{
    lstd_openos(L);
    lstd_opentime(L);
    lstd_openerr(L);
    return 1;
}

