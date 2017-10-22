#include "bitmap.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>     //for getchar
#include <fstream>

#ifdef WIN32
	#include <conio.h>
#else
	#include <termios.h>  //for getch
	#include <unistd.h>	  //for getch
#endif

using namespace std;

class UserInterface
{
    char choice;
    
public:
    void clearScreen();
    
#ifndef WIN32
    int _getch();
#endif
    
    UserInterface();
    
    void showMainMenu(bool check);
    bool Encode();
    void showInstructions();
    void showAbout();
    void printScreen(char *c);
};
