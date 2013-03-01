#include "DatagramPacket.h"

int __DatagramPacket__(struct DatagramPacket * _this, const char * dest_ip, port_t dest_port, char * data, int data_len)
{

  if( SocketUtility.create_sockaddr(&_this->_dest_addr, dest_ip, dest_port) == -1) return -1;

  _this->_dest_addr_len = sizeof(struct sockaddr_in);

  _this->_data = data;

  _this->_data_len = data_len;

  _this->data = dgrm_data;
  _this->dataLength = dgrm_dataLength;
  _this->destAddr = dgrm_destAddr;
  _this->destAddrLength = dgrm_destAddrLength;
  _this->setMessage = dgrm_setMessage;
  _this->setDestination = dgrm_setDestination;
  _this->reset = dgrm_reset;

  return 0;
}

int __Input_DatagramPacket__(struct DatagramPacket * _this, char * data, int expected_len)
{

  if( SocketUtility.create_sockaddr(&_this->_dest_addr, NULL, PORT_ANY) == -1) return -1;

  _this->_dest_addr_len = sizeof(struct sockaddr_in);

  _this->_data = data;

  _this->_data_len = expected_len;

  _this->data = dgrm_data;
  _this->dataLength = dgrm_dataLength;
  _this->destAddr = dgrm_destAddr;
  _this->destAddrLength = dgrm_destAddrLength;
  _this->setMessage = dgrm_setMessage;
  _this->setDestination = dgrm_setDestination;
  _this->reset = dgrm_reset;

  return 0;
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
