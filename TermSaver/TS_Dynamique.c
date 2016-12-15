#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/time.h>

#include "printf_center.c"
#include "printf_middle.c"

//_____________________________________________________________________


//Fonction pour centrer une phrase
/*void printf_center (const char* str)
{
	unsigned int n;
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);	//Recupération de la taille de la console

	for (n=0; n<(w.ws_col-strlen(str))/2; n++)	//Calcul du centre de la console
	{
		putchar(' ');		//Ajout d'espaces pour centrer
	}
	printf("%s", str);
}
*/


//_____________________________________________________________________



/*void afficherHeure(char *tableau)
{
	int taille_tableau=8, i, j, largeur, hauteur, largeur_totale=0, positionFichier;
	char nomFichier[50], format[3], caractere, caractere_fichier;

	for(i=0; i<8; i++)
	{
		for(j=0; j<8; j++)
		{
			positionFichier=i+2;

			caractere=tableau[j];
			if(caractere==':')
			{
				sprintf(nomFichier, "/home/raphael/Projet_ecran_veille/chiffres/points.pbm");
			}
			else
			{
				sprintf(nomFichier, "/home/raphael/Projet_ecran_veille/chiffres/%c.pbm", caractere);
			}
			printf("\n%s", nomFichier);
			if(i<7)
			{
				sprintf(nomFichier, "/home/raphael/Projet_ecran_veille/chiffres/esp.pbm");
				printf("\n%s", positionFichier);
			}

			FILE *fichier=NULL
			fichier=fopen (nomFichier, "r");

			while (fgetc(fp) != '\n') {};
			fscanf(fichier, "%d%d", &largeur, &hauteur);

			if(i==1) {largeur_totale+=largeur;}
			largeur_totale+=largeur;
			fclose(fichier);
		}
	}*/


	//Récupérer la largeure totale de l'heure
/*	for(i=0; i<8; i++)
	{
		caractere=tableau[i];

		if(caractere==':')
		{
			sprintf(nomFichier, "/home/raphael/Projet_ecran_veille/chiffres/points.pbm");
		}
		else
		{
			sprintf(nomFichier, "/home/raphael/Projet_ecran_veille/chiffres/%c.pbm", caractere);
		}

		FILE * fichier=NULL;
		fichier=fopen(nomFichier, "r");

		fgets(format, 3, fichier);
		fscanf(fichier, "%d%d", &largeur, &hauteur);
		largeur_totale+=largeur;
		fgetc(fichier);

		for(caractere_fichier='_'; caractere_fichier!=EOF; caractere_fichier=fgetc(fichier))
		{
			if(caractere_fichier=='1')
			{ printf("%c", 88); }
			else if(caractere_fichier=='0')
			{ printf("%c", 32); }
			else if(caractere_fichier=='\n')
			{ printf("\n"); }
			else {}
		}

		printf("\n\n");

		fclose(fichier);

		if(i<7)
		{
			FILE *fichier=NULL;
			fichier=fopen("/home/raphael/Projet_ecran_veille/chiffres/esp.pbm", "r");

			fgets(format, 3, fichier);
			largeur_totale+=largeur;
			fgetc(fichier);

			for(caractere_fichier='_'; caractere_fichier!=EOF; caractere_fichier=fgetc(fichier))
			{
				if(caractere_fichier=='1')
				{ printf("%c", 88); }
				else if(caractere_fichier=='0')
				{ printf("%c", 32); }
				else if(caractere_fichier=='\n')
				{ printf("\n"); }
				else {}
			}

			printf("\n\n");
	
			fclose(fichier);
		}
	}
}
*/


//_____________________________________________________________________



int main (void)
{
	time_t secondes;
	struct tm instant;
	int i, t;
	
	//Configuration du rafraichissement
	printf("Entrez le temps de rafraichissement : ");
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
		//afficherHeure(tableau);									// Inverser les // si séb envoie
		printf_middle(2) ;
		printf_center(tableau);		// Idem


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
	return 0;
}
