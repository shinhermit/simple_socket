#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "DatagramSocket.h"
#include "DatagramPacket.h"

int main(int argc, char ** argv)
{
  struct DatagramPacket packet;
  struct DatagramSocket socket;
  port_t port;
  char host[100];
  char data[MAXLEN];

  port = 1983;
  strcpy(host,"127.0.0.1");
  strcpy(data,"bonjour");
  SocketUtility.ClientCommandLine(argc, argv, host, 100, &port, data, MAXLEN);

  if( __DatagramPacket__(&packet, host, port, data, strlen(data)) == -1 ) return -1;

  if( __DatagramSocket__(&socket) == -1) return -1;

  sleep(0.01); //on laisse le serveur se lancer

  if( socket.send(&socket, &packet) == -1 )
    {
      perror("socket.send");
      socket.close(&socket);
      exit(-1);
    }

  socket.close(&socket);

  return 0;
}
