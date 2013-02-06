#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DatagramSocket.h"
#include "DatagramPacket.h"

int main()
{

  struct DatagramPacket packet;
  struct DatagramSocket socket;

  int expected_len = strlen("Bonjour")+1;
  char * recv_data = (char*) malloc(expected_len);
  if(!recv_data) exit(-1);

  if( __Input_DatagramPacket__(&packet, recv_data, expected_len) == -1 ) return -1;

  if( __DatagramSocket__(&socket) == -1 ) return -1;

  if( socket.bind(&socket, 7777) == -1 )
    {
      perror("socket.bind");
      socket.close(&socket);
      exit(-1);
    }

  socket.receive(&socket, &packet);

  /* if( socket->receive(socket, packet) == -1 ); */
  /* 	{ */
  /* 	  perror("socket->receive"); */
  /* 	  packet->delete(packet); */
  /* 	  socket->close(socket); */
  /* 	  exit(-1); */
  /* 	} */

  printf( "Serveur: reçu message.\nContenu: %s\n", packet.data(&packet) );

  socket.close(&socket);

  free(recv_data);

  return 0;
}
