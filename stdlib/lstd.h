
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
void lstd_stackdump(lua_State *L);

int lstd_openos(lua_State * L);
int lstd_opentime(lua_State * L);
int lstd_openerr(lua_State *L);

#endif /* _LSTD_H */

