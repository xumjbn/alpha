
#ifndef _LSTD_H
#define _LSTD_H

#include <string.h>

#include "lualib.h"
#include "lauxlib.h"


#define UNUSED(x) (void)x 

#define LENUMS(n) \
    do {\
        lua_pushinteger(L, n);\
        lua_setfield(L, -2, #n);\
    } while (0)

#define LERR_NUMS(n)    LENUMS(n)   

#define MALLOC(size)    malloc(size)
#define RALLOC(size)    ralloc(size)
#define FREE(p)         free(p)




void lstd_checknargs(lua_State *L, int maxargs);

void lstd_rawsetnumber(lua_State *L, const char *key, int value);
int  lstd_rawgetnumber(lua_State *L, const char *key);
void lstd_rawsetstring(lua_State *L, const char *key, const char *value);

const char *lstd_rawgetistring(lua_State *L, int key);

void lstd_stackdump(lua_State *L);



/* stdlib api */
int lstd_openos(lua_State *L);
int lstd_openfs(lua_State *L);
int lstd_opentime(lua_State *L);
int lstd_openerr(lua_State *L);
int lstd_openopt(lua_State *L);
int lstd_openarr(lua_State *L);
int lstd_opensocket(lua_State *L);
int lstd_opensyslog(lua_State *L);
int lstd_opensignal(lua_State *L);

#endif /* _LSTD_H */

