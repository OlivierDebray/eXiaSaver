#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "mvt.c"
#include <sys/ioctl.h>


//Variable pour la direction de lavion
int direction;
int varx= 204;
int vary= 62;

//Declaration des fonctions
int PositionAvion();
int afficherAvion();

void main(int argc , char *argv[]) {
	int lancement = 1;
	char *positiondebut ;	

	//creationMAP();

	if (argc < 2)
	{
		printf("Erreur : aucun argument de position (1 , 2 , 3 ou 4)\n") ;
		exit(EXIT_FAILURE) ;
	}
	else
		positiondebut = argv[1] ;

    if (positiondebut == "0") direction = 1;
    	else if (positiondebut == "1")  direction = 2; 
    	else if (positiondebut == "2")  direction = 3; 
    	else if (positiondebut == "3")  direction = 4; 
	PositionAvion(direction);	

  while(lancement == 1) {

    //On recupere la valeur que l'utilisateur a ecrit
	char input = getch();
    
	//On compare afin de savoir qu'elle est le caractere ecrit
    if (input == 'h') direction = 1 ;
    	else if (input == 'b') direction = 2 ;
    	else if (input == 'g') direction = 3 ;
    	else if (input == 'd') direction = 4 ;
    	else if (input == 's') lancement = 2;
    
	PositionAvion(direction);
  }
}


int PositionAvion(int vDirection) {
//Fonction qui va permettre de changer la position de l'avion
	switch(vDirection) {
	   	case 1 :
    		//Vers le haut
    		if (vary > 0) {
    			vary --;
    			//Si on touche le haut de la console
    			if (vary == 0) vary = 62;
    		}
    		break;
    	case 2 :
    		//Vers le bas
    		if (vary <= 62) {
    			vary ++;
    			//Si on touche le bas on l'envoi en haut
    			if (vary == 62) vary = 0;
    		}
    		break;
    	case 3 : 
    		//Vers la gauche
    		if (varx > 0) {
 				varx --;
 				//Si on touche le bord de gauche on l'envoi a droite
 				if  (varx == 0) varx = 204;
 			}
    		break;
    	case 4 :
    	  	//Vers la droite
			if (varx <= 204) {
				varx ++;
				//Si on touche a droite on envoi a gauche
				if (varx == 204) varx = 0;
			}
    	  	break;
    }
	afficherAvion(vDirection);
	return 0;
}

int afficherAvion(int affichage) {

	//Appel la fonction pour afficher l'avion
	system("clear");
	
	//char appel[5] = "queue";
      switch(direction)
       {
        case 3: {
          //Permet de deplacer le curseur avec x et y comme valeurs
	  printf("\033[%d;%dH", vary, varx); 
	  printf("   xx     \n");
	
	  printf("\033[%d;%dH", vary + 1 , varx); 
	  printf("  x     xx\n");
	
	  printf("\033[%d;%dH", vary + 2 , varx); 
	  printf("xxxxxxxxx \n"); 

          printf("\033[%d;%dH", vary + 3 , varx); 
	  printf("  x     xx\n");

          printf("\033[%d;%dH", vary + 4 , varx);
          printf("   xx     \n");

          
	 break;
        }
         
        case 4: {
          printf("\033[%d;%dH", vary, varx); 
	  printf("     xx   \n");
	
	  printf("\033[%d;%dH", vary + 1 , varx); 
	  printf("xx     x  \n");
	
	  printf("\033[%d;%dH", vary + 2 , varx); 
	  printf(" xxxxxxxxx\n"); 

          printf("\033[%d;%dH", vary + 3 , varx); 
	  printf("xx     x  \n");
  
          printf("\033[%d;%dH", vary + 4 , varx);
          printf("     xx   \n");
         
         break;
        }

       case 1: {
 
          printf("\033[%d;%dH", vary, varx); 
	  printf("  x\n");
	
	  printf("\033[%d;%dH", vary + 1 , varx); 
	  printf(" xxx\n");
	
	  printf("\033[%d;%dH", vary + 2 , varx); 
	  printf("x x x\n"); 

          printf("\033[%d;%dH", vary + 3 , varx); 
	  printf("  x\n");
  
          printf("\033[%d;%dH", vary + 4 , varx);
          printf("  x\n");
          
          printf("\033[%d;%dH", vary + 5 , varx); 
	  printf(" xxx\n");
	
	  printf("\033[%d;%dH", vary + 6 , varx); 
	  printf(" x x\n");

         break;
        } 

         case 2: {
 
          printf("\033[%d;%dH", vary, varx); 
	  printf(" x x\n");
	
	  printf("\033[%d;%dH", vary + 1 , varx); 
	  printf(" xxx\n");
	
	  printf("\033[%d;%dH", vary + 2 , varx); 
	  printf("  x\n"); 

          printf("\033[%d;%dH", vary + 3 , varx); 
	  printf("  x\n");
  
          printf("\033[%d;%dH", vary + 4 , varx);
          printf("x x x\n");
	
	  printf("\033[%d;%dH", vary + 5 , varx); 
	  printf(" xxx\n");
	
	  printf("\033[%d;%dH", vary + 6 , varx); 
	  printf("  x\n"); 
        
         break;
        }

    }
  
	return 0;

}


