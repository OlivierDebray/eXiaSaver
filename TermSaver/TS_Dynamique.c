#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/time.h>

#include "printf_center.c"
#include "printf_middle.c"

void main()
{
	time_t secondes;
	struct tm instant;
	int i, t;
	
	//Configuration du rafraichissement
	printf_center("Entrez le temps de rafraichissement : ");
	scanf("%d", &t);

	system ("clear");

	//Recupération de l'heure de l'ordinateur
	time(&secondes);
	instant=*localtime(&secondes);

	//Affichage de l'heure avec le temps de rafraichissement
	while(1)
	{
		int theu = instant.tm_hour, heure0, heure1;
		int tmin = instant.tm_min, min0, min1;
		int tsec = instant.tm_sec, sec0, sec1;

		if(theu<10)
		{
			heure0=0;
			heure1=theu;
		}

		else
		{
			heure0=theu%10;
			heure0=theu-heure0;
			heure0/=10;
			heure1=theu%10;
		}

		if(tmin<10)
		{
			min0=0;
			min1=tmin;
		}

		else
		{
			min0=tmin%10;
			min0=tmin-min0;
			min0/=10;
			min1=tmin%10;
		}

		if(tsec<10)
		{
			sec0=0;
			sec1=tsec;
		}

		else
		{
			sec0=tsec%10;
			sec0=tsec-sec0;
			sec0/=10;
			sec1=tsec%10;
		}

		char tableau[8];
		sprintf(tableau, "%d%d%c%d%d%c%d%d\n", heure0, heure1, ':', min0,  min1, ':', sec0, sec1);
		printf_middle(2) ;
		printf_center(tableau);

		printf_center("Cet écran sera actualisé dans quelques secondes ");	//Affichage de la phrase centrée

		for(i=0; i<t; i++)		//t est le temps avant le rafraichissement
		{
			printf(". ");
			fflush(stdout);
			sleep(1);		//Ajoute un "." par seconde
		}

		system ("clear");
		time(&secondes);
		instant=*localtime(&secondes);
	}
}
