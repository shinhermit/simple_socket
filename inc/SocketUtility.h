#ifndef _SocketUtility
#define _SocketUtility

#ifndef _BSD_SOURCE
#define _BSD_SOURCE
#endif

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h> //memset

#define DEFAULT_PROTOCOL 0
#define PORT_ANY 0
#define SOCK_TYPE_ANY 0
#define NO_OPTION 0
#define NO_FLAG 0

#define MAXLEN 200

typedef u_short port_t;

typedef enum{FALSE, TRUE} Bool;

struct static_SocketUtility
{
  int (*create_sockaddr)(struct sockaddr_in * addr, const char * ip, port_t port);

  int (*getsockaddr)(struct sockaddr_in * addr, const char * node, port_t port);
};

int utility_create_sockaddr(struct sockaddr_in * addr, const char * ip, port_t port);

int utility_getsockaddr(struct sockaddr_in * addr, const char * node, port_t port);

struct static_SocketUtility SocketUtility;

#endif
