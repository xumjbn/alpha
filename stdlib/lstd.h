
#ifndef _LSTD_H
#define _LSTD_H

#include "lualib.h"
#include "lauxlib.h"

void lstd_stackdump(lua_State *L);
int lstd_openos(lua_State * L);
int lstd_opentime(lua_State * L);

#endif /* _LSTD_H */
