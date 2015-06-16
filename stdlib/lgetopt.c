
#include <string.h>
#include <getopt.h>
#include <stdbool.h>

#include "lstd.h"


static int parse_optlongs(lua_State *L, int index, struct option *optlongs)
{
    int has_arg;
    const char *s = NULL;

    luaL_checktype(L, index, LUA_TTABLE);
    int n = lua_objlen(L, index);
    for (int i = 1; i <= n; i++) {
        lua_pushnumber(L, i);
        lua_rawget(L, -2);
        luaL_checktype(L, -1, LUA_TTABLE);
        s = lstd_popstring_fromarray(L, 2);
        if (strcmp(s, "none") == 0) 
            has_arg = no_argument;
        else if (strcmp(s, "required") == 0)
            has_arg = required_argument;
        else if (strcmp(s, "optional") == 0) 
            has_arg = optional_argument;
        else {
            luaL_error(L, "arguments expected (none or required or optional");
        }
        optlongs[i - 1].name = lstd_popstring_fromarray(L, 1);
        optlongs[i - 1].has_arg = has_arg;
        optlongs[i - 1].flag = NULL;
        s = lstd_popstring_fromarray(L, 3);
        optlongs[i - 1].val = s[0];        
        lua_pop(L, 1);
    }
    lua_pop(L, 1);
    return 0;
}

static int parse_args(lua_State *L, int index, int *argc, char *argv[])
{
    int i = 0;

    luaL_checktype(L, index, LUA_TTABLE);
    int nargs = lua_objlen(L, index);
    if (nargs > 64)
        luaL_error(L, "argments is too loog %d, should less than  64", argc);
    for (i = 0; i <= nargs; i++) 
        argv[i] = lstd_popstring_fromarray(L, i);
    argv[i] = NULL;
    *argc = nargs + 1;
    lua_pop(L, 1);
    
    return 0;
}

static int _getopt_long(lua_State *L, int argc, char * const argv[], 
        const char *optstring, struct option *longopts)
{
    int c;
    bool res_table = false;
    char optstr[2] = {0};

    lua_newtable(L);
    lua_newtable(L);    /* top */
    while ((c = getopt_long(argc, argv, optstring, longopts, NULL)) != -1) {
        if (c != '?') {
            optstr[0] = c;
            lua_pushstring(L, optstr);
            lua_pushstring(L, (optarg ? optarg: ""));
            lua_rawset(L, -4);
        } else {
            res_table = true;
            optstr[0] = optopt;
            lua_pushstring(L, optstr);
            lua_pushstring(L, (argv[optind] ? argv[optind]: ""));
            lua_rawset(L, -3);
        }
    }
    if (!res_table) {
        lua_pop(L, 1);
        lua_pushnil(L);
    }
    return 0;
}

/*
 * opts, err = getopt.getopt(args, "hvl:", [1])
 */
static int lopt_getopt(lua_State *L)
{
    int argc = 0;
    char *argv[64];
    const char *optstring = NULL;
    
    if (lua_isnil(L, 3) || lua_isnumber(L, 3)) { 
        if (lua_tonumber(L, 3))
            opterr = 0; 
    } else {
        luaL_error(L, "bad arguments");
    }
    lua_settop(L, 2);
    optstring = luaL_checkstring(L, 2);
    lua_pop(L, 1);
    parse_args(L, 1, &argc, argv);
    _getopt_long(L, argc, argv, optstring, NULL);

    return 2;
}

/*
 * args = arg
 * optstring =  "hc:i" 
 * longopts = { 
 *      {"help", "none", "h"}, 
 *      {"debug", "required", "d"},
 * } 
 * opts, err = getopt.getopt_long(args, optstrings, longopts, [1])
 */
static int lopt_getopt_long(lua_State *L)
{
    int argc = 0;
    char *argv[64];
    struct option optlongs[64];
    const char *optstring = NULL;
    
    if (lua_tonumber(L, 4))
        opterr = 0; 

    lua_settop(L, 3);
    parse_optlongs(L, 3, optlongs);
    optstring = luaL_checkstring(L, -1);
    lua_pop(L, 1);
    parse_args(L, 1, &argc, argv);
    _getopt_long(L, argc, argv, optstring, NULL);

    return 2;
}

static const struct luaL_Reg opt_funcs[] = {
    {"getopt",       lopt_getopt},
    {"getopt_long",  lopt_getopt_long},
    {NULL,           NULL},
};

int lstd_openopt(lua_State *L)
{
    luaL_register(L, "getopt", opt_funcs);
    return 0;
}
