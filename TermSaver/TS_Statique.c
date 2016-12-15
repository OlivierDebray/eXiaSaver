#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <sys/wait.h>
#include "getch.c"

#include "printf_middle.c"
#include "printf_center.c"

void processus_fils(char *img)
{
int ligne = 0 , nb_ligne = 0 ; //déclaration des variable "ligne" et "nbr_ligne", on lui attribu aussi la valeur 0

char chaine[256] ; //création d'un tableau de type char appelé chaine de taille 256

FILE *fichier = fopen(strcat(getenv("EXIASAVER1_PBM") , img), "r"); //FILE est un pointeur vers fichier. getenv obtient la valeur de la variable environnement. strcat associe getenv à img

    	if (fichier != NULL) //structure if, tant que le fichier n'est pas vide'
    	{
		while (fgets(chaine , 256 , fichier) != NULL) //parcourt tout le fihcier pour voir combien il y a de ligne
			nb_ligne++ ; // incrémentation nombre de ligne, il passe a la ligne suivante dès que la ligne est fini

		printf_middle(nb_ligne) ; //centre verticalement la chiane de caractere nb_ligne
		rewind(fichier) ; //permet de reveneir au debut du fichier

		while (fgets(chaine , 256 , fichier) != NULL) //récupere les chaine de caractere du fchicier dans la chaine tant qu'il y a des lignes
		{
			if (ligne > 1) //si la ligne est superieur à 1
			{
				for (int i = 0 ; i < 256 ; i++) // pour les chiane de caractere 0 à 256 avec une incrémenetation
				{
					if (chaine[i] == '0') //si la chaine de caractère stocké est "0"
						chaine[i] = ' ' ; //afficher "   "
					else if (chaine[i] == '1') //si la chaine de caractère stocké est "1"
						chaine[i] = 'X' ; //afficher "X"
					else if (chaine[i] == '\n') // si la chaine de caractère stocké est "\n" (retour a la ligne)
						chaine[i] = '\n' ; //affciher "\n" (retour à la ligne)
				}

				printf_center(chaine) ; //centrer horizontalement la chaine de caractere chaine
			}
			ligne++ ; //incrémentation
		}
    		fclose(fichier); //ferme le fichier ouvert
	}
	exit(EXIT_SUCCESS) ;
}

void main(int argc, char* argv[]) //déclaration de la fonction main
{
system("clear"); //permet l'effacement de la console, efface l'ensseble des commandes précédentes

char img[100] ; //création d'un tableau de type char appelé img de taille 100

strcpy(img , "/ecran") ; // copie de la chaine de caractère /ecran dans img
strcat(strcat(img , argv[1]) , ".pbm") ; // ajoute a img la valeur de l'argument et la chaine ".pbm"

pid_t pid ;

do {
	pid = fork() ;
} while (pid == -1) ;

switch (pid)
{
	case -1 :
		break ;
	case 0 :
		processus_fils(img) ;
		break ;
	default :
		wait(NULL) ;
}

getch() ;

system("clear") ; //efface le terminal
}
