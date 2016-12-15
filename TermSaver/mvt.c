#include <termios.h>
#include <unistd.h>

//importation de la fonction GETCH
//Afin de pouvoir l'utiliser sur linux
int getch() {
	struct termios initial_settings, new_settings;
	char ch;
	tcgetattr(0, &initial_settings);
	new_settings = initial_settings;
	new_settings.c_lflag &= ~ICANON;
	new_settings.c_lflag &= ~ECHO;
	new_settings.c_lflag &= ~ISIG;
	new_settings.c_oflag &= ~NL0;
	new_settings.c_oflag &= ~CR0;
	new_settings.c_oflag &= ~TAB0;
	new_settings.c_oflag &= ~BS0;
	new_settings.c_cc[VMIN] = 1;
	new_settings.c_cc[VTIME] = 0;
	cfsetospeed(&new_settings, B230400);
	cfsetispeed(&new_settings, 0);
	tcsetattr(0, TCSANOW, &new_settings);
	read(0, &ch, 1);
	tcsetattr(0, TCSANOW, &initial_settings);
	return ch;
}	
