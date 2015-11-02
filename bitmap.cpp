#include"bitmap.h"
#include<stdlib.h>

BMPimage::~BMPimage()
{
    delete[] data;
}

BMPimage::BMPimage(char* filename)
{
    FILE* f = fopen(filename, "rb");

    fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

    // extract image height and width from header
    width = *(int*)&info[18];
    height = *(int*)&info[22];
    bitDepth = *(int*)&info[28];
    channels = bitDepth/8;

    size = *(int*)&info[34];
    data = new unsigned char[size]; // allocate 3 bytes per pixel
    fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
    fclose(f);


}

void BMPimage::writeBMP(char *filename)
{

    FILE *f = fopen(filename,"wb");

   // unsigned char *newdata = new unsigned char[size];
   // newdata = data;

    fwrite(info, sizeof(unsigned char), 54, f);
    fwrite(data, sizeof(unsigned char), size, f);
    fclose(f);
    //delete[] newdata;
}

const unsigned int BMPimage::getSIZE()
{
    return size;
}

const int BMPimage::getWIDTH()
{
    return width;
}

const int BMPimage::getHEIGHT()
{
    return height;
}

pixel BMPimage::getPIXEL( int x, int y)
{
    int index = (y*width+x)*channels;
    pixel p;
    if(channels==3)
    {
        p.b = data[index];
        p.g = data[index+1];
        p.r = data[index+2];
    }
    else if(channels==4)
    {
        p.b = data[index];
        p.g = data[index+1];
        p.r = data[index+2];
        p.a = data[index+3];
    }
    return p;
}

pixel BMPimage::getPIXEL(int index)
{
    pixel p;
    if(channels==3)
    {
        p.b = data[index];
        p.g = data[index+1];
        p.r = data[index+2];
    }
    else if(channels==4)
    {
        p.b = data[index];
        p.g = data[index+1];
        p.r = data[index+2];
        p.a = data[index+3];
    }
    return p;
}

void BMPimage::changePIXEL( pixel p, int x, int y)
{
    int index = (y*width+x)*channels;
    if(channels==3)
    {
        data[index] = p.b;
        data[index+1] = p.g;
        data[index+2] = p.r;
    }
    else if(channels==4)
    {
        data[index] = p.b;
        data[index+1] = p.g;
        data[index+2] = p.r;
        data[index+3] = p.a;
    }
}

void BMPimage::changePIXEL( pixel p, int index)
{
    if(channels==3)
    {
        data[index] = p.b;
        data[index+1] = p.g;
        data[index+2] = p.r;
    }
    else if(channels==4)
    {
        data[index] = p.b;
        data[index+1] = p.g;
        data[index+2] = p.r;
        data[index+3] = p.a;
    }
}

void BMPimage::convertImage()
{
    for(unsigned int i=0;i<size;i++)
        if(data[i]%2)
            data[i]--;
}


void BMPimage::encode(char *encFile)     //just a test algorithm to hide files
{
    convertImage();
    fstream f(encFile);
    char c;
    unsigned long int sizeFile;
    f.seekg(0,ios::end);
    sizeFile = f.tellg();
    if(sizeFile>=size/8)
    {
        cout<<"Given File too large";
        exit(0);
    }
    f.seekg(0,ios::beg);
    int ctr = 0;

    do
    {
        f>>c;
        for(int j=7;j>=0;j--)
        {
            data[ctr+j]+=(c%2);
            c/=2;
        }
        ctr+=8;
    }while(!f.eof());
    f.close();
}

void BMPimage::decode()             //test algorithm to decode files
{
    char save[100],msg;
    cout<<"Save decoded message as...";
    cin>>save;
    ofstream saveFile(save);

    for(unsigned int i=0;i<size;i+=8)
    {
        msg=0;
        for(int j=0;j<8;j++)
        {
            msg+=((data[i+j]%2)*pow(2,7-j));
        }
       // cout<<msg;
       if(msg==0)
       break;
       else if(msg!=32)
        saveFile<<msg;
        else if(msg==32)
            saveFile<<" ";

    }
    saveFile.close();

}

