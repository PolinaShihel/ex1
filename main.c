#include <stdio.h>
#include "RLEList.h"
#include "AsciiArtTool.h"

#define EXPECTED_ARGUMENTS_COUNT 3

#define ENCODED_FLAG -e
#define INVERTED_FLAG -i

#define FLAG_ARG_INDEX 0
#define SOURCE_ARG_INDEX 1
#define TARGET_ARG_INDEX 2

#define FILE_ERROR -1
#define LETTER_TO_INVERT ' '
#define LETTER_INVERTED '@'

char invertedRLEList(char originalLetter)
{
    if(!originalLetter){
        return RLE_LIST_NULL_ARGUMENT;
    }
    if(originalLetter== LETTER_TO_INVERT){
        return LETTER_INVERTED;
    }
}

int main(int argc, char** argv)
{
    if (argc == EXPECTED_ARGUMENTS_COUNT) {
        FILE* sourceFileStream = fopen(argv[SOURCE_ARG_INDEX], "%r");
        FILE* targetFileStream = fopen(argv[TARGET_ARG_INDEX], "%w");
        RLEList orignialArt = asciiArtRead(sourceFileStream);
        if(!orignialArt){
            return FILE_ERROR;
        }
        if (argv[FLAG_ARG_INDEX] == ENCODED_FLAG) {
            if(asciiArtPrint(orignialArt, targetFileStream)!=RLE_LIST_SUCCESS){
                return NULL;
            }
        }
        else if (argv[FLAG_ARG_INDEX == INVERTED_FLAG]) {
            MapFunction invertedASCIIArt = &invertedRLEList;
            RLEListMap(orignialArt,invertedASCIIArt);
            asciiArtPrintEncoded(orignialArt,targetFileStream);
        }
        else{//if the provided parameter is not fitting either options
            fclose(sourceFileStream);
            fclose(targetFileStream);
            return NULL;
        }
        fclose(sourceFileStream);
        fclose(targetFileStream);
    }
    else{//if the number of arguments provided is not as expected
        return NULL;
    }
    return 0;
}