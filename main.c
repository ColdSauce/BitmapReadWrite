#include "main.h"

int main(){
   BITMAPINFOHEADER b;
   unsigned char* bitmapData;
   bitmapData = LoadBitmapFile("test.bmp", &b);
   


}

//The following code is taken from http://stackoverflow.com/questions/14279242/read-bitmap-file-into-structure. 
//I wanted to write out the program and then look at it in an attempt to learn C a little bit better.


#pragma pack(push, 1)

typedef struct tagBITMAPFILEHEADER{
    WORD bfType; //tells you what the file type is.
    DWORD bfSize; //Size of the bitmap file in bytes
    WORD bfReserved1; //this is reserved. Must be 0
    WORD bfReserved2; //this is reserved. Must be 0
    DWORD bOffBits; //specifies the offset from the bitmapfileheader to the bitmap bits.
}BITMAPFILEHEADER;
    


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

    //So now the program has to read the header so that it can see if the file is actually a bitmap.
    //Bitmaps have an id of 0x4D42 so if this file doesn't have that id, it's not a bitmap.
    fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER),1,filePtr);
    if(bitmapFileHeader.bfType != 0x4D42){
        fclose(filePtr);
        return NULL;
    }

    fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER),1,filePtr);

    //Then we gotta move the "cursor" of the file reader to the actual position where it should be for the bitmap data. This is found in bitmapFileHeader off bits. It gives you the offset in bits.
    fseek(filePtr, bitmapFileHeader.bfOffBits,SEEK_SET);

    //Then it's important to allocate enough memory for the bitmap image itself.
    biitmapImage = (unsigned char*)malloc(bitmapInfoHeader->biSizeImage);

    if(!bitmapImage){
        //if it's 0,
        free(bitmapImage);
        fclose(filePtr);
        return NULL;
    }
    //now we actually read the bitmap data.
    fread(bitmapImage,bitmapInfoHeader->biSizeImage,filePtr);

    //make sure bitmap image data was read.
    if(bitmapImage == NULL){
        fclose(filePtr);
        return NULL; 
    }

    //For some strange reason, bitmaps are BGR so it's important to swap those values.
    for(int imageIdx = 0; imageIdx < bitmapInfoHeader->biSizeImage;imageIdx+=3){
        tempRGB = bitmapImage[imageIdx];
        bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
        bitmapImage[imageIdx + 2] = tempRGB;
    }

    fclose(filePtr);
    return bitmapImage;
}
