#ifndef _ServerSocket
#define _ServerSocket

#include "SocketUtility.h"
#include "StreamSocket.h"

struct ServerSocket
{
  int _descriptor;
  struct sockaddr_in _myaddr;
  struct sockaddr_in _client_addr;
  socklen_t _client_addr_len;

  int (*bind)(struct ServerSocket * _this, port_t listening_port, int max_pending);

  int (*accept)(struct ServerSocket * _this, struct StreamSocket * service_socket);

  int (*close)(struct ServerSocket * _this);

};

int __ServerSocket__(struct ServerSocket * _this);

int lstnsckt_bind(struct ServerSocket * _this, port_t listening_port, int max_pending);

int lstnsckt_accept(struct ServerSocket * _this, struct StreamSocket * service_socket);

int lstnsckt_close(struct ServerSocket * _this);

#endif
