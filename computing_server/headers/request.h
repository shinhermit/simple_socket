#ifndef _request
#define _request

enum calculus_t
  {
    END = 0,
    FACTORIAL,
    POWER,
    STATS
  };

typedef int request_size_t;

struct request_t
{
  enum calculus_t type;
  request_size_t param_data_len;
};

#endif
