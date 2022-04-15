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
* The function writes into the received file the ASCIIArt image in it's compressed state
* that corresponds to the type returned from the RLEListExportString that's implemented in the RLEList.c file
*
* @param list - RLE list containing the the ASCIIArt image in a RLEList struct
* @param out_stream - FILE pointer to be used to write out the compressed ASCIIArt image into
*
* @return
* 	RLE_LIST_NULL_ARGUMENT if a NULL was sent as one of the parameters
* 	RLE_LIST_ERROR if the file was opened with wrong credentials
* 	RLE_LIST_SUCCESS if the compressed image was input successfully into the file
*/
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);

#endif //ASCIIARTTOOL_H
