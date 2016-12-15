#include <stdio.h>	// Inclusion des différentes bibliothèques utilisées
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h>

#include "lecture_stats.c"	

void stats(int type , char param[5]) ;	// Prototype de la fonction de sauvegarde des statistiques

int aleatoire()		// Fonction permettant de créer un nombre aléatoire compris entre 0 et 255
{
        int rand ;
        FILE *f = fopen("/dev/urandom" , "r") ;		// On ouvre le fichier urandom qui contient des valeurs générérées à partir des bruits électriques de l'ordinateur
        fread(&rand , 1 , 1 , f) ;	// On prend un octet parmi ces valeurs
        fclose(f) ;

	return rand ;
}

void lancementStatique()
{
	printf("Lancement du TermSaver statique\n") ;
	sleep(1) ;

	int rand = aleatoire() , choix = 0 , nb_img = -2 , i = 0 ;	// On déclare nb_img à -2 car un répertoire vide contient quand même deux informations

	DIR* PBM_1 = opendir(getenv("EXIASAVER1_PBM")) ; 	// On ouvre le répertoire contenant les fichiers PBM

	while (readdir(PBM_1) != NULL)		// On boucle pour savoir combien de fichiers sont dans le répertoire
		nb_img++ ;

	if (nb_img == 0)	// Si il n'y a pas de fichiers dans le répertoire, on termine le processus
	{
		printf("--- Pas de fichiers à lire, fin du processus ---\n") ;
		exit(EXIT_FAILURE) ;
	}

	closedir(PBM_1) ;

	int tmp = (256 / nb_img) ;	// On déclare une variable tampon égale au quotient de 256 par le nombre de fichiers

	while (choix == 0)	// On boucle pour voir à combien de tmp rand équivaud au minimum ; exemple : pour 8 images, tmp = 32 , si rand = 70 alors choix = 3
	{
		if (rand < (tmp * i))
			choix = i ;
		i++ ;
	}

	char arg[5] ;

	sprintf(arg , "%d" , choix) ;

        stats(1 , arg) ;        // On enregistre le résultat dans les statistiques

	if (execl(strcat(getenv("EXIASAVER_HOME") , "/TS_Statique") , "TS_Statique" , arg , NULL) == -1)
		printf("Erreur\n") ;
}

void lancementDynamique()
{
        printf("Lancement du TermSaver dynamique\n") ;
        sleep(1) ;

	char taille[5] = " " ;

	stats(2 , taille) ;      // On enregistre le résultat dans les statistiques
}

void lancementInteractif()
{
        printf("Lancement du TermSaver interactif\n") ;
        sleep(1) ;

	char pos[5] = " " ;

	stats(3 , pos) ;      // On enregistre le résultat dans les statistiques
}

void lancementStatistiques()
{
        printf("Affichage des statistiques\n\n") ;
        sleep(1) ;

	lecture_stats() ;	// On appelle la fonction lecture_stats() dans lecture_stats.c
}

void lancementAleatoire()
{
       	int rand = aleatoire() ;

	switch ((rand % 3) + 1)		// On effectue le modulo du nombre entre 0 et 255 obtenu pour le ramener à un tirage au sort entre 3 valeurs
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

void stats(int type , char param[5])
{
	time_t t = time(NULL) ;		// On initialise l'heure
	char *p ;	// On définit une chaine de caractère qui servira à stocker l'heure
	int len ;

	FILE* stats = fopen("/mnt/hgfs/eXiaSaver/stats.txt" , "a") ;	// On ouvre le fichier de statistiques

        p = ctime(&t) ;		// On affecte la valeur du temps à la chaine p ...
        len = strlen(p) ;	// ... dont on récupère la valeur dans len

        fprintf(stats , "     %.*s     |" , len - 1 , p) ;	// Puis l'on écrit la chaine p dont on a retiré le dernier caractère (soit le retour à la ligne)


	switch (type)	// On écrit de plus quel type de TermSaver à été lancé
	{
		case 1 :
			fprintf(stats , "     Statique     |") ;
			break ;
                case 2 :
                        fprintf(stats , "     Dynamique    |") ;
			break ;
                case 3 :
                        fprintf(stats , "     Interactif   |") ;
			break ;
	}

	fprintf(stats , "     %s\n" , param) ;	// On écrit la valeur du paramètre

	fclose(stats) ;
}
