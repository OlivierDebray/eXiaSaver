#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>

void printf_middle(int hauteur)
{
        unsigned int n ;
        struct winsize w ;
        ioctl(0 , TIOCGWINSZ , &w) ;

        for (n=0 ; n < ((w.ws_row - hauteur) / 4) ; n++)
                printf("\n") ;
}

void printf_center(const char *str)
{
	unsigned int n ;
	struct winsize w ;
	ioctl(0 , TIOCGWINSZ , &w) ;

	for (n= 0 ; n < ((w.ws_col - strlen(str)) / 4) ; n++)
		printf(" ") ;
	printf("%s" , str) ;
}

void main(int argc, char* argv[])
{
system("clear");

char img[100] ;

int ligne = 0 , nb_ligne = 0 ;

char chaine[256] ;

strcpy(img , "/ecran") ;
strcat(strcat(img , argv[1]) , ".pbm") ;

FILE *fichier = fopen(strcat(getenv("EXIASAVER1_PBM") , img), "r");

    if (fichier != NULL)
    {
	while (fgets(chaine , 256 , fichier) != NULL)
		nb_ligne++ ; 

	printf_middle(nb_ligne) ;
	rewind(fichier) ;

	while (fgets(chaine , 256 , fichier) != NULL)
	{
		if (ligne > 1)
		{
			for (int i = 0 ; i < 256 ; i++)
			{
				if (chaine[i] == '0')
					chaine[i] = ' ' ;
				else if (chaine[i] == '1')
					chaine[i] = 'X' ;
				else if (chaine[i] == '\n')
					chaine[i] = '\n' ;
			}

			printf_center(chaine) ;
		}
		ligne++ ;
	}
    	fclose(fichier);	
    }

	getchar() ;
	system("clear") ;
}
