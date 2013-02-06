#include "StreamSocket.h"

#include <stdlib.h>

int main(int argc, char** argv)
{
  char * ip = "127.0.0.1";
  port_t port = 4000;
  char * data = "Bonjour";

  if(argc > 3)
    {
      ip = argv[1];
      port = atoi(argv[2]);
    }

  struct StreamSocket socket;

  if( __StreamSocket__(&socket) == -1 )
    exit(-1);

  socket.connect(&socket, ip, port);

  socket.write(&socket, data, strlen(data)+1 );

  socket.close(&socket);

  return 0;
}
