#include "DatagramSocket.h"

int __DatagramSocket__(struct DatagramSocket * _this)
{

  _this->_descriptor = socket(AF_INET, SOCK_DGRAM, DEFAULT_PROTOCOL);

  if(_this->_descriptor == -1) return -1;

  else if( SocketUtility.create_sockaddr(&_this->_myaddr, NULL, PORT_ANY) == -1 ) return -1;

  else
    {
      _this->bind = sock_bind;
      _this->send = sock_send;
      _this->receive = sock_receive;
      _this->close = sock_close;

      return 0;
    }
}

int sock_bind(struct DatagramSocket * _this, port_t port)
{
  _this->_myaddr.sin_port = htons(port);

  return bind(_this->_descriptor, (struct sockaddr*)(&_this->_myaddr), sizeof(struct sockaddr_in));
}

int sock_send(struct DatagramSocket * _this, struct DatagramPacket * packet)
{
  return sendto(_this->_descriptor,
		packet->data(packet),
		packet->dataLength(packet),
		NO_OPTION,
		packet->destAddr(packet),
		packet->destAddrLength(packet));
}

int sock_receive(struct DatagramSocket * _this, struct DatagramPacket * packet)
{
  return recvfrom(_this->_descriptor,
		  packet->data(packet),
		  packet->dataLength(packet),
		  NO_OPTION,
		  packet->destAddr(packet),
		  (socklen_t *)(&packet->_dest_addr_len));
}

int sock_close(struct DatagramSocket * _this)
{
  return close(_this->_descriptor);
}
