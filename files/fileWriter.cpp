//#include <simplecpp>
#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
using namespace std;

int main()
{
    char c[100];
    FILE *writeFile,*readFile;
    cout<<"Enter file name to write to- ";
    cin>>c;
    writeFile = fopen(c,"a+");
    cout<<"Enter name of read file.\n";
    cin>>c;
    readFile = fopen(c,"a+");

    fseek(writeFile,0,SEEK_SET);
    fseek(readFile,0,SEEK_SET);

    char ch;
    while(!feof(readFile))
    {
       ch = fgetc(readFile);
       if(ch!=0)
       fputc(ch,writeFile);
    }

    fseek(writeFile,0,SEEK_SET);
        while(!feof(writeFile))
        {
            ch = fgetc(writeFile);
            cout<<ch;
        }


    fclose(writeFile);
    fclose(readFile);
}
