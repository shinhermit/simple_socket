#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DatagramSocket.h"
#include "DatagramPacket.h"

int main()
{
  int expected_len = strlen("Bonjour")+1;
  char * recv_data = (char*) malloc(expected_len);
  if(!recv_data) exit(-1);

  struct DatagramPacket * packet = __New_Input_DatagramPacket__(recv_data, expected_len);

  struct DatagramSocket * socket = __New_DatagramSocket__("127.0.0.1");

  if(packet && socket)
    {
      if( socket->bind(socket, 7777) == -1 )
	{
	  perror("socket->bind");
	  packet->delete(packet);
	  socket->close(socket);
	  exit(-1);
	}

      socket->receive(socket, packet);

      /* if( socket->receive(socket, packet) == -1 ); */
      /* 	{ */
      /* 	  perror("socket->receive"); */
      /* 	  packet->delete(packet); */
      /* 	  socket->close(socket); */
      /* 	  exit(-1); */
      /* 	} */

      printf( "Serveur: reçu message.\nContenu: %s\n", packet->data(packet) );

      packet->delete(packet);
      socket->close(socket);
    }

  else
    {
      fprintf(stderr, "Echec allocation dynamique.");
      exit(-1);
    }

  free(recv_data);

  return 0;
}
