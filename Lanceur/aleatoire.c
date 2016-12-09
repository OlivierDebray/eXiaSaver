#include <unistd.h>

int aleatoire()
{
	int rand ;
	FILE *f ;

	f = fopen("/dev/urandom" , "r") ;
	fread(&rand , 1 , 1 , f) ;
	fclose(f) ;

	return rand ;
}
