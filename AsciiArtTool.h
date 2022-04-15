#ifndef ASCIIARTTOOL_H
#define ASCIIARTTOOL_H

#include <stdio.h>

/**
  The following functions are available :
* asciiArtRead - Creates an RLEList out of a file
* asciiArtPrint: Writes the whole picture to the file stream using the
* given list that represents the compressed picture
* asciiArtPrintEncoded: Writes to file the picture in a compressed format.
* /

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
* asciiArtPrint: Writes the whole picture to the file stream using the
* given list that represents the compressed picture
*
* @list - An RLEList that contains the file's characters
* @out_stream - The stream that the picture will be written to
* @return
* 	RLE_LIST_NULL_ARGUMENT if a NULL was sent as one of the parameters
* 	RLE_LIST_OUT_OF_MEMORY if a memory allocation has failed
* 	RLE_LIST_SUCCESS if the picture has been written to the file successfully
*/
RLEListResult asciiArtPrint(RLEList list, FILE* out_stream);

/**
* asciiArtPrintEncoded: Writes to file the picture in a compressed format.
*
* The compressed format corresponds to the type returned from the
* RLEListExportString that's implemented in the RLEList.c file
*
* @return
*
*/
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);
#endif //ASCIIARTTOOL_H
