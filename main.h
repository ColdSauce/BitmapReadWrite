#include <stdio.h>
#include <stdlib.h>

#pragma pack(push, 1)

typedef struct {
    unsigned short bfType; //tells you what the file type is.
    unsigned int bfSize; //Size of the bitmap file in bytes
    unsigned int bfReserved1; //this is reserved. Must be 0
    unsigned int bfReserved2; //this is reserved. Must be 0
    unsigned int bfOffBits; //specifies the offset from the bitmapfileheader to the bitmap bits.
}BITMAPFILEHEADER;
    


#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
    unsigned int biSize;
    int biWidth;
    int  biHeight;
    unsigned short biPlanes;
    unsigned short biBitCount;
    unsigned int biCompression;
    unsigned int  biSizeImage;
    int biXPelsPerMeter;
    int biYPelsPerMeter;
    unsigned int  biClrUsed;
    unsigned int biClrImportant;
}BITMAPINFOHEADER;


#pragma pack(pop)


int main();

unsigned char* LoadBitMapFile(char* filename, BITMAPINFOHEADER* bitmapInfoHeader);