int BMPimage::getBitDepth()
{
        return bitDepth;
}


void BMPimage::EncodeLSB()
{
    char fileName[100],c;
    cout<<"Enter the name of the file to hide.";
    cin>>fileName;

    FILE *encFile;
    encFile = fopen(fileName,"r+");

    int index=0 , j=0;
    convertImage();
    while(!feof(encFile))
    {
        c = fgetc(encFile);

        for(j=7;j>=0;j--)
        {
            data[index+j] += (c%2);
            c/=2;
        }
        index+=8;
        if(index>=size)
        {
            cout<<"File is too large.";
            break;
        }

    }

    cout<<"Save encoded image as ...";
    cin>>fileName;
    writeBMP(fileName);
    fclose(encFile);

    cout<<"File successfully encoded.\n";


}

void BMPimage::DecodeLSB()
{


    char fileName[100];
    cout<<"Save file as...";
        cin>>fileName;
        FILE *saveFile = fopen(fileName,"a+");
        int index=0,c=0;
        do{
             c=0;
            for(int j=0;j<8;j++)
                c+=(data[index+j]%2)*pow(2,7-j);

            fputc(c,saveFile);
            index+=8;

        }while(c!=0);

        fclose(saveFile);
}


void BMPimage::pseudoEncode()
{
    long unsigned int index=0;
    char fileName[100],c;
    cout<<"Enter the name of file to hide.\n";
    cin>>fileName;
    FILE *f = fopen(fileName,"r+");
    pixel p;
    while(!feof(f))
    {
        index = (height*index + width)%size;
        //p = getPIXEL(index);
        c = fgetc(f);
        cout<<".";
        //cout<<(int)c <<" ";
        data[index] = c;
        //changePIXEL(p,index);
    }

    cout<<"Save encoded image as ...";
    cin>>fileName;
    writeBMP(fileName);
    fclose(f);

    cout<<"File successfully encoded.\n";
}

void BMPimage::pseudoDecode()
{
    long unsigned int index=0;
    char fileName[100],c;
    pixel p;
    //int i=0;
    cout<<"Save file as...";
        cin>>fileName;
        FILE *saveFile = fopen(fileName,"a+");
    do
    {
        index = (height*index + width)%size;
        //p = getPIXEL(index);
        c = data[index];
        fputc(c,saveFile);
        //i++;
    }while(c!=0);

    fclose(saveFile);

}


void BMPimage::blueEncode()             //has some bugs to be fixed
{
    long unsigned int index=channels;
    char fileName[100],c;
    cout<<"Enter the name of file to hide.\n";
    cin>>fileName;
    FILE *f = fopen(fileName,"r+");

    if(channels==3)
        data[0]=data[1]=data[2]=0;
    else if(channels==4)
        data[0]=data[1]=data[2]=data[3]=0;

    while(!feof(f))
    {
        if((int)data[index]>150)
        {
            c = fgetc(f);
            data[index+2]=c;
            data[index] = c;
        }
        index+=channels;
        if(index>size)
            break;
    }

    if(!feof(f))
    {
        cout<<"File is too large.\n";
        for(int i=0;i<channels;i++)
            data[i]=255;

    }
    else
    {
    cout<<"Save encoded image as ...";
    cin>>fileName;
    writeBMP(fileName);
    cout<<"File successfully encoded.\n";
    }
    fclose(f);


}

void BMPimage::blueDecode()
{
    long unsigned int index=channels;
    char fileName[100],c;

    bool checkEncode = true;
    for(int i=0;i<channels;i++)
        if(data[i]!=0)
            checkEncode = false;

    if(!checkEncode)
    {
        cout<<"No file is encoded in the image.\n";
    }
    else
    {
        cout<<"Save file as...";
        cin>>fileName;
        FILE *saveFile = fopen(fileName,"a+");

        while(c!=0)
        {
            if(data[index+2]==data[index])
            {
                c = data[index];
                fputc(c,saveFile);
            }
            index+=channels;
        }


        fclose(saveFile);
    }

}

