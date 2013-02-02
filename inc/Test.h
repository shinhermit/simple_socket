#ifndef _Test
#define _Test

struct Test
{
  char * _mess;
  char * _author;

  void (*print)(struct Test * _this);
};

void __Test__(struct Test * _this, const char * mess, const char * author);

void print(struct Test * _this);

#endif
