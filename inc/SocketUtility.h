#ifndef _SocketUtility
#define _SocketUtility

#ifndef _BSD_SOURCE
#define _BSD_SOURCE
#endif

#include <arpa/inet.h>
#include <string.h> //memset

#define DEFAULT_PROTOCOL 0
#define ANY_PORT 0
#define NO_OPTION 0

#define MAXLEN 200

typedef u_short port_t;

typedef enum{FALSE, TRUE} Bool;

struct static_SocketUtility
{
  int (*create_sockaddr)(struct sockaddr_in * addr, const char * ip, port_t port);
};

int utility_create_sockaddr(struct sockaddr_in * addr, const char * ip, port_t port);

struct static_SocketUtility SocketUtility;

#endif
