#include <stdio.h>
#include <ctype.h>
#include "CalculusClient.h"

int main()
{
  struct CalculusClient client;
  char c;
  int nb;
  int data_len;
  int puiss;
  int i;
  int * numbers = NULL;
  struct stat_t res;

  if( __CalculusClient__(&client) == -1)
    perror("CalculusClient");

  if( client.connect(&client, "127.0.0.1", 4000) == -1)
    return -1;

  do
    {
      printf("Quelle opération?\n");
      printf("[F]actoriel\n");
      printf("[P]uissance\n");
      printf("[S]tatistiques\n");
      printf("[Q]uitter\n");

      c = getchar();

      switch( toupper(c) )
	{
	case 'F':
	  printf("fact(n)\nn=? ");
	  scanf("%d", &nb); getchar();
	  printf( "fact(%d) = %ld\n", nb, client.fact(&client, nb) );
	  break;

	case 'P':
	  printf("pow(nb, puiss)\nnb=? ");
	  scanf("%d", &nb); getchar();
	  printf("puiss=? ");
	  scanf("%d", &puiss); getchar();
	  printf( "pow(%d, %d) = %ld\n", nb, puiss, client.pow(&client, nb, puiss) );
	  break;

	case 'S':
	  printf("stats(nb_1, nb_2,..., nb_p)\np=? ");
	  scanf("%d", &nb); getchar();

	  if( data_len != (int)( nb*sizeof(int) ) )
	    {
	      data_len = nb*sizeof(int);
	      numbers = (int*) realloc( numbers, nb*sizeof(int) );
	    }

	  printf("nb1 nb2 ... nb_p\n");

	  for(i=0; i< nb; ++i)
	    scanf("%d", &numbers[i]); getchar();

	  for(i=0; i< nb; ++i) printf("%d ", numbers[i]); printf("\n");

	  client.stats(&client, numbers, nb, &res);
	  printf( "moy = %f\nmin = %d\nmax = %d\n", res.moy, res.min, res.max );
	  break;

	case 'Q':
	  client.disconnect(&client);
	  break;

	default:
	  printf("Unknown choice\n");
	}
    }
  while( toupper(c) != 'Q' );

  if(numbers)
    free(numbers);

  return 0;
}
