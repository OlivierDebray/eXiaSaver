#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "lanceur.c"

void main (int argc , char **argv)	// Fonction principale dans laquelle on récupère les paramètres d'appel
{
	system("clear") ;	// Nettoyage de la console

	if (argc > 1)	// On teste si l'utilisateur a passé un argument avec la commande
	{
		if (strcmp(argv[1] , "-1") == 0)	// Si l'argument est -1 on lance le TermSaver Statique
			lancementStatique() ;

                else if (strcmp(argv[1] , "-2") == 0)	// S'il est -2 on lance le TermSaver Dynamique
                        lancementDynamique() ;

                else if (strcmp(argv[1] , "-3") == 0)	// S'il est -3 on lance le TermSaver Interactif
                        lancementInteractif() ;

                else if(strcmp(argv[1] , "-stats") == 0)	// S'il est -stats on afficher les statistiques
                        lancementStatistiques() ;

		else
			lancementAleatoire() ;	// Si l'argument est tout autre, on lance un TermSaver aléatoire
	}
	else
	{
		lancementAleatoire() ;	// De même, s'il n'y a pas de paramètres, on lance un TermSaver aléatoire
	}
}
