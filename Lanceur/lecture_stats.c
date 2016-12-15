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

	int n = 0 , compteurStat = 0 , compteurDyna = 0 , compteurInte = 0 , compteur1 = 0 , compteur2 = 0 , compteur3 = 0 ;	// On définit les différentes variables
	char str[100] ;
	char ParamStat[100] = {0} ;	// Tableau contenant les paramètres du Statique
	int ParamStat_alloc = 0 ;	// Variable permettant de gérer l'allocation des valeurs dans le tableau

	while (fgets(str , 100 , stats) != NULL)	// Tant qu'on peut récupérer des lignes dans le fichier ...
	{
		for (int i = 0 ; str[i] != '\n' ; i++)	// ... pour chaque ligne on regarde s'il y a la présence des mots "St" "Dy" ou "In" et l'on incrémente les compteurs en conséquence
		{
			if ((str[i] == 'S') && (str[i + 1] == 't'))
			{
				compteurStat++ ;
				
				int cpt_ParamStat = 0 ;

				for (int j = 0 ; j < 100 ; j++)	
				{
					if (str[i + 19] != ParamStat[j])	// Si le paramètre est différent d'une case du tableau
						cpt_ParamStat++ ;		// On incrémente le compteur

					if (str[i + 19] == ParamStat[j])	// Si le paramètre équivaud l'une des cases du tableau
						ParamStat[j+50] = ParamStat[j+50] + 1 ;	// On incrémente la valeur de la case correspondant à son compteur 

					if (cpt_ParamStat == 100)		// Si aucune case n'a été en correspondance
					{
						ParamStat[ParamStat_alloc] = str[i + 19] ;	// La première case libre prend la valeur du paramètre
						ParamStat[ParamStat_alloc + 50] = 1 ;	// Et vaut 1
						ParamStat_alloc++ ;			// Et l'on incrémente la valeur du compteur d'allocation
					}
				}
			}
			else if ((str[i] == 'D') && (str[i + 1] == 'y'))
			{
				compteurDyna++ ;
                        }
			else if ((str[i] == 'I') && (str[i + 1] == 'n'))
                        {
			        compteurInte++ ;
			}
		}
	}

	int tmp , tmp2 ;	// Variables tampon pour le tri

	for (int k = 100 ; k > 50 ; k--)	// On examine les 50 dernières cases du tableau
	{
		if (ParamStat[k] > ParamStat[k-1])	// Si le paramètre le plus haut est plus grand, on inverse les valeurs de l'écran et de l'occurence
		{	
			tmp = ParamStat[k-1] ;
			tmp2 = ParamStat[k - 51] ;
			ParamStat[k-1] = ParamStat[k] ;
			ParamStat[k - 51] = ParamStat[k -50] ;
			ParamStat[k] = tmp ;
			ParamStat[k - 50] = tmp2 ;
		}
	}
	
	// On affiche les occurences

	printf("- Statique : %d fois\n    dont : " , compteurStat) ;
		printf("- %d fois avec l'écran %c\n" , ParamStat[50] , ParamStat[0]) ;
		printf("           - %d fois avec l'écran %c\n" , ParamStat[51] , ParamStat[1]) ;
		printf("           - %d fois avec l'écran %c\n\n" , ParamStat[52] , ParamStat[2]) ;

        printf("- Dynamique : %d fois\n" , compteurDyna) ;

        printf("- Interactif : %d fois\n" , compteurInte) ;

	if ((compteurStat > compteurDyna) && (compteurStat > compteurInte))	// On regarde quel TermSaver est le plus fréquent et on l'affiche
		printf("\nLe TermSaver le plus utilisé est le Statique\n") ;
        else if ((compteurDyna > compteurStat) && (compteurDyna > compteurInte))
                printf("\nLe TermSaver le plus utilisé est le Dynamique\n") ;
        else if ((compteurInte > compteurStat) && (compteurInte > compteurDyna))
                printf("\nLe TermSaver le plus utilisé est l'Interactif\n") ;

	fclose(stats) ;
} 
