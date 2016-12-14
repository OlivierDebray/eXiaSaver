#include <stdlib.h>	// Inclusion des différentes bibliothèques
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void recupStats() ;	// Prototype de la fonction recupStats()

pid_t creationProcessus()	// Fonction permettant de créer un nouveau processus et de renvoyer le PID
{
	pid_t pid ;

	do	// On fork, et l'on rééssaye si le fork a échoué
	{
		pid = fork() ;
	} while (pid == -1) ;

	return pid ;
}

void processusFils()
{
	FILE * stats = fopen("/mnt/hgfs/eXiaSaver/stats.txt" , "r") ;	// On ouvre le fichier des statistiques en lecture

	char str[100] ;
	int i = 0 ;

	while (fgets(str , 100 , stats) != NULL)	// On récupère toutes les lignes du fichier que l'on imprime sur le terminal
		printf("%s" , str) ;

	fclose(stats) ;
}

void processusPere()
{
	wait(NULL) ;	// On attend la fin du processus fils

	char rep ;

	printf("\nAppuyez sur O pour afficher les statistiques\n") ;

	scanf("%c" , &rep) ;	// On attend la réponse de l'utilisateur

	if((rep == 'O') || (rep == 'o'))	// Si la réponse est O, on appelle une autre fonction ; sinon, le processus se termine
		recupStats() ;
}

void lecture_stats()	// Fonction appelée dans lanceur.c, fait office de "main"
{
	pid_t pid = creationProcessus() ;	// Création d'un nouveau processus

	switch (pid)	// On teste pour voir si le processus a échoué, si l'on est dans le processus fils ou dans le processus père
	{
		case -1 :
			break ;
		case 0 :
			processusFils() ;
			break ;
		default :
			processusPere() ;
			break ;
	}
}

void recupStats()	// Fonction servant à récupérer les valeurs de "stats.txt"
{
	FILE * stats = fopen("/mnt/hgfs/eXiaSaver/stats.txt" , "r") ;	// On ouvre le fichier

	int n = 0 , compteurStat = 0 , compteurDyna = 0 , compteurInte = 0 ;	// On définit les différentes variables
	char str[100] ;

	while (fgets(str , 100 , stats) != NULL)	// Tant qu'on peut récupérer des lignes dans le fichier ...
	{
		for (int i = 0 ; str[i] != '\n' ; i++)	// ... pour chaque ligne on regarde s'il y a la présence des mots "St" "Dy" ou "In" et l'on incrémente les compteurs en conséquence
		{
			if ((str[i - 1] == 'S') && (str[i] == 't'))
				compteurStat++ ;
			else if ((str[i - 1] == 'D') && (str[i] == 'y'))
				compteurDyna++ ;
                        else if ((str[i - 1] == 'I') && (str[i] == 'n'))
                                compteurInte++ ;
		}
	}

	printf("- Statique : %d\n" , compteurStat) ;
        printf("- Dynamique : %d\n" , compteurDyna) ;
        printf("- Interactif : %d\n" , compteurInte) ;

	if ((compteurStat > compteurDyna) && (compteurStat > compteurInte))	// On regarde quel TermSaver est le plus fréquent et on l'affiche
		printf("\nLe TermSaver le plus utilisé est le Statique\n") ;
        else if ((compteurDyna > compteurStat) && (compteurDyna > compteurInte))
                printf("\nLe TermSaver le plus utilisé est le Dynamique\n") ;
        else if ((compteurInte > compteurStat) && (compteurInte > compteurDyna))
                printf("\nLe TermSaver le plus utilisé est l'Interactif\n") ;

	fclose(stats) ;
} 
