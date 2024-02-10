#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "RLEList.h"


RLEList asciiArtRead(FILE* in_stream){
    if (in_stream == NULL){
        return NULL;
    }

    int character;
    RLEList fileData = RLEListCreate();

    while ((character = fgetc(in_stream)) != EOF){
        if (RLEListAppend(fileData, character) != RLE_LIST_SUCCESS){
            RLEListDestroy(fileData);
            return NULL;
        }
    }
    return fileData;
}

RLEListResult asciiArtPrint(RLEList list, FILE* out_stream){
    if (out_stream == NULL || RLEListSize(list) <= 0){ // -- ISSUE --
        return RLE_LIST_NULL_ARGUMENT;
    }

    char character;
    RLEListResult result;

    for (int i = 0; i < RLEListSize(list); i++){
        character = RLEListGet(list, i, &result); // not sure what the function should get
        if (result != RLE_LIST_SUCCESS){
            return result;
        }

        if (fputc(character, out_stream) == EOF){
            return RLE_LIST_NULL_ARGUMENT;
        }
    }
    return RLE_LIST_SUCCESS;
}

RLEListResult asciiArtPrintEncoded(RLEList list, FILE* out_stream){
    if (out_stream == NULL || RLEListSize(list) <= 0){ // -- ISSUE --
        return RLE_LIST_NULL_ARGUMENT;
    }

    RLEListResult result;
    char* string = RLEListExportToString(list, &result);

    if (result != RLE_LIST_SUCCESS){
        return result;
    }
    
    fprintf(out_stream, string);
    free(string);
    return RLE_LIST_SUCCESS;
}