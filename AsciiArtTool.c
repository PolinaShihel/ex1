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

RLEListResult asciiArtPrint(RLEList list, FILE* out_stream)
{
    if (!list || !out_stream) {
        return RLE_LIST_NULL_ARGUMENT;
    }

    char* picture = malloc((RLEListSize(list) + 1) * sizeof(char));
    if (!picture) {
        return RLE_LIST_OUT_OF_MEMORY;
    }

    char* p = picture;
    while (list)
    {
        while (list->letterAppearances--)
        {
            *p = list->letter;
            p++;
        }
    }
    *p = '\0';

    int fputsResult = fputs(picture, out_stream) == EOF ? RLE_LIST_ERROR : RLE_LIST_SUCCESS;
    free(picture);
    return fputsResult;
}

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream)
{
    if(!list||!out_stream){
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEListResult errorCode;
    char* compressedImage = RLEListExportToString(list,&errorCode);
    if(!(errorCode = RLE_LIST_SUCCESS))
    {
        return errorCode;
    }
    if(0 > fprintf(out_stream,"%s",compressedImage)){
        return RLE_LIST_ERROR;//if the file was opened with insufficient privileges
    }
    free(compressedImage);
    return RLE_LIST_SUCCESS;
}

