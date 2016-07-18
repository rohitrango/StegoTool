#include "bitmap.h"
#include <iostream>
#include <cstdlib>
#include <termios.h>  //for getch
#include <unistd.h>	  //for getch
#include <cstdio>     //for getchar
#include <fstream>
using namespace std;

class UserInterface
{
	char choice;

public:
	void clear();
	int _getch();
    UserInterface();
	void showMainMenu(bool check);
	bool Encode();
	void showInstructions();
	void showAbout();
	void printScreen(char *c);
};
