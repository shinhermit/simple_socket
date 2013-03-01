#ifndef _CalculusClient
#define _CalculusClient

#include "StreamSocket.h"
#include "calculus.h" //pour struct stat_t
#include "request.h" //pour enum calculus_t
#include <string.h>

struct CalculusClient
{
  struct StreamSocket _socket;

  char * _buffer;

  int _buffer_len;

  int _buffer_offset;

  int (*connect)(struct CalculusClient * _this, const char * ip, port_t port);

  int (*disconnect)(struct CalculusClient * _this);

  void (*_prepare_buffer)(struct CalculusClient * _this, enum calculus_t calc_type, request_size_t calc_param_len);

  void (*_buffer_add)(struct CalculusClient * _this, const void * data, int data_len);

  long (*fact)(struct CalculusClient * _this, int nb);

  long (*pow)(struct CalculusClient * _this, int nb, int puiss);

  int (*stats)(struct CalculusClient * _this, int * numbers, int nb_numbers, struct stat_t *results);

};

int __CalculusClient__(struct CalculusClient * _this);

int remote_connect(struct CalculusClient * _this, const char * ip_serv, port_t port_serv);

int remote_disconnect(struct CalculusClient * _this);

void _remote_prepare_buffer(struct CalculusClient * _this, enum calculus_t calc_type, request_size_t calc_param_len);

void _remote_buffer_add(struct CalculusClient * _this, const void * data, int data_len);

long remote_fact(struct CalculusClient * _this, int nb);

long remote_pow(struct CalculusClient * _this, int nb, int puiss);

int remote_stats(struct CalculusClient * _this, int * numbers, int nb_numbers, struct stat_t *results);

#endif
