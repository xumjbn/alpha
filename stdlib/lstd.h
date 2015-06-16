
#ifndef _LSTD_H
#define _LSTD_H

#include "lualib.h"
#include "lauxlib.h"

#define LERR_NUMS(n) \
    do {\
        lua_pushinteger(L, n);\
        lua_setfield(L, -2, #n);\
    } while (0)



void lstd_checknargs(lua_State *L, int maxargs);

void lstd_pushnumber_totable(lua_State *L, const char *key, lua_Number value);
int  lstd_popnumber_fromtable(lua_State *L, const char *key);
void lstd_pushstring_totable(lua_State *L, const char *key, const char *value);

char *lstd_popstring_fromarray(lua_State *L, int key);

void lstd_stackdump(lua_State *L);

int lstd_openos(lua_State * L);
int lstd_opentime(lua_State * L);
int lstd_openerr(lua_State *L);
int lstd_openopt(lua_State *L);

#endif /* _LSTD_H */

