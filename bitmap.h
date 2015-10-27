#include <iostream>
#include <stdio.h>
#include<fstream>
#include<cmath>
using namespace std;
#ifndef BITMAP_VAR
#define BITMAP_VAR
#pragma pack(1)
struct pixel
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
};
class BMPimage
{
    int i;
    unsigned char info[54];
    int width;
    int height;
    unsigned int size;
    unsigned char* data;

    public:

    BMPimage(char *filename);           //constructor
    void writeBMP(char *filename);      //write into file
    const unsigned int getSIZE();       //returns the size of the file
    const int getWIDTH();               //returns the width of the image
    const int getHEIGHT();              //returns the height of the image
    pixel getPIXEL( int x, int y);
    void changePIXEL( pixel p, int x, int y);
    void convertImage();
    void encode(char* encFile);
    void decode();
    ~BMPimage();
};

#pragma pack(pop)
#endif
