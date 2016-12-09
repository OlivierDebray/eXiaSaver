#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void lancementStatique()
{
	printf("Lancement du TermSaver statique\n") ;
	sleep(1) ;
}

void lancementDynamique()
{
        printf("Lancement du TermSaver dynamique\n") ;
        sleep(1) ;
}

void lancementInteractif()
{
        printf("Lancement du TermSaver interactif\n") ;
        sleep(1) ;
}

void lancementStatistiques()
{
        printf("Affichage des statistiques\n") ;
        sleep(1) ;
}

void lancementAleatoire()
{
	while (1)
	{
		int rand ;
		FILE *f ;

		f = fopen("/dev/urandom" , "r") ;
		fread(&rand , 1 , 1 , f) ;
		fclose(f) ;

		if (rand < 85)
		{
			lancementStatique() ;
			break ;
		}
		else if (rand < 170)
		{
			lancementDynamique() ;
			break ;
		}
		else if (rand < 255)
		{
			lancementInteractif() ;
			break ;
		}
	}
}
