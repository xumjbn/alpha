
#include <stdlib.h>

#include "lstd.h"


typedef struct array {
    int size;
    double v[0];
}num_array_t;

static int larr_new(lua_State *L)
{
    int n = luaL_checkint(L, 1);
    struct array *a = (struct array *)lua_newuserdata(L, sizeof(struct array) * n);
    a->size = n;
    return 1;
}

/*
 * set(a, i, v)
 */
static int larr_set(lua_State *L)
{
    struct array *a = (struct array *)lua_touserdata(L, 1);
    int i = luaL_checkint(L, 2);
    double v = luaL_checknumber(L, 3);
    luaL_argcheck(L, a != NULL, 1, "array expected");
    luaL_argcheck(L, (i >= 0 && i < a->size), 2, "out of range");
    a->v[i] = v;
    return 0;
}

/*
 * v = get(a, i)
 */
static int larr_get(lua_State *L)
{
    struct array *a = (struct array *)lua_touserdata(L, 1);
    int i = luaL_checkint(L, 2);
    luaL_argcheck(L, a != NULL, 1, "array expected");
    luaL_argcheck(L, (i >= 0 && i < a->size), 2, "out of range");
    double v = a->v[i];
    lua_pushnumber(L, v);
    return 1;
}

static const struct luaL_Reg arr_funcs[] = {
    {"new",     larr_new},
    {"set",     larr_set},
    {"get",     larr_get},
    {NULL,      NULL},
};

int lstd_openarr(lua_State *L)
{
    luaL_register(L, "arr", arr_funcs);
    return 0;
}
