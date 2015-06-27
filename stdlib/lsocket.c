
#include <sys/types.h>
#include <sys/socket.h>

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
}

/*
 * lsocket.bind(sockfd, ipaddr, port)
 */
static int lsocket_bind(lua_State *L)
{
}

/*
 * lsocket.connect(sockfd, ipaddr, port)
 */
static int lsocket_connect(lua_State *L)
{
}

/*
 * lsocket.listen(sockfd, backlog)
 */
static int lsocket_listen(lua_State *L)
{
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
