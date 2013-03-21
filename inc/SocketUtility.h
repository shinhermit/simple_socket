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
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_PROTOCOL 0
#define PORT_ANY 0
#define SOCK_TYPE_ANY 0
#define NO_OPTION 0
#define NO_FLAG 0

#define MAXLEN 512

typedef u_short port_t;

typedef enum{FALSE, TRUE} Bool;

struct static_SocketUtility
{
  int (*create_sockaddr)(struct sockaddr_in * addr, const char * ip, port_t port);

  int (*getsockaddr)(struct sockaddr_in * addr, const char * node, port_t port);

  void (*ntocs)(const char* nstring, char* cstring, int len);

  void (*ctons)(char* nstring, const char* cstring, int len);

  void (*itoa)(int i, char * ascii, int maxlen);

  void (*ServerCommandLine)(int argc, char ** argv, port_t * port, int * maxpending);

  void (*ClientCommandLine)(int argc, char ** argv, char * host, int maxHostLen, port_t *port, char * data, int maxDataLen);
};

int utility_create_sockaddr(struct sockaddr_in * addr, const char * ip, port_t port);

int utility_getsockaddr(struct sockaddr_in * addr, const char * node, port_t port);

void utility_ntocs(const char* nstring, char* cstring, int len);

void utility_ctons(char* nstring, const char* cstring, int len);

void utility_itoa(int i, char * ascii, int maxlen);

void utility_ServerCommandLine(int argc, char ** argv, port_t * port, int * maxpending);

void utility_ClientCommandLine(int argc, char ** argv, char * host, int maxHostLen, port_t *port, char * data, int maxDataLen);

struct static_SocketUtility SocketUtility;

#endif
