#include "ServerSocket.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{
  struct ServerSocket listener;
  struct StreamSocket socket;

  port_t port = 4000;
  int max_pending = 5;
  int max_len = 20*sizeof(char);
  char * data = (char *) malloc(max_len);

  if(argc > 3)
    {
      port = atoi(argv[1]);
      max_pending = atoi(argv[2]);
    }

  if( __ServerSocket__(&listener) == -1 )
    exit(-1);

  listener.bind(&listener, port, max_pending);

  listener.accept(&listener, &socket);

  socket.read(&socket, data, max_len);

  printf("Serveur: recu message\n.Contenu: %s\n", data);

  socket.close(&socket);

  free(data);

  return 0;
}
