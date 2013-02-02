#include <stdio.h>
#include "Test.h"

void __Test__(struct Test * _this, const char * mess, const char * author)
{
  _this->_mess = mess;
  _this->_author = author;

  _this->print = print;
}

void print(struct Test * _this)
{
  printf("Auteur: %s\n Message: %s\n", _this->_mess, _this->_author);
}

int main()
{
  struct Test test;

  __Test__(&test, "Hello", "Josuah");

  test.print(&test);

  printf("%d\n", sizeof(test));

  printf("%d\n", sizeof(struct Test));

  return 0;
}

