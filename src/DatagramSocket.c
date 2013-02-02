#include "DatagramSocket.h"

struct DatagramSocket * __New_DatagramSocket__(const char* ip)
{
  struct DatagramSocket * _this = (struct DatagramSocket *) malloc( sizeof(struct DatagramSocket) );

  if(_this == NULL) return NULL; //echec malloc

  _this->_descriptor = socket(AF_INET, SOCK_DGRAM, DEFAULT_PROTOCOL);

  if( SocketUtility.create_sockaddr(&_this->_sockaddr, ip, ANY_PORT) == -1 ) return NULL;

  _this->_sockaddr_len = sizeof(_this->_sockaddr); //erreur ??

  if(_this->_descriptor == -1)
    {
      free(_this);
      _this = NULL;

      return NULL;
    }
  
  else
    {
      _this->bind = sock_bind;
      _this->send = sock_send;
      _this->receive = sock_receive;
      _this->close = sock_close;

      return _this;
    }
}

int sock_bind(struct DatagramSocket * _this, port_t port)
{
  if(port != ANY_PORT)
    {
      _this->_sockaddr.sin_port = port; //attention, _sockaddr n'est pas de type sockaddr_in
    }

  return bind(_this->_descriptor, (struct sockaddr*)(&_this->_sockaddr), _this->_sockaddr_len);
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
  int ret = close(_this->_descriptor);

  if(ret != -1 )
    {
      free(_this);

      _this = NULL;
    }

  return ret;
}
