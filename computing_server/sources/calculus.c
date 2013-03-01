#include "calculus.h"

long fact(int nb)
{
  int i;
  long res;

  res = 1;
  for (i = nb; i > 1; --i)
    res = res * i;

  return res;
}

long power(int nb, int puiss)
{ 
  long res = nb;
  int i;

  for (i=1; i < puiss; ++i)
    res = res * nb;

  return res;
}

void stats(int * numbers, int nb_numbers, struct stat_t *res)
{
  int i;
  long somme;

  res->min = numbers[0];
  res->max = numbers[0];
  somme = numbers[0];
  
  for (i=1; i < nb_numbers; ++i)
    {
      if (numbers[i] > res -> max) res -> max = numbers[i];
      if (numbers[i] < res -> min) res -> min = numbers[i];
      somme += numbers[i];
    }

  res -> moy = ((float)somme) / nb_numbers;
}


