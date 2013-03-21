#include "StreamSocket.h"

#include <stdlib.h>

int main(int argc, char** argv)
{
  port_t port;
  char host[100];
  char data[MAXLEN];

  port = 1983;
  strcpy(host,"127.0.0.1");
  strcpy(data,"bonjour");
  SocketUtility.ClientCommandLine(argc, argv, host, 100, &port, data, MAXLEN);

  struct StreamSocket socket;

  if( __StreamSocket__(&socket) == -1 )
    exit(-1);

  socket.connect(&socket, host, port);

  socket.write( &socket, data, strlen(data) );

  socket.close(&socket);

  return 0;
}
