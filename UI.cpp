#include "UI.h"

UserInterface::UserInterface()
{
    char c[50] = "files/mainScreen.bin" ;
    printScreen(c);
    _getch();
}


#ifndef WIN32
// This is the reference to the given getch function, since we didnot know how to create and modify with buffered and non-buffered input
// http://stackoverflow.com/questions/3276546/how-to-implement-getch-function-of-c-in-linux
int UserInterface::_getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
} 
#endif

void UserInterface::clearScreen()
{
#ifdef WIN32
    system("cls");
#else
    system("clear");
#endif
}


bool UserInterface::Encode()
{
    clearScreen();
    char c[100];
    
    cout<<"Enter name of image to encode/decode.\n";
    cin>>c;
    BMPimage image(c);

    if(image.getSIZE()==0)
    {
        cout<<"File doesnot exist or is corrupt. Exiting program.\n";
        exit(0);
    }

    char fileName[100] = "files/encode.bin";
    printScreen(fileName);
    choice ='0';
    do
    {
        choice = _getch();
    }while(!(choice=='1' || choice=='2' || choice=='3' || choice=='4' || choice=='5' || choice=='6'));

    switch(choice)
    {
        case '1' : return image.EncodeLSB();
        case '2' : return image.pseudoEncode();
        case '3' : return image.filterEncode();
        case '4' : return image.DecodeLSB();
        case '5' : return image.pseudoDecode();
        case '6' : return image.filterDecode();
        default: return false;
    }

}

void UserInterface::printScreen(char *c)
{
    clearScreen();
    FILE *openFile;
    openFile = fopen(c,"a+");
    char ch;
    int i=0;
    
    fseek(openFile,-1,SEEK_END);
    int size = ftell(openFile);
    fseek(openFile,0,SEEK_SET);
    
    while(!feof(openFile))
    {
        if(i==size)
            break;
        ch = fgetc(openFile);
        cout<<ch;
        i++;
    }
    fclose(openFile);
}

void UserInterface::showMainMenu(bool check = true)
{
    char c[50] = "files/mainMenu.bin";
    printScreen(c);

    if(!check)
        cout<<"The file you tried to open either doesnot exist in the directory or is corrupt.\n";

    do{
    choice = _getch();
    }while(!(choice=='1' || choice=='2' || choice=='3' || choice=='4'));

    switch(choice)
    {
        case '1' :  check = Encode();
                    break;
        case '2':   showInstructions();
                    break;
        case '3':   showAbout();
                    break;
        case '4':   clearScreen();
                    exit(0);
        default: cout<<"\nUnexpected error.\n";
    }
    showMainMenu(check);

}

void UserInterface::showInstructions()
{
    char c[50]="files/instructions.bin";
    printScreen(c);

    do
    {
        choice = _getch();
    }while(choice!='1');
    showMainMenu();
}


void UserInterface::showAbout()
{
    char c[50]="files/about.bin";
    printScreen(c);

    do
    {
        choice = _getch();
    }while(choice!='1');
    showMainMenu();
}

