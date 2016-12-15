#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>

void printf_center(const char *str) //déclaration de la fonction "printf_center"
{
	unsigned int n ;
	struct winsize w ;
	ioctl(0 , TIOCGWINSZ , &w) ;	// On récupère les propriétés de taille de la console

	for (n= 0 ; n < ((w.ws_col - strlen(str)) / 2) ; n++)	// On remplit la moitié de l'espace vide d'espace pour centrer l'image en largeur
		printf(" ") ;

	printf("%s" , str) ;	// On imprime la chaine de l'image
}
