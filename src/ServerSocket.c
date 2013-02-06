#include "ServerSocket.h"

int __ServerSocket__(struct ServerSocket * _this)
{
  _this->_descriptor = socket(AF_INET, SOCK_STREAM, DEFAULT_PROTOCOL);

  if(_this->_descriptor == -1) return -1;

  else if( SocketUtility.create_sockaddr(&_this->_myaddr, NULL, ANY_PORT) == -1 ) return -1;

  else if( SocketUtility.create_sockaddr(&_this->_client_addr, NULL, ANY_PORT) == -1 ) return -1;

  else
    {
      _this->bind = lstnsckt_bind;
      _this->accept = lstnsckt_accept;
      _this->close = lstnsckt_close;

      return 0;
    }

}

int lstnsckt_bind(struct ServerSocket * _this, port_t listening_port, int max_pending)
{
  _this->_myaddr.sin_port = listening_port;

  if( bind(_this->_descriptor, (struct sockaddr*)(&_this->_myaddr), sizeof(struct sockaddr_in)) == -1 )
    return -1;

  else
    {
      return listen(_this->_descriptor, max_pending);
    }
}

int lstnsckt_accept(struct ServerSocket * _this, struct StreamSocket * service_socket)
{
  int fd;

  fd = accept(_this->_descriptor, (struct sockaddr *)&_this->_client_addr, &_this->_client_addr_len);

  if(fd == -1) return -1;

  else
    {
      return __StreamSocket_from_fd__(service_socket, fd);
    }
}

int lstnsckt_close(struct ServerSocket * _this)
{
  return close(_this->_descriptor);
}
