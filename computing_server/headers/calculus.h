#ifndef _calculus
#define _calculus

struct stat_t{
  float moy;
  int max;
  int min;
};

long fact(int nb);

long power(int nb, int puiss);

void stats(int * numbers, int nb_numbers, struct stat_t *res);

#endif
