#include "AsciiArtTool.h"

RLEList asciiArtRead(FILE* inStream)
{
    if (!inStream) {//instructed to return null if the file pointer is invalid
        return NULL;
    }
    char currentLetter = fgetc(inStream);
    RLEList compressedImage = RLEListCreate();
    if (!compressedImage) {
        return NULL;
    }
    while (currentLetter != EOF){
        if (RLEListAppend(compressedImage, currentLetter) != RLE_LIST_SUCCESS) {
            return NULL;
        }
        currentLetter = fgetc(inStream);
    }
    return compressedImage;
}

RLEListResult asciiArtPrint(RLEList list, FILE* outStream)
{
    if (!list || !outStream) {
        return RLE_LIST_NULL_ARGUMENT;
    }

    char* picture = malloc((RLEListSize(list) + 2) * sizeof(char));
    if (!picture) {
        return RLE_LIST_OUT_OF_MEMORY;
    }

    char* picturePointer = picture;
    int listSize = RLEListSize(list);
    for (int i = 0; i < listSize; i++) {
        RLEListResult result;
        char currentLetter = RLEListGet(list, i, &result);
        if (result != RLE_LIST_SUCCESS) {
            return result;
        }
        *picturePointer = currentLetter;
        picturePointer++;
    }
    *picturePointer = '\n';
    *picturePointer = '\0';

    int fputsResult = fputs(picture, outStream) == EOF ? RLE_LIST_ERROR : RLE_LIST_SUCCESS;
    free(picture);
    return fputsResult;
}

RLEListResult asciiArtPrintEncoded(RLEList list, FILE* outStream)
{
    if (!list || !outStream) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEListResult errorCode;
    char* compressedImage = RLEListExportToString(list, &errorCode);
    if (errorCode != RLE_LIST_SUCCESS) {
        return errorCode;
    }
    fprintf(outStream, "%s\n", compressedImage);
    free(compressedImage);
    return RLE_LIST_SUCCESS;
}



