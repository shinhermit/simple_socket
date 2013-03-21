#include "ServerSocket.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{
  struct ServerSocket listener;
  struct StreamSocket socket;

  port_t port;
  int max_pending;
  char data[MAXLEN];
  int nb_recv;

  port = 1983;
  max_pending = 5;
  SocketUtility.ServerCommandLine(argc, argv, &port, &max_pending);

  if( __ServerSocket__(&listener) == -1 )
    exit(-1);

  listener.bind(&listener, port, max_pending);

  listener.accept(&listener, &socket);

  nb_recv = socket.read(&socket, data, MAXLEN-1);

  SocketUtility.ntocs(data, data, nb_recv);

  printf("Serveur: recu message\n.Contenu: %s\n", data);

  socket.close(&socket);

  return 0;
}
