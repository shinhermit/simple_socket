#include "SocketUtility.h"

int utility_create_sockaddr(struct sockaddr_in * addr, const char * ip, port_t port)
{

  memset( addr, 0, sizeof(struct sockaddr_in) );

  if(ip != NULL)
    {
      if( inet_aton(ip, & addr->sin_addr) == -1 ) return -1;
    }

  else
    {
      addr->sin_addr.s_addr = INADDR_ANY;
    }

  addr->sin_port = htons(port);

  addr->sin_family = AF_INET;

  return 0;
}

int utility_getsockaddr(struct sockaddr_in * addr, const char * node, port_t port)
{
  struct addrinfo hints = {NO_FLAG, AF_INET, SOCK_TYPE_ANY, DEFAULT_PROTOCOL, 0, NULL, NULL, NULL};
  struct addrinfo * res;

  if( getaddrinfo(node, NULL, &hints, &res) == -1 ) return -1;

  if(res == NULL) return -1;

  else
    {
      memcpy(addr, res->ai_addr, res->ai_addrlen);

      addr->sin_port = htons(port);

      freeaddrinfo(res);

      return 0;
    }
}

struct static_SocketUtility SocketUtility = {utility_create_sockaddr, utility_getsockaddr};
