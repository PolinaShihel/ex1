#include "AsciiArtTool.h"
#include "RLEList.h"

RLEList asciiArtRead(FILE* in_stream)
{
    if(!in_stream){

    }
    char currentLetter;
    RLEList compressedImage = RLEListCreate();
    do{
        currentLetter = fgetc(in_stream);
        RLEListAppend(compressedImage,currentLetter);
    }while (currentLetter != EOF);

    return compressedImage;
}


