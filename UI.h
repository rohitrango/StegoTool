#include "bitmap.h"
#include "bitmap_n.cpp"
#include "bitmap_r.cpp"
#include <iostream>
#include <cstdlib>
//#include <termios.h>  //for getch
#include <unistd.h>	  //for getch
#include <cstdio>     //for getchar
#include <fstream>
#include <conio.h>
using namespace std;

#ifndef UI
#define UI

class UserInterface
{
	char choice;

public:
	void clear();
	//int getch();
    UserInterface();
	void showMainMenu(bool check);
	bool Encode();
	void showInstructions();
	void showAbout();
	void printScreen(char *c);
};

#endif
