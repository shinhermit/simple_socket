#ifndef _CalculusServer
#define _CalculusServer

#include <stdio.h>
#include "ServerSocket.h"
#include "calculus.h"
#include "request.h" //pour enum calculus_t

struct CalculusServer
{
  struct ServerSocket _listener;
  struct StreamSocket _socket;

  int (*_fact)(struct CalculusServer * _this);

  int (*_pow)(struct CalculusServer * _this);

  int (*_stats)(struct CalculusServer * _this, int param_data_len);

  int (*waitCalculus)(struct CalculusServer * _this);

  int (*finish)(struct CalculusServer * _this);
};

int __CalculusServer__(struct CalculusServer * _this, port_t port);

int _serv_fact(struct CalculusServer * _this);

int _serv_pow(struct CalculusServer * _this);

int _serv_stats(struct CalculusServer * _this, int param_data_len);

int serv_waitCalculus(struct CalculusServer * _this);

int serv_finish(struct CalculusServer * _this);

#endif
