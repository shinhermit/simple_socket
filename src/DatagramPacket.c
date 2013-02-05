#include "DatagramPacket.h"

struct DatagramPacket * __New_DatagramPacket__(const char * dest_ip, port_t dest_port, char * data, int data_len)
{
  struct DatagramPacket * packet = (struct DatagramPacket *) malloc( sizeof(struct DatagramPacket) );

  if(packet == NULL) return NULL;

  if( SocketUtility.create_sockaddr(&packet->_dest_addr, dest_ip, dest_port) == -1) return NULL;

  packet->_dest_addr_len = sizeof(struct sockaddr_in);

  packet->_data = data;

  packet->_data_len = data_len;

  packet->data = dgrm_data;
  packet->dataLength = dgrm_dataLength;
  packet->destAddr = dgrm_destAddr;
  packet->destAddrLength = dgrm_destAddrLength;
  packet->setMessage = dgrm_setMessage;
  packet->setDestination = dgrm_setDestination;
  packet->reset = dgrm_reset;
  packet->delete = dgrm_delete;

  return packet;
}

struct DatagramPacket * __New_Input_DatagramPacket__(char * data, int expected_len)
{
  struct DatagramPacket * packet = (struct DatagramPacket *) malloc( sizeof(struct DatagramPacket) );

  if(packet == NULL) return NULL;

  if( SocketUtility.create_sockaddr(&packet->_dest_addr, NULL, ANY_PORT) == -1) return NULL;

  packet->_dest_addr_len = sizeof(struct sockaddr_in);

  packet->_data = data;

  packet->_data_len = expected_len;

  packet->data = dgrm_data;
  packet->dataLength = dgrm_dataLength;
  packet->destAddr = dgrm_destAddr;
  packet->destAddrLength = dgrm_destAddrLength;
  packet->setMessage = dgrm_setMessage;
  packet->setDestination = dgrm_setDestination;
  packet->reset = dgrm_reset;
  packet->delete = dgrm_delete;

  return packet;
}

char * dgrm_data(struct DatagramPacket * _this)
{
  return _this->_data;
}

int dgrm_dataLength(struct DatagramPacket * _this)
{
  return _this->_data_len;
}

struct sockaddr * dgrm_destAddr(struct DatagramPacket * _this)
{
  return (struct sockaddr*)(&_this->_dest_addr);
}

int dgrm_destAddrLength(struct DatagramPacket * _this)
{
  return _this->_dest_addr_len;
}

void dgrm_setMessage(struct DatagramPacket * _this, char * data, int length)
{
  _this->_data = data;
  _this->_data_len = length;
}

int dgrm_setDestination(struct DatagramPacket * _this, const char * dest_ip, port_t dest_port)
{
  return SocketUtility.create_sockaddr(&_this->_dest_addr, dest_ip, dest_port);
}

int dgrm_reset(struct DatagramPacket * _this, const char * dest_ip, port_t dest_port, char * data, int data_len)
{
  _this->_data = data;
  _this->_data_len = data_len;

  return SocketUtility.create_sockaddr(&_this->_dest_addr, dest_ip, dest_port);
}

void dgrm_delete(struct DatagramPacket * _this)
{
  free(_this);

  _this = NULL;
}
