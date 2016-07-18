#include"bitmap.h"


BMPimage::~BMPimage()
{
    delete[] data;
}

BMPimage::BMPimage(char* filename)
{
    FILE* f = fopen(filename, "rb");
    if(!f)
    {
        //cout<<"Invalid name of given file \nExiting interface\n";
        size= 0;
        return;
    }

    // read the 54-byte header
    fread(info, sizeof(unsigned char), 54, f);

    // extract image height, width, bitDepth, channels and size from header
    width = *(int*)&info[18];
    height = *(int*)&info[22];
    bitDepth = *(int*)&info[28];
    channels = bitDepth/8;
    size = *(int*)&info[34];

    data = new unsigned char[size]; // allocate array of 1 byte per r or g or b value per pixel
    fread(data, 1, size, f); // read the rest of the data at once
    fclose(f);

}

void BMPimage::writeBMP(char *filename)
{

    FILE *f = fopen(filename,"wb");

    fwrite(info, 1, 54, f);
    fwrite(data, 1, size, f);
    fclose(f);
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

void BMPimage::encode(char *encFile)     //just a test algorithm to hide files
{
    fstream f(encFile);
    if(!f)
    {
        cout<<"Invalid name of given file \nExiting interface.\n";
        exit(0);
    }
    char c;
    unsigned long int sizeFile;
    f.seekg(0,ios::end);
    sizeFile = f.tellg();
    if(sizeFile>=size/8)
    {
        cout<<"ERROR : Given File too large\nExiting Interface.\n";
        exit(0);
    }
    f.seekg(0,ios::beg);
    int ctr = 0;

    do
    {
        f>>c;
        for(int j=7;j>=0;j--)
        {
            data[ctr+j]=(data[ctr+j]/2)*2;
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
    cout<<"\tSave decoded message as : ";
    cin>>save;
    ofstream saveFile(save);
    if(!saveFile)
    {
        cout<<"Invalid name of given file \nExiting interface.\n";
        exit(0);
    }
    for(unsigned int i=0;i<size;i+=8)
    {
        msg=0;
        for(int j=0;j<8;j++)
        {
            msg+=((data[i+j]%2)*pow(2,7-j));
        }
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


bool BMPimage::filterEncode()
{
    long unsigned int count=0,*laplace;
    laplace=new long unsigned int[size];
    for(int i=1;i<width-1;++i)
    {
        for(int j=1;j<height-1;++j)
        {
            unsigned char p;
            p = max(this->getPIXEL(i,j-1).r,(max(this->getPIXEL(i,j-1).b,this->getPIXEL(i,j-1).g)));
            p += max(this->getPIXEL(i,j+1).r,(max(this->getPIXEL(i,j+1).b,this->getPIXEL(i,j+1).g)));
            p += max(this->getPIXEL(i-1,j).r,(max(this->getPIXEL(i-1,j).b,this->getPIXEL(i-1,j).g)));
            p += max(this->getPIXEL(i+1,j).r,(max(this->getPIXEL(i+1,j).b,this->getPIXEL(i+1,j).g)));
            p -= 4*max(this->getPIXEL(i,j).r,(max(this->getPIXEL(i,j).b,this->getPIXEL(i,j).g)));
            if(p<30)
            {
                laplace[count]=(j*width+i)*channels;
                ++count;
            }
        }
    }
    cout<<"\tEnter name of file to be processed : ";
    char name[25],c;
    cin>>name;
    bool *hash;
    hash = new bool[count];
    for(unsigned int i=0;i<count;++i)
    hash[i]=false;
    ifstream f(name,ios::ate|ios::binary);
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
    cout<<"\tEnter Password for seed(max 20 characters) : ";
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
                w%=count;
            }while(hash[w]);
            hash[w]=true;
            data[laplace[w]]=(data[laplace[w]]/2)*2;
            data[laplace[w]] += (c%2);
            c/=2;
        }
    }
    data[2] = sizeFile%256;
    sizeFile/=256;
    data[1] = sizeFile%256;
    sizeFile/=256;
    data[0] = sizeFile%256;
    cout<<"\tSave processed image as(*.bmp) : ";
    char fileName[100];
    cin>>fileName;
    writeBMP(fileName);
    f.close();
    cout<<"\tFile successfully processed.\n";
    delete[] hash;
    delete[] laplace;
    return true;
}
bool BMPimage::filterDecode()
{
    cout<<"\tEnter host's original image name(*.bmp) : ";
    char hostname[25];
    cin>>hostname;
    BMPimage host(hostname);
    long unsigned int count=0,*laplace;
    laplace = new long unsigned int[size];
    for(int i=1;i<width-1;++i)
    {
        for(int j=1;j<height-1;++j)
        {
            unsigned char p;
            p = max(host.getPIXEL(i,j-1).r,(max(host.getPIXEL(i,j-1).b,host.getPIXEL(i,j-1).g)));
            p += max(host.getPIXEL(i,j+1).r,(max(host.getPIXEL(i,j+1).b,host.getPIXEL(i,j+1).g)));
            p += max(host.getPIXEL(i-1,j).r,(max(host.getPIXEL(i-1,j).b,host.getPIXEL(i-1,j).g)));
            p += max(host.getPIXEL(i+1,j).r,(max(host.getPIXEL(i+1,j).b,host.getPIXEL(i+1,j).g)));
            p -= 4*max(host.getPIXEL(i,j).r,(max(host.getPIXEL(i,j).b,host.getPIXEL(i,j).g)));
            if(p<30)
            {
                laplace[count]=(j*width+i)*channels;
                ++count;
            }
        }
    }

    long unsigned int fileSize;
    cout<<"\tSave retreived file as : ";
    char name[25],c;
    cin>>name;
    bool *hash;
    hash = new bool[count];
    for(unsigned int i=0;i<count;++i)
    hash[i]=false;
    FILE *saveFile = fopen(name,"wb");
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
                w%=count;
            }while(hash[w]);
            hash[w]=true;
            c+=(data[laplace[w]]%2)*pow(2,j);
        }
        fwrite(&c,1,1,saveFile);
    }

    fclose(saveFile);
    cout<<"\tFile retreived successfully in : "<<name<<endl;
    delete[] hash;
    delete[] laplace;
    return true;
}
