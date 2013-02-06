#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "DatagramSocket.h"
#include "DatagramPacket.h"

int main()
{
  struct DatagramPacket packet;
  struct DatagramSocket socket;
  char * data = "Bonjour";

  if( __DatagramPacket__(&packet,"127.0.0.1", 7777, data, strlen(data)+1) == -1 ) return -1;

  if( __DatagramSocket__(&socket) == -1) return -1;

  sleep(0.01); //on laisse le serveur se lancer

  socket.send(&socket, &packet);

  /* if( socket->send(socket, packet) == -1 ); */
  /* 	{ */
  /* 	  perror("socket->send"); */
  /* 	  packet->delete(packet); */
  /* 	  socket->close(socket); */
  /* 	  exit(-1); */
  /* 	} */

  socket.close(&socket);

  return 0;
}
