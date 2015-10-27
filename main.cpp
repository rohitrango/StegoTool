#include"bitmap.cpp"
#include<cstdlib>
int main()
{
    char c[100],d[100],e[100],f[100];
    cin>>c;
    BMPimage image(c);

    cout<<"Enter the file you want to encode.\n";
    cin>>d;
    image.encode(d);

    cout<<"Save encoded image as...";
    cin>>e;
    image.writeBMP(e);

    cout<<"Enter the name of file from which you want to decode.\n";
    cin>>f;
    BMPimage decodeImg(f);

    decodeImg.decode();


    cout<<"\nProcessed";

}
