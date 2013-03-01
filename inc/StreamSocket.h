#ifndef _StreamSocket
#define _StreamSocket

#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "SocketUtility.h"

struct StreamSocket
{
  int _descriptor;
  struct sockaddr_in _server_addr;

  int (*connect)(struct StreamSocket * _this, const char * ip, port_t port);

  int (*connect_by_name)(struct StreamSocket * _this, const char * name, port_t port);

  int (*write)(struct StreamSocket * _this, char * data, int data_len);

  int (*read)(struct StreamSocket * _this, char * data, int data_len);

  int (*read_until)(struct StreamSocket * _this, char * data, int data_len);

  int (*close)(struct StreamSocket * _this);
  
};

int __StreamSocket__(struct StreamSocket * _this);

int __StreamSocket_from_fd__(struct StreamSocket * _this, int fd);

int strmsckt_connect(struct StreamSocket * _this, const char * ip, port_t port);

int strmsckt_connect_by_name(struct StreamSocket * _this, const char * name, port_t port);

int strmsckt_write(struct StreamSocket * _this, char * data, int data_len);

int strmsckt_read(struct StreamSocket * _this, char * data, int data_len);

int strmsckt_read_until(struct StreamSocket * _this, char * data, int until_len);

int strmsckt_close(struct StreamSocket * _this);

#endif
