#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{

int caractere;

FILE *fichier = NULL;
fichier = fopen("ecran1.pbm", "r");


    if (fichier != NULL)

    {
        while (caractere != EOF)
        {
            caractere = fgetc(fichier);
            


            if(caractere =='0')
            {
            	caractere = 45;
            }

            else if(caractere == '1')
            {
            	caractere = 88;
            }

	printf("%c", caractere);

        }

    fclose(fichier);

    }
    return 0;
}
