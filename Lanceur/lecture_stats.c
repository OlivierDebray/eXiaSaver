#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

char* recupStats() ;

pid_t creationProcessus()
{
	pid_t pid ;

	do
	{
		pid = fork() ;
	} while ((pid == -1) && (errno == EAGAIN)) ;

	return pid ;
}

void processusFils()
{
	FILE * stats = fopen("/mnt/hgfs/eXiaSaver/stats.txt" , "r") ;

	char str[100] ;
	int i = 0 ;

	while (fgets(str , 100 , stats) != NULL)
		printf("%s" , str) ;

	fclose(stats) ;
}

void processusPere()
{
	wait(NULL) ;

	char rep ;

	printf("\nAppuyez sur O pour afficher les statistiques\n") ;

	scanf("%c" , &rep) ;

	if((rep == 'O') || (rep == 'o'))
		recupStats() ;
}

void lecture_stats()
{
	pid_t pid = creationProcessus() ;

	switch (pid)
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

char* recupStats()
{
	FILE * stats = fopen("/mnt/hgfs/eXiaSaver/stats.txt" , "r") ;

	int n = 0 , compteurStat = 0 , compteurDyna = 0 , compteurInte = 0 ;
	char str[100] , *tmp ;

	char *tmpType , *tmpParam ;

	while (fgets(str , 100 , stats) != NULL)
	{
		for (int i = 0 ; str[i] != '\n' ; i++)
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

	if ((compteurStat > compteurDyna) && (compteurStat > compteurInte))
		printf("\nLe TermSaver le plus utilisé est le Statique\n") ;
        if ((compteurDyna > compteurStat) && (compteurDyna > compteurInte))
                printf("\nLe TermSaver le plus utilisé est le Dynamique\n") ;
        if ((compteurInte > compteurStat) && (compteurInte > compteurDyna))
                printf("\nLe TermSaver le plus utilisé est l'Interactif\n") ;

	fclose(stats) ;
} 
