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

void utility_ntocs(const char* nstring, char* cstring, int len)
{
  int i;

  for(i=0; i<len; ++i)
    cstring[i] = nstring[i];

  cstring[len] = '\0';
}

void utility_ctons(char* nstring, const char* cstring, int len)
{
  int i;

  for(i=0; i<len; ++i)
    nstring[i] = cstring[i];
}

void utility_itoa(int i, char * ascii, int maxlen)
{
  snprintf(ascii, maxlen, "%d", i);
}

void utility_ServerCommandLine(int argc, char ** argv, port_t * port, int * maxpending)
{
  int i;

  for(i=0; i<argc; ++i)
    {
      if( port != NULL && !strcmp(argv[i], "--port") )
	{
	  if(i+1 < argc)
	    {
	      if(argv[i+1][0] != '-')
		{
		  ++i;
		  *port = atoi(argv[i]);
		}
	    }
	}

      else if( maxpending != NULL && !strcmp(argv[i], "--maxpending") )
	{
	  if(i+1 < argc)
	    {
	      if(argv[i+1][0] != '-')
		{
		  ++i;
		  *maxpending = atoi(argv[i]);
		}
	    }
	}
    }
}

void utility_ClientCommandLine(int argc, char ** argv, char * host, int maxHostLen, port_t *port, char * data, int maxDataLen)
{
  int i;

  for(i=0; i<argc; ++i)
    {
      if( host != NULL && !strcmp(argv[i], "--host") )
	{
	  if(i+1 < argc)
	    {
	      if(argv[i+1][0] != '-')
		{
		  ++i;
		  strncpy(host, argv[i], maxHostLen);
		}
	    }
	}

      else if( port != NULL && !strcmp(argv[i], "--port") )
	{
	  if(i+1 < argc)
	    {
	      if(argv[i+1][0] != '-')
		{
		  ++i;
		  *port = atoi(argv[i]);
		}
	    }
	}

      else if( data!=NULL && !strcmp(argv[i], "--message") )
	{
	  if(i+1 < argc)
	    {
	      if(argv[i+1][0] != '-')
		{
		  ++i;
		  strncpy( data, argv[i], maxDataLen);
		}
	    }
	}
    }
}

struct static_SocketUtility SocketUtility = {utility_create_sockaddr, utility_getsockaddr, utility_ntocs, utility_ctons, utility_itoa, utility_ServerCommandLine, utility_ClientCommandLine};
