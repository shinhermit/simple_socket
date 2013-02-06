#include "ServerSocket.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char ** argv)
{
  struct ServerSocket listener;
  struct StreamSocket socket;

  port_t port = 4000;
  int max_pending = 5;
  int max_len = MAXLEN*sizeof(char);
  int received;
  char data[MAXLEN];
  Bool quit;

  if(argc > 3)
    {
      port = atoi(argv[1]);
      max_pending = atoi(argv[2]);
    }

  if( __ServerSocket__(&listener) == -1 )
    exit(-1);

  listener.bind(&listener, port, max_pending);

  if( listener.accept(&listener, &socket) == -1) exit(-1);

  printf("Serveur: connected\n");

  switch( fork() )
    {
    case -1:
      perror("fork");
      exit(-1);
    case 0:
      quit = FALSE;

      while(!quit)
	{
	  received = socket.read(&socket, data, max_len-1);

	  data[received] = '\0';

	  if( !strcmp(data, "fin.\n") )
	    {
	      strcpy(data, "fin.\n");
	      socket.write(&socket, data, strlen(data));
	      quit = TRUE;
	    }

	  else
	    {
	      printf("Lui: %s\n", data);
	      printf("Moi: ");

	      fgets(data, MAXLEN, stdin);

	      socket.write(&socket, data, strlen(data));
	    }

	}
      break;

    default:
      wait(NULL);
      socket.close(&socket);
      listener.close(&listener);
      break;
    }

  return 0;
}
