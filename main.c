#include "AsciiArtTool.h"
#include <assert.h>
#include <string.h>

#define ERROR_CODE -1
#define EXPECTED_ARGUMENTS_COUNT 4

#define ENCODED_FLAG "-e"
#define INVERTED_FLAG "-i"

#define FLAG_ARG_INDEX 1
#define SOURCE_ARG_INDEX 2
#define TARGET_ARG_INDEX 3

#define SPACE_CHARACTER ' '
#define AT_CHARACTER '@'

char invertedRLEList(char originalLetter) {
    switch (originalLetter) {
        case AT_CHARACTER: {
            return SPACE_CHARACTER;
        }
        case SPACE_CHARACTER: {
            return AT_CHARACTER;
        }
        default: {
            return originalLetter;
        }
    }
}

int main(int argc, char** argv) {
    assert(argc == EXPECTED_ARGUMENTS_COUNT);
    if(argc != EXPECTED_ARGUMENTS_COUNT){
        printf("insufficient amount of parameters given");
        return  ERROR_CODE;
    }
    FILE* sourceFileStream = fopen(argv[SOURCE_ARG_INDEX], "r");
    FILE* targetFileStream = fopen(argv[TARGET_ARG_INDEX], "w");
    RLEList orignialArt = asciiArtRead(sourceFileStream);
    if (!orignialArt) {
        RLEListDestroy(orignialArt);
        return ERROR_CODE;
    }

    if (strcmp(argv[FLAG_ARG_INDEX], ENCODED_FLAG) == 0) {
        if(asciiArtPrintEncoded(orignialArt, targetFileStream) != RLE_LIST_SUCCESS) {
            RLEListDestroy(orignialArt);
            return ERROR_CODE;
        }

    }
    else if (strcmp(argv[FLAG_ARG_INDEX], INVERTED_FLAG) == 0) {
        if (RLEListMap(orignialArt, invertedRLEList) != RLE_LIST_SUCCESS ||
            asciiArtPrint(orignialArt, targetFileStream) != RLE_LIST_SUCCESS) {
            RLEListDestroy(orignialArt);
            return ERROR_CODE;
        }
    }
    else {//if the provided parameter is not fitting either options
        fclose(sourceFileStream);
        fclose(targetFileStream);
        RLEListDestroy(orignialArt);
        return ERROR_CODE;
    }

    RLEListDestroy(orignialArt);
    fclose(sourceFileStream);
    fclose(targetFileStream);
    return 0;
}