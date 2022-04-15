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
 * The function prints out the compressed format corresponds to the type returned from the
 * RLEListExportString that's implemented in the RLEList.c file into a file that was received as a pointer
 *
 * @param list - RLE list containing the ASCIIArt image in a RLEList struct
 * @param out_stream  - FILE pointer to e file chosen to contain the compressed ascii image format
 * @return
 * 	RLE_LIST_NULL_ARGUMENT if a NULL was sent as one of the parameters
 * 	RLE_LIST_OUT_OF_MEMORY if an allocation failed in the function used to create the compressed image
 * 	RLE_LIST_SUCCESS if the compressed list was input into the file successfully
 * 	RLE_LIST_ERROR if the file was opened with insufficient privileges
 */
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);

#endif //ASCIIARTTOOL_H
