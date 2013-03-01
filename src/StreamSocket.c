#include "StreamSocket.h"

int __StreamSocket__(struct StreamSocket * _this)
{
  _this->_descriptor = socket(AF_INET, SOCK_STREAM, DEFAULT_PROTOCOL);

  if(_this->_descriptor == -1) return -1;

  else if( SocketUtility.create_sockaddr(&_this->_server_addr, NULL, PORT_ANY) == -1 ) return -1;

  else
    {
      _this->connect = strmsckt_connect;
      _this->connect_by_name = strmsckt_connect_by_name;
      _this->write = strmsckt_write;
      _this->read = strmsckt_read;
      _this->read_until = strmsckt_read_until;
      _this->close = strmsckt_close;

      return 0;
    }

}

int __StreamSocket_from_fd__(struct StreamSocket * _this, int fd)
{
  _this->_descriptor = fd;

  if(_this->_descriptor == -1) return -1;

  else if( SocketUtility.create_sockaddr(&_this->_server_addr, NULL, PORT_ANY) == -1 ) return -1;

  else
    {
      _this->connect = strmsckt_connect;
      _this->connect_by_name = strmsckt_connect_by_name;
      _this->write = strmsckt_write;
      _this->read = strmsckt_read;
      _this->close = strmsckt_close;

      return 0;
    }

}

int strmsckt_connect(struct StreamSocket * _this, const char * dest_ip, port_t dest_port)
{
  if( SocketUtility.create_sockaddr(&_this->_server_addr, dest_ip, dest_port) == -1) return -1;

  else
    {
      return connect(_this->_descriptor, (struct sockaddr *)&_this->_server_addr, sizeof(struct sockaddr_in));
    }
}

int strmsckt_connect_by_name(struct StreamSocket * _this, const char * servname, port_t port)
{
  if( SocketUtility.getsockaddr(&_this->_server_addr, servname, port) == -1) return -1;

  else
    {
      return connect(_this->_descriptor, (struct sockaddr *)&_this->_server_addr, sizeof(struct sockaddr_in));
    }
}

int strmsckt_write(struct StreamSocket * _this, char * data, int data_len)
{
  return write(_this->_descriptor, data, data_len);
}

int strmsckt_read(struct StreamSocket * _this, char * data, int data_len)
{
  return read(_this->_descriptor, data, data_len);
}

int strmsckt_read_until(struct StreamSocket * _this, char * data, int until_len)
{
  int nb_remain;
  int nb_recv;
  int offset;

  printf("StreamSocket::strmsckt_read_until: begenning\n");
  nb_remain = until_len;
  offset = 0;
  while(nb_remain > 0)
    {
      nb_recv = read(_this->_descriptor, data+offset, nb_remain);

      if(nb_recv == -1)
  	return -1;

      printf("StreamSocket::strmsckt_read_until: received %d bits\n", nb_recv);

      offset += nb_recv;
      nb_remain -= nb_recv;
    }

  return 0;
}

int strmsckt_close(struct StreamSocket * _this)
{
  return close(_this->_descriptor);
}
