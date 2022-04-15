#ifndef ASCIIARTTOOL_H
#define ASCIIARTTOOL_H

#include <stdio.h>

/**
 * asciiArtRead: creates an RLEList out of a file
 *
 * The function receives a FILE pointer and reads the contents of the file letter
 * by letter and appends each letter to a created empty RLEList.
 *
 * @param in_stream - FILE pointer to be used to get the contents of the file holding the asciiArt
 * @return
 *       RLE list containing the ASCIIArt in it's compressed state
 */
RLEList asciiArtRead(FILE* in_stream);



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
