#include "UI.h"


UserInterface::UserInterface()
{
    char c[50] = "files/mainScreen.bin" ;
    printScreen(c);
    getch();
}


// This is the reference to the given getch function, since we didnot know how to create and modify with buffered and non-buffered input
// http://stackoverflow.com/questions/3276546/how-to-implement-getch-function-of-c-in-linux
/*int UserInterface::getch(void)
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
}*/

void UserInterface::clear()
{
  for(int i=0;i<10;i++)
    cout<<"\n\n\n";
}


bool UserInterface::Encode()
{
    system("cls");
    bool check =true;
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
        cin>>choice;
    }while(!(choice=='1' or choice=='2' or choice=='3' or choice=='4' or choice=='5' or choice=='6'));

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
    system("cls");
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

void UserInterface::showMainMenu(bool check=true)
{
    char c[50] = "files/mainMenu.bin";
    printScreen(c);

    if(!check)
        cout<<"The file you tried to open either doesnot exist in the directory or is corrupt.\n";

    do{
    cin>>choice;
    }while(!(choice=='1' or choice=='2' or choice=='3' or choice=='4'));

    switch(choice)
    {
        case '1' :  check = Encode();
                    break;
        case '2':   showInstructions();
                    break;
        case '3':   showAbout();
                    break;
        case '4':   system("cls");
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
        cin>>choice;
    }while(choice!='1');
    showMainMenu();
}


void UserInterface::showAbout()
{
    char c[50]="files/about.bin";
    printScreen(c);

    do
    {
        cin>>choice;
    }while(choice!='1');
    showMainMenu();
}

