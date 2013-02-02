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

  addr->sin_port = port;

  addr->sin_family = AF_INET;

  return 0;
}

struct static_SocketUtility SocketUtility = {utility_create_sockaddr};
