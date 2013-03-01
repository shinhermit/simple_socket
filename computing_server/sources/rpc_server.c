#include "CalculusServer.h"

int main()
{
  struct CalculusServer server;

  if( __CalculusServer__(&server, 4000) == -1 )
    return -1;

  server.waitCalculus(&server);

  server.finish(&server);

  return 0;
}
