
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#include "lstd.h"

/*
 * err, fd = lsocket.socket(domain, type, protocol)
 * @domain AF_XX family
 * @type	SOCK_XX family
 * @protocol: 
 * if err == 0 return fd, else return errno 
 */
static int lsocket_socket(lua_State *L)
{
	lstd_checknargs(L, 3);
	int domain = luaL_checkint(L, 1);
	int type = luaL_checkint(L, 2);
	int protocol = luaL_checkint(L, 3);
	int fd = socket(domain, type, protocol);
	if (fd > 0) {
		lua_pushnumber(L, 0);
		lua_pushnumber(L, fd);
	} else {
		lua_pushnumber(L, errno);
		lua_pushnil(L);
	}
	return 2;
}

/*
 * err = lsocket.bind(sockfd, ipaddr, port)
 */
static int lsocket_bind(lua_State *L)
{
	struct sockaddr_in sa;
	struct in_addr addr;
	
	lstd_checknargs(L, 3);
	int fd = luaL_checkint(L, 1);
	const char *s = luaL_checkstring(L, 2);
	uint16_t port = luaL_checkint(L, 3);
	
	bzero(&sa, sizeof(sa));
	int res = inet_aton(s, &addr);
	if (res) {
		sa.sin_family = AF_INET;
		sa.sin_port = htons(port);
		sa.sin_addr.s_addr = htonl(addr.s_addr);
		int err = bind(fd, (struct sockaddr *)&sa, sizeof(struct sockaddr));
		lua_pushnumber(L, err? errno: 0);
	} else {
		luaL_error(L, "%s\n", "invalid ip address");
	}
	return 1;
}

/*
 * err = lsocket.connect(sockfd, ipaddr, port)
 */
static int lsocket_connect(lua_State *L)
{
	struct sockaddr_in sa;
	struct in_addr addr;
	
	lstd_checknargs(L, 3);
	int fd = luaL_checkint(L, 1);
	const char *s = luaL_checkstring(L, 2);
	uint16_t port = luaL_checkint(L, 3);
	
	int res = inet_aton(s, &addr);
	if (res) {
		sa.sin_family = AF_INET;
		sa.sin_port = htons(port);
		sa.sin_addr.s_addr = htonl(addr.s_addr);
		int err = connect(fd, (struct sockaddr *)&sa, sizeof(struct sockaddr));
		lua_pushnumber(L, err? errno: 0);
	} else {
		lua_pushnumber(L, errno);
	}
	return 1;
}

/*
 * err = lsocket.listen(sockfd, backlog)
 */
static int lsocket_listen(lua_State *L)
{
	lstd_checknargs(L, 2);
	int fd = luaL_checkint(L, 1);
	int backlog = luaL_checkint(L, 2);
	int err = listen(fd, backlog);
	lua_pushnumber(L, err? errno: 0);
	return 1;
}


static void lsocket_const_register(lua_State *L)
{
	/* domain */
	LENUMS(AF_UNIX);	/* unix */
	LENUMS(AF_INET);	/* IPv4 */
	LENUMS(AF_INET6);	/* IPv6 */
	
	/* type */
	LENUMS(SOCK_STREAM);	
	LENUMS(SOCK_DGRAM);	
	LENUMS(SOCK_RAW);	
}

static const struct luaL_Reg socket_funcs[] = {
	{"socket", 		lsocket_socket},
	{"bind", 		lsocket_bind},
	{"coneect", 	lsocket_connect},
	{"listen", 		lsocket_listen},
	//{"accept", 	lsocket_accept},
	//{"send", 		lsocket_send},
	//{"recv", 		lsocket_recv},
	//{"sendto", 	lsocket_sendto},
	//{"recvfrom", 	lsocket_recvfrom},
	//{"close", 	lsocket_close},
	//{"shutdown", 	lsocket_shutdown},
	//{"setsockopt",lsocket_setsockopt},
	//{"getsockopt",lsocket_getsockopt},
    {NULL,       	NULL},
};

int lstd_opensocket(lua_State *L)
{
    luaL_register(L, "socket", socket_funcs);
	lsocket_const_register(L);
    return 0;
}
