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

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream)
{
    if(!list||!out_stream){
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEListResult errorCode;
    char* compressedList = RLEListExportToString(list,&errorCode);
    if(errorCode != RLE_LIST_SUCCESS){
        return  errorCode;
    }
    if(0 > fprintf(out_stream, "%s", compressedList))
        return RLE_LIST_ERROR; //if the file was opened with the wrong permissions that don't allow writing
    free(compressedList);
    return RLE_LIST_SUCCESS;
}



