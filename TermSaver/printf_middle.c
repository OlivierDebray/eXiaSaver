#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>

void printf_middle(int hauteur) //déclaration de la fonction "printf_middle""
{
        unsigned int n ;
        struct winsize w ;
        ioctl(0 , TIOCGWINSZ , &w) ;	// On récupère les propriétés de taille de la console

        for (n=0 ; n < ((w.ws_row - hauteur) / 2) ; n++)	// On remplit la moitié de l'espace vide de retours chariots pour centrer l'image en hauteur
                printf("\n") ;
}
