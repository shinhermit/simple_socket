#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DatagramSocket.h"
#include "DatagramPacket.h"

int main(int argc, char ** argv)
{

  struct DatagramPacket packet;
  struct DatagramSocket socket;
  port_t port;

  char recv_data[MAXLEN];
  int nb_recv;

  port = 1983;
  SocketUtility.ServerCommandLine(argc, argv, &port, NULL);

  if( __Input_DatagramPacket__(&packet, recv_data, MAXLEN-1) ) return -1;

  if( __DatagramSocket__(&socket) == -1 ) return -1;

  if( socket.bind(&socket, port) == -1 )
    {
      perror("socket.bind");
      socket.close(&socket);
      exit(-1);
    }

  nb_recv = socket.receive(&socket, &packet);
  if( nb_recv == -1 )
    {
      perror("socket.receive");
      socket.close(&socket);
      exit(-1);
    }

  SocketUtility.ntocs(packet.data(&packet), packet.data(&packet), nb_recv);

  printf( "Serveur: reçu message.\nContenu: %s\n", packet.data(&packet) );

  socket.close(&socket);

  return 0;
}
