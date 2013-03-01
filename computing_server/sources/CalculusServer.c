#include "CalculusServer.h"

int __CalculusServer__(struct CalculusServer * _this, port_t port)
{
  const int max_pending = 5;

  if(__ServerSocket__(&_this->_listener) == -1)
    return -1;

  _this->_listener.bind(&_this->_listener, port, max_pending);

  _this->waitCalculus = serv_waitCalculus;
  _this->_fact = _serv_fact;
  _this->_pow = _serv_pow;
  _this->_stats = _serv_stats;
  _this->finish = serv_finish;

  return 0;
}

int _serv_fact(struct CalculusServer * _this)
{
  int nb;
  long result;

  if( _this->_socket.read( &_this->_socket, (char*)&nb, sizeof(int) ) == -1)
    return -1;

  result = fact(nb);

  if( _this->_socket.write(&_this->_socket, (char*)&result, sizeof(long)) == -1)
    return -1;

  return 0;
}

int _serv_pow(struct CalculusServer * _this)
{
  int nb;
  int puiss;
  long result;

  if( _this->_socket.read( &_this->_socket, (char*)&nb, sizeof(int) ) == -1)
    return -1;

  if( _this->_socket.read( &_this->_socket, (char*)&puiss, sizeof(int) ) == -1)
    return -1;

  result = power(nb, puiss);

  if( _this->_socket.write(&_this->_socket, (char*)&result, sizeof(long)) == -1)
    return -1;

  return 0;
}

int _serv_stats(struct CalculusServer * _this, int param_data_len)
{
  int * numbers;
  struct stat_t results;

  numbers = (int*) malloc(param_data_len);

  if( _this->_socket.read( &_this->_socket, (char*)numbers, param_data_len ) == -1 )
    return -1;

  stats(numbers, (int)(param_data_len/sizeof(int)), &results);

  if( _this->_socket.write(&_this->_socket, (char*)&results, sizeof(struct stat_t) ) == -1)
    return -1;

  free(numbers);

  return 0;
}

int serv_waitCalculus(struct CalculusServer * _this)
{
  short fin;
  struct request_t req;

  if( _this->_listener.accept(&_this->_listener, &_this->_socket) == -1)
    return -1;

  fin = 0;
  while(!fin)
    {
      //récupération des informations sur l'opération demandée
      if( _this->_socket.read( &_this->_socket, (char*)&req, sizeof(struct request_t) ) == -1)
	return -1;

      switch(req.type)
	{
	case END:
	  fin = 1;
	  break;

	case FACTORIAL:
	  _this->_fact(_this);
	  break;

	case POWER:
	  _this->_pow(_this);
	  break;

	case STATS:
	  _this->_stats(_this, req.param_data_len);
	  break;

	default:
	  return -1;
	}

    }

  return 0;
}

int serv_finish(struct CalculusServer * _this)
{
  if( _this->_listener.close(&_this->_listener) == -1 )
    return -1;

  if( _this->_socket.close(&_this->_socket) == -1 )
    return -1;

  return 0;
}
