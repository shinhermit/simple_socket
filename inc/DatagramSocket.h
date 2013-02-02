#ifndef _DatagramSockect
#define _DatagramSockect

#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include "DatagramPacket.h"
#include "SocketUtility.h"

#define DEFAULT_PROTOCOL 0
#define ANY_PORT 0
#define NO_OPTION 0

struct DatagramSocket
{
  int _descriptor;
  struct sockaddr_in _sockaddr;
  socklen_t  _sockaddr_len;

  int (*bind)(struct DatagramSocket * _this, port_t port);

  int (*send)(struct DatagramSocket * _this, struct DatagramPacket * packet);

  int (*receive)(struct DatagramSocket * _this, struct DatagramPacket * packet);

  int (*close)(struct DatagramSocket * _this);
};

struct DatagramSocket * __New_DatagramSocket__(const char* ip);

int sock_bind(struct DatagramSocket * _this, port_t port);

int sock_send(struct DatagramSocket * _this, struct DatagramPacket * packet);

int sock_receive(struct DatagramSocket * _this, struct DatagramPacket * packet);

int sock_close(struct DatagramSocket * _this);

#endif
