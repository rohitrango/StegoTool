#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <cstdio>

#ifdef WIN32
    #include <algorithm>
#endif

using namespace std;

#ifndef BITMAP_VAR
#define BITMAP_VAR

#pragma pack(push,1)

struct pixel
{
    unsigned char b;
    unsigned char g;
    unsigned char r;
    unsigned char a;

    pixel()
    {
        r=g=b=a=0;
    }
};
class BMPimage
{
    int i;
    unsigned char info[54] , bitDepth;
    int width;
    int height;
    unsigned int size;
    unsigned char* data;
    int channels;

    public:

    bool pseudoEncode();
    bool pseudoDecode();
    bool filterEncode();
    bool filterDecode();
    bool EncodeLSB();
    bool DecodeLSB();
    BMPimage(char *filename); //constructor
    int getBitDepth();
    void writeBMP(char *filename);      //write into file
    const unsigned int getSIZE();       //returns the size of the file
    const int getWIDTH();               //returns the width of the image
    const int getHEIGHT();              //returns the height of the image
    pixel getPIXEL( int x, int y);
    pixel getPIXEL(int index);
    void changePIXEL( pixel p, int x, int y);
    void changePIXEL( pixel p, int index);
    void encode(char* encFile);
    void decode();
    ~BMPimage();
};


#pragma pack(pop)
#endif
