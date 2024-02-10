#ifndef ASCII_ART_TOOL_H
#define ASCII_ART_TOOL_H

#include <stdio.h>
#include <stdbool.h>
#include "RLEList.h"


/**
*   asciiArtRead: reads and compresses the given file using RLE.
*
* @param in_stream - The file containing the ACII image.
* @return
* 	RLE_LIST that contains the file compressed data.
*   Empty list if no data found.
*/
RLEList asciiArtRead(FILE* in_stream);

/**
*   asciiArtPrint: writes decoded data from RLEList to the given file.
*
* @param list - RLE list, containing compressed data for the file.
* @param out_stream - The file the function will update.
* @return
* 	RLE_LIST_NULL_ARGUMENT if a NULL was sent as one of the parameters.
* 	RLE_LIST_SUCCESS If the function wrote to the file successfully.
*/
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);

/**
*   asciiArtPrintEncoded: writes compressed data from RLEList to the given file
*   or the list was empty.
*
* @param list - RLE list, containing compressed data for the file.
* @param out_stream - The file the function will update.
* @return
* 	RLE_LIST_NULL_ARGUMENT if a NULL was sent as one of the parameters or the
*   list was empty.
* 	RLE_LIST_SUCCESS if the function wrote to the file successfully.
*/
RLEListResult asciiArtPrintEncoded(RLEList list, FILE* out_stream);

#endif