#include"bitmap.h"

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

    size = 3 * width * height;
    data = new unsigned char[size]; // allocate 3 bytes per pixel
    fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
    fclose(f);

    for(i = 0; i < size; i += 3)
    {
            unsigned char tmp = data[i];
            data[i] = data[i+2];
            data[i+2] = tmp;
    }
}

void BMPimage::writeBMP(char *filename)
{

    int i=0;
    FILE *f = fopen(filename,"wb");

   // unsigned char *newdata = new unsigned char[size];
   // newdata = data;
    for(i = 0; i < size; i += 3)
    {
            unsigned char tmp = data[i];
            data[i] = data[i+2];
            data[i+2] = tmp;
    }
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
    int index = (y*width+x)*3;
    pixel p = {data[index],data[index+1],data[index+2]};
    return p;
}

void BMPimage::changePIXEL( pixel p, int x, int y)
{
    int index = (y*width+x)*3;
    data[index] = p.r;
    data[index+1] = p.g;
    data[index+2] = p.b;
}

void BMPimage::convertImage()
{
    for(int i=0;i<size;i++)
        if(data[i]%2)
            data[i]--;
}


void BMPimage::encode(char *encFile)
{
    convertImage();
    fstream f(encFile);
    char c;
    long int sizeFile;

    f.seekg(0,ios::end);
    sizeFile = f.tellg();
    f.seekg(0,ios::beg);
    int ctr = 0;

    while(!f.eof())
    {
        f>>c;
        for(int j=7;j>=0;j--)
        {
            data[ctr+j]+=(c%2);
            c/=2;
        }
        ctr+=8;
    }
    for(int i=0;i<8;++i)
    {
        data[i+ctr]+=1;
    }
    f.close();
}

void BMPimage::decode()
{
    char save[100],msg;
    cout<<"Save decoded message as...";
    cin>>save;
    ofstream saveFile(save);

    for(int i=0;i<size;i+=8)
    {
        msg=0;
        for(int j=0;j<8;j++)
        {
            msg+=((data[i+j]%2)*pow(2,j));
        }
       // cout<<msg;
       if(msg==255)
       break;
        saveFile<<msg;

    }
    saveFile.close();

}
