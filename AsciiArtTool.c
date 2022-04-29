#include "AsciiArtTool.h"

#define ENTER_CHARACTER_LEN 1
#define NULL_CHARACTER_LEN 1

RLEList asciiArtRead(FILE* inStream)
{
    if (!inStream) {
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

    char* picture = malloc((RLEListSize(list) + ENTER_CHARACTER_LEN + NULL_CHARACTER_LEN) * sizeof(char));
    if (!picture) {
        return RLE_LIST_OUT_OF_MEMORY;
    }

    char* ptr = picture;
    int listSize = RLEListSize(list);
    for (int i = 0; i < listSize; i++) {
        RLEListResult result;
        char currentLetter = RLEListGet(list, i, &result);
        if (result != RLE_LIST_SUCCESS) {
            return result;
        }
        *ptr = currentLetter;
        ptr++;
    }
    *ptr = '\n';
    *ptr = '\0';

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
    fprintf(outStream, "%s", compressedImage);
    free(compressedImage);
    return RLE_LIST_SUCCESS;
}



