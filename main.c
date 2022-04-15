#include <stdio.h>
#include "RLEList.h"
#include "AsciiArtTool.h"

#define EXPECTED_ARGUMENTS_COUNT 3

#define ENCODED_FLAG -e
#define INVERTED_FLAG -i

#define FLAG_ARG_INDEX 0
#define SOURCE_ARG_INDEX 1
#define TARGET_ARG_INDEX 2

int main(int argc, char** argv)
{
    if (argc == EXPECTED_ARGUMENTS_COUNT) {
        FILE* sourceFileStream = fopen(argv[SOURCE_ARG_INDEX], "%r");
        FILE* targetFileStream = fopen(argv[TARGET_ARG_INDEX], "%w");
        if (argv[FLAG_ARG_INDEX] == ENCODED_FLAG) {
            asciiArtPrint(asciiArtRead(sourceFileStream), targetFileStream);
        }
        else {
            //TODO: invert the required characters (don't encode the picture afterwards)
        }
    }

    //TODO: decide how to behave when argc != 3
  
    return 0;
}