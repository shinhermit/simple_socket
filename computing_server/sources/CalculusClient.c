#include "CalculusClient.h"

int __CalculusClient__(struct CalculusClient * _this)
{
  if(__StreamSocket__(&_this->_socket) == -1)
      return -1;

  _this->_buffer = NULL;
  _this->_buffer_offset = 0;

  _this->connect = remote_connect;
  _this->disconnect = remote_disconnect;
  _this->_prepare_buffer = _remote_prepare_buffer;
  _this->_buffer_add = _remote_buffer_add;
  _this->fact = remote_fact;
  _this->stats = remote_stats;
  _this->pow = remote_pow;

  return 0;
}

int remote_connect(struct CalculusClient * _this, const char * ip_serv, port_t port_serv)
{
  if( _this->_socket.connect(&_this->_socket, ip_serv, port_serv) == -1 )
      return -1;    

  return 0;
}

int remote_disconnect(struct CalculusClient * _this)
{
  _this->_prepare_buffer(_this, END, 0);

  if( _this->_socket.write(&_this->_socket, _this->_buffer, _this->_buffer_len) == -1)
      return -1;

  if( _this->_socket.close(&_this->_socket) == -1 )
      return -1;

  if(_this->_buffer)
    {
      free(_this->_buffer);
      _this->_buffer = NULL;
    }

  return 0;    
}

void _remote_prepare_buffer(struct CalculusClient * _this, enum calculus_t calc_type, request_size_t calc_param_len)
{

  struct request_t request;

  request.type = calc_type;

  if(request.param_data_len != calc_param_len)
    {
      _this->_buffer_offset = 0;
      request.param_data_len = calc_param_len;

      _this->_buffer_len = sizeof(struct request_t) + calc_param_len;

      _this->_buffer = (char*) realloc(_this->_buffer, _this->_buffer_len);

      memcpy( _this->_buffer, &request, sizeof(struct request_t) );
    }

  _this->_buffer_offset += sizeof(struct request_t);
  
}

void _remote_buffer_add(struct CalculusClient * _this, const void * data, int data_len)
{
  memcpy( _this->_buffer + _this->_buffer_offset, data, data_len);

  _this->_buffer_offset += data_len;
}

long remote_fact(struct CalculusClient * _this, int nb)
{
  long result;

  _this->_prepare_buffer(_this, FACTORIAL, sizeof(int) );

  _this->_buffer_add(_this, &nb, sizeof(int) );

  if( _this->_socket.write(&_this->_socket, _this->_buffer, _this->_buffer_len) == -1)
      return -1;

  if( _this->_socket.read( &_this->_socket, (char*)&result, sizeof(long)) == -1 )
    return -1;

  return result;
}

long remote_pow(struct CalculusClient * _this, int nb, int puiss)
{
  long result;

  _this->_prepare_buffer( _this, POWER, 2*sizeof(int) );

  _this->_buffer_add( _this, &nb, sizeof(int) );

  _this->_buffer_add( _this, &puiss, sizeof(int) );

  if( _this->_socket.write(&_this->_socket, _this->_buffer, _this->_buffer_len) == -1)
      return -1;

  if( _this->_socket.read( &_this->_socket, (char*)&result, sizeof(long) ) == -1 )
    return -1;

  return result;
}

int remote_stats(struct CalculusClient * _this, int * numbers, int nb_numbers, struct stat_t *results)
{

  _this->_prepare_buffer( _this, STATS, nb_numbers*sizeof(int) );

  _this->_buffer_add( _this, numbers, nb_numbers*sizeof(int) );

  if( _this->_socket.write(&_this->_socket, _this->_buffer, _this->_buffer_len) == -1)
      return -1;

  if( _this->_socket.read( &_this->_socket, (char*)results, sizeof(struct stat_t) ) == -1 )
    return -1;

  return 0;
}

