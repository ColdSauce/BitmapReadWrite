#include "main.h"


//The following code is taken from http://stackoverflow.com/questions/14279242/read-bitmap-file-into-structure. 
//I wanted to write out the program and then look at it in an attempt to learn C a little bit better.

unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader){
    FILE *filePtr;
    BITMAPFILEHEADER bitmapFileHeader;
    unsigned char *bitmapImage;
    unsigned char tempRGB;
    
    filePtr = fopen(filename,"rb");
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
    bitmapImage = (unsigned char*)malloc(bitmapInfoHeader->biSizeImage);

    if(!bitmapImage){
        //if it's 0,
        free(bitmapImage);
        fclose(filePtr);
        return NULL;
    }
    int amountOfElements = bitmapInfoHeader->biSizeImage / 8;
    //now we actually read the bitmap data.
    fread(bitmapImage,bitmapInfoHeader->biSizeImage,amountOfElements,filePtr);

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

int main(){
   BITMAPINFOHEADER b;
   unsigned char* bitmapData;
   bitmapData = LoadBitmapFile("test.bmp", &b);
   printf("%u",*bitmapData);
   


}
