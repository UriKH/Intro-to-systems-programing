#include <stdio.h>
#include <stdbool.h>
#include "RLEList.h"


/**
*   asciiArtRead: reads and compresses the given file using RLE.
*
* @param in_stream - The file containing the ACII image.
* @return
* 	RLE_LIST that contains the file compressed data.
*/
RLEList asciiArtRead(FILE* in_stream);

/**
*   asciiArtPrint: writes data from RLEList to the given file.
*
* @param list - RLE list, containing data for the file.
* @param out_stream - The file the function will update.
* @return
* 	RLE_LIST_NULL_ARGUMENT if a NULL was sent as one of the parameters.
* 	RLE_LIST_SUCCESS If the function wrote to the file successfully.
*/
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);

/**
*   asciiArtPrintEncoded: writes compressed data from RLEList to the given file.
*
* @param list - RLE list, containing compressed data for the file.
* @param out_stream - The file the function will update.
* @return
* 	RLE_LIST_NULL_ARGUMENT if a NULL was sent as one of the parameters.
* 	RLE_LIST_SUCCESS if the function wrote to the file successfully. 
*/
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);