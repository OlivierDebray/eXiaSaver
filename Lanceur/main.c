#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "lanceur.c"

void main (int argc , char **argv)	// Fonction principale dans laquelle on récupère les paramètres d'appel
{
	system("clear") ;	// Nettoyage de la console

	if (argc > 1)
	{
		if (strcmp(argv[1] , "-1") == 0)
			lancementStatique() ;

                else if (strcmp(argv[1] , "-2") == 0)
                        lancementDynamique() ;

                else if (strcmp(argv[1] , "-3") == 0)
                        lancementInteractif() ;

                else if(strcmp(argv[1] , "-stats") == 0)
                        lancementStatistiques() ;

		else
			lancementAleatoire() ;
	}
	else
	{
		lancementAleatoire() ;
	}
}
