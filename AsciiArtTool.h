#ifndef ASCIIARTTOOL_H
#define ASCIIARTTOOL_H

#include <stdio.h>


/**
* asciiArtPrintEncoded: Writes to file the picture in a compressed format.
*
* TThe compressed format corresponds to the type returned from the
* RLEListExportString that's implemented in the RLEList.c file
*
* @return
*
*/
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);
#endif //ASCIIARTTOOL_H
