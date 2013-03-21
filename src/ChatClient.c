#include "StreamSocket.h"

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv)
{
  char[100] host;
  port_t port;
  char data[MAXLEN];

  int max_len = MAXLEN*sizeof(char);
  int received;
  Bool quit;

  port = 1983;
  strcpy(host,"127.0.0.1");
  SocketUtility.ClientCommandLine(argc, argv, host, 100, &port, data, MAXLEN);

  struct StreamSocket socket;

  if( __StreamSocket__(&socket) == -1 )
    exit(-1);

  if( socket.connect(&socket, host, port) == -1) exit(-1);
  printf("Client: connected\n");

  quit = FALSE;

  while(!quit)
    {
      printf("Moi: ");
      fgets(data, MAXLEN, stdin);

      socket.write(&socket, data, strlen(data));

      received = socket.read(&socket, data, max_len-1);

      SocketUtility.ntocs(data, data, received);

      if( !strcmp(data, "fin.\n") )
	{
	  strcpy(data, "fin.\n");
	  socket.write(&socket, data, strlen(data));
	  quit = TRUE;
	}

      else
	{
	  printf("Lui: %s", data);
	}
    }

  socket.close(&socket);

  return 0;
}
