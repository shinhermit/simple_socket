#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "DatagramSocket.h"
#include "DatagramPacket.h"

int main()
{
  char * data = "Bonjour";

  struct DatagramPacket * packet = __New_DatagramPacket__("127.0.0.1", 7777, data, strlen(data)+1);

  struct DatagramSocket * socket = __New_DatagramSocket__();

  if(packet && socket)
    {
      sleep(0.01); //on laisse le serveur se lancer

      socket->send(socket, packet);

      /* if( socket->send(socket, packet) == -1 ); */
      /* 	{ */
      /* 	  perror("socket->send"); */
      /* 	  packet->delete(packet); */
      /* 	  socket->close(socket); */
      /* 	  exit(-1); */
      /* 	} */

      packet->delete(packet);
      socket->close(socket);
    }

  else
    {
      fprintf(stderr, "Echec allocations dynamiques.");
      exit(-1);
    }
  return 0;
}
