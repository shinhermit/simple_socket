#ifndef _DatagramPacket
#define _DatagramPacket

#include <sys/socket.h>
#include <stdlib.h>
#include "SocketUtility.h"

struct DatagramPacket
{
  struct sockaddr_in _dest_addr;
  int _dest_addr_len;
  char * _data;
  int _data_len;

  char * (*data)(struct DatagramPacket * _this);

  int (*dataLength)(struct DatagramPacket * _this);

  struct sockaddr * (*destAddr)(struct DatagramPacket * _this);

  int (*destAddrLength)(struct DatagramPacket * _this);

  void (*setMessage)(struct DatagramPacket * _this, char * buf, int length);

  int (*setDestination)(struct DatagramPacket * _this, const char * dest_ip, port_t dest_port);

  int (*reset)(struct DatagramPacket * _this, const char * dest_ip, port_t dest_port, char * data, int data_len);
};

int __DatagramPacket__(struct DatagramPacket * _this, const char * dest_ip, port_t dest_port, char * data, int data_len);

int __Input_DatagramPacket__(struct DatagramPacket * _this, char * data, int expected_len);

char * dgrm_data(struct DatagramPacket * _this);

int dgrm_dataLength(struct DatagramPacket * _this);

struct sockaddr * dgrm_destAddr(struct DatagramPacket * _this);

int dgrm_destAddrLength(struct DatagramPacket * _this);

void dgrm_setMessage(struct DatagramPacket * _this, char * buf, int length);

int dgrm_setDestination(struct DatagramPacket * _this, const char * dest_ip, port_t dest_port);

int dgrm_reset(struct DatagramPacket * _this, const char * dest_ip, port_t dest_port, char * data, int data_len);

#endif
