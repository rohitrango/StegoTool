#include "bitmap.h"


bool BMPimage::EncodeLSB()
{
    char fileName[100],c;
    cout<<"\tEnter the name of the file to hide : ";
    cin>>fileName;
    ifstream f(fileName,ios::ate|ios::binary);
    if(!f)
    {
        cout<<"Invalid name of given file \nExiting interface\n";
        return false;
    }
    unsigned long int sizeFile;
    f.seekg(0,ios::end);
    sizeFile = f.tellg();
    if(sizeFile>=size/8)
    {
        cout<<"ERROR : Given File too large";
        return false;
    }
    f.seekg(0,ios::beg);

    unsigned int index=3;
    cout<<"\tFileSize = "<<sizeFile<<" Bytes."<<endl;
    for(unsigned int i=0;i<sizeFile;++i)
    {
        f.read(&c,1);
        for(int j=7;j>=0;j--)
        {
            data[index+j]=(data[index+j]/2)*2;
            data[index+j] += (c%2);
            c/=2;
        }
        index+=8;
        

    }
    data[2] = sizeFile%256;
    sizeFile/=256;
    data[1] = sizeFile%256;
    sizeFile/=256;
    data[0] = sizeFile%256;
    cout<<"\tSave processed image as(*.bmp) : ";
    cin>>fileName;
    writeBMP(fileName);
    f.close();
    cout<<"\tFile successfully processed.\n";
    return true;
}

bool BMPimage::DecodeLSB()
{

    long fileSize;
    char fileName[100];
    cout<<"\tSave retreived file as : ";
    cin>>fileName;
    FILE *saveFile = fopen(fileName,"wb");
    if(!saveFile)
    {
        cout<<"Invalid name of given file \nExiting interface\n";
        return false ;
    }
    int index=3;
    char c=0;
    fileSize = data[0];
    fileSize*=256;
    fileSize+=data[1];
    fileSize*=256;
    fileSize+=data[2];
    cout<<"\tFileSize = "<<fileSize<<" Bytes."<<endl;
    for(int i=0;i<fileSize;++i)
    {
        c=0;
        for(int j=0;j<8;j++)
        c+=(data[index+j]%2)*pow(2,7-j);
        fwrite(&c,1,1,saveFile);
        index+=8;
    }
    cout<<"\tFile retreived successfully in : "<<fileName<<endl;
    fclose(saveFile);
    return true;
}

bool BMPimage::pseudoEncode()
{
    char filename[100],c;
    bool *hash;
    hash = new bool[size];
    for(unsigned int i=0;i<size;++i)
    hash[i]=false;
    cout<<"\tEnter file to be processed : ";
    cin>>filename;
    ifstream f(filename,ios::ate|ios::binary);
    if(!f)
    {
        cout<<"Invalid name of given file \nExiting interface.\n";
        return false;
    }
    unsigned long int sizeFile;
    f.seekg(0,ios::end);
    sizeFile = f.tellg();
    if(sizeFile>=size/8)
    {
        cout<<"ERROR : Given File too large.\n";
        return false;
    }
    f.seekg(0,ios::beg);
    cout<<"\tFileSize = "<<sizeFile<<" Bytes."<<endl;
    cout<<"\tEnter password for seed(max 20 characters): ";
    char password[21];
    cin>>password;
    int x=0,y=7,z=11,w=3;
    for(int i=0;password[i]!='\0';++i)
    {
        x+=password[i]*(i+1);
    }

    for(unsigned int i=0;i<sizeFile;++i)
    {
        f.read(&c,1);
        for(int j=7;j>=0;j--)
        {
            do
            {
                unsigned int t = x ^ (x << 11);
                x = y; y = z; z = w;
                w = w ^ (w >> 19) ^ t ^ (t >> 8);
                w%=size;
            }while(hash[w]);
            hash[w]=true;
            data[w]=(data[w]/2)*2;
            data[w] += (c%2);
            c/=2;
        }
    }
    data[2] = sizeFile%256;
    sizeFile/=256;
    data[1] = sizeFile%256;
    sizeFile/=256;
    data[0] = sizeFile%256;
    cout<<"\tSave processed image as (*.bmp) : ";
    char fileName[100];
    cin>>fileName;
    writeBMP(fileName);
    f.close();
    cout<<"\tFile successfully processed.\n";
    delete[] hash;
    return true;
}

bool BMPimage::pseudoDecode()
{
    long unsigned int fileSize;
    char fileName[100],c;
    pixel p;
    bool *hash;
    hash = new bool[size];
    for(unsigned int i=0;i<size;++i)
    hash[i]=false;
    cout<<"\tSave retreived file as : ";
    cin>>fileName;
    FILE *saveFile = fopen(fileName,"wb");
    if(!saveFile)
    {
        cout<<"Invalid name of given file \nExiting interface.\n";
        return false;
    }
    fileSize = data[0];
    fileSize*=256;
    fileSize+=data[1];
    fileSize*=256;
    fileSize+=data[2];
    cout<<"\tFileSize = "<<fileSize<<" Bytes."<<endl;
    cout<<"\tEnter password : ";
    char password[20];
    cin>>password;
    int x=0,y=7,z=11,w=3;
    for(int i=0;password[i]!='\0';++i)
    {
        x+=password[i]*(i+1);
    }
    for(unsigned int i=0;i<fileSize;++i)
    {
        c=0;
        for(int j=0;j<8;j++)
        {
            do
            {
                unsigned int t = x ^ (x << 11);
                x = y; y = z; z = w;
                w = w ^ (w >> 19) ^ t ^ (t >> 8);
                w%=size;
            }while(hash[w]);
            hash[w]=true;
            c+=(data[w]%2)*pow(2,j);
        }
        fwrite(&c,1,1,saveFile);
    }
    cout<<"\tFile retreived successfully in : "<<fileName<<endl;
    fclose(saveFile);
    delete[] hash;
    return true;
}