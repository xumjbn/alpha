
#include <stdlib.h>

#include "lstd.h"


typedef struct array {
    int size;
    double v[0];
}num_array_t;

static struct array *checkarray(lua_State *L)
{
    void *ud = luaL_checkudata(L, 1, "lstd.array");
    luaL_argcheck(L, ud != NULL, 1, "array expected");
    return (struct array *)ud;
}

static int larr_new(lua_State *L)
{
    int n = luaL_checkint(L, 1);
    struct array *a = (struct array *)lua_newuserdata(L, sizeof(struct array) * n);
    a->size = n;

    luaL_getmetatable(L, "lstd.array");
    lua_setmetatable(L, -2);
    return 1;
}

/*
 * set(a, i, v)
 */
static int larr_set(lua_State *L)
{
    struct array *a = checkarray(L); 
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
    struct array *a = checkarray(L);
    int i = luaL_checkint(L, 2);
    luaL_argcheck(L, a != NULL, 1, "array expected");
    luaL_argcheck(L, (i >= 0 && i < a->size), 2, "out of range");
    double v = a->v[i];
    lua_pushnumber(L, v);
    return 1;
}

static int larr_size(lua_State *L)
{
    struct array *a = checkarray(L); 
    lua_pushnumber(L, a->size);
    return 1;
}

static const struct luaL_Reg arr_funcs[] = {
    {"new",     larr_new},
    {NULL,      NULL},
};

static const struct luaL_Reg arr_metafuncs[] = {
    {"__index",     larr_get},
    {"__newindex",  larr_set},
    {"__len",       larr_size},
    {NULL,          NULL},
};

int lstd_openarr(lua_State *L)
{
    luaL_newmetatable(L, "lstd.array");
    luaL_register(L, NULL, arr_metafuncs);
    luaL_register(L, "arr", arr_funcs);
    return 0;
}
