#ifndef _SocketUtility
#define _SocketUtility

#ifndef _BSD_SOURCE
#define _BSD_SOURCE
#endif

#include <arpa/inet.h>
#include <string.h> //memset

typedef u_short port_t;

struct static_SocketUtility
{
  int (*create_sockaddr)(struct sockaddr_in * addr, const char * ip, port_t port);
};

int utility_create_sockaddr(struct sockaddr_in * addr, const char * ip, port_t port);

struct static_SocketUtility SocketUtility;

#endif
