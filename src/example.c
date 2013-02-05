#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
  switch( fork() )
    {
    case -1:
      perror("premier fork(): ");
      exit(-1);

    case 0:
      execl("./serveur.out", "serveur.out", NULL);

      perror("execl(): ");
      exit(-1);

    default:

      switch( fork() )
	{
	case -1:
	  perror("deuxième fork(): ");
	  exit(-1);

	case 0:
	  sleep(1);
	  execl("./client.out", "client.out", NULL);

	  perror("execl(): ");
	  exit(-1);

	default:
	  wait(NULL);
	  wait(NULL);
	}
    }

  return 0;
}
