#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

void stats(int type , int param) ;

void lancementStatique()
{
	printf("Lancement du TermSaver statique\n") ;
	sleep(1) ;

        int rand ;
        FILE *f = fopen("/dev/urandom" , "r") ;
        fread(&rand , 1 , 1 , f) ;
        fclose(f) ;

	int choix = 0 ;

	int nb_img = 8 ;	// Compléter avec les directives de répertoires
	int tmp = (256 / nb_img) ;

	int i = 0 ;

	while (choix == 0)
	{
		if (rand < (tmp * i))
			choix = i ;
		i++ ;
	}

	stats(1 , choix) ;

	printf("choix %d\n" , choix) ;
}

void lancementDynamique()
{
        printf("Lancement du TermSaver dynamique\n") ;
        sleep(1) ;

	int taille ;

	stats(2 , taille) ;
}

void lancementInteractif()
{
        printf("Lancement du TermSaver interactif\n") ;
        sleep(1) ;

	int pos ;

	stats(3 , pos) ;
}

void lancementStatistiques()
{
        printf("Affichage des statistiques\n") ;
        sleep(1) ;
}

void lancementAleatoire()
{
       	int rand ;

        FILE *f = fopen("/dev/urandom" , "r") ;
       	fread(&rand , 1 , 1 , f) ;
       	fclose(f) ;

	switch ((rand % 3) + 1)
	{
		case 1 :
			lancementStatique() ;
			break ;
		case 2 :
			lancementDynamique() ;
			break ;
		case 3 :
			lancementInteractif() ;
			break ;
	}
}

void stats(int type , int param)
{
	time_t t = time(NULL) ;

	FILE* stats = fopen("/mnt/hgfs/eXiaSaver/stats.txt" , "a") ;

	switch (type)
	{
		case 1 :
			fprintf(stats , "Statique     |") ;
			break ;
                case 2 :
                        fprintf(stats , "Dynamique    |") ;
			break ;
                case 3 :
                        fprintf(stats , "Interactif   |") ;
			break ;
	}

	fprintf(stats , "     %d     |" , param) ;

        fprintf(stats , "     %s" , asctime(localtime(&t))) ;
}
