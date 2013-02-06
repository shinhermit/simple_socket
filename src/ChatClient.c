#include "StreamSocket.h"

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv)
{
  char * ip = "127.0.0.1";
  port_t port = 4000;
  int max_len = MAXLEN*sizeof(char);
  int received;
  char data[MAXLEN];
  Bool quit;

  if(argc > 3)
    {
      ip = argv[1];
      port = atoi(argv[2]);
    }

  struct StreamSocket socket;

  if( __StreamSocket__(&socket) == -1 )
    exit(-1);

  if( socket.connect(&socket, ip, port) == -1) exit(-1);
  printf("Client: connected\n");

  quit = FALSE;

  while(!quit)
    {
      printf("Moi: ");
      fgets(data, MAXLEN, stdin);

      socket.write(&socket, data, strlen(data));

      received = socket.read(&socket, data, max_len-1);

      data[received] = '\0';

      if( !strcmp(data, "fin\n") )
	{
	  strcpy(data, "fin\n");
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
