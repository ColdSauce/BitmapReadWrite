#include "main.h"

int main(){
    
}

//The following code is taken from http://stackoverflow.com/questions/14279242/read-bitmap-file-into-structure. 
//I wanted to write out the program and then look at it in an attempt to learn C a little bit better.


#pragma pack(push, 1)

typedef struct tagBITMAPFILEHEADER{
    WORD bfType; //tells you what the file type is.
}
    


#pragma pack(pop)

#pragma pack(push, 1)
typedef struct tagBITMAPINFOHEADER{
    DWORD biSize;
    LONG biWidth;
    LONG biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD BiSizeImage;
    LONG biXPelsPerMeter;
    LONG biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD BiClrImportant;
} BITMAPINFOHEADER;


#pragma pack(pop)

unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader){
    FILE *filePointer;
    BITMAPFILEHEADER bitmapFileHeader;
    unsigned char *bitmapImage;
    unsigned char tempRGB;
    
    filePtr = ropen(filename,"rb");
    if(filePtr == NULL){
        return NULL;
    }

    //So now the program has to read the header so that it can see if 
}
