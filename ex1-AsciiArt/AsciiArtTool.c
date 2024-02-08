#include <stdio.h>
#include <stdbool.h>
#include "RLEList.h"

RLEList asciiArtRead(FILE* in_stream){
    if (in_stream == NULL){
        return NULL; // -- ISSUE -- // Need to check on piazza what are we supposed to return
    }

    int character;
    RLEList fileData = RLEListCreate();
    RLEListResult result;

    while ((character = fgetc(in_stream)) != EOF){
        result = RLEListAppend(fileData, character);
        if (result != RLE_LIST_SUCCESS){
            // -- ISSUE --
            // return error?
            RLEListDestroy(fileData);
            return NULL;
        }
    }
    return fileData;
}

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream){
    if (out_stream == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }

    char character;
    RLEListResult result;
    
    for (int i = 0; i < RLEListSize(list); i++){
        character = RLEListGet(list, i, &result);
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
    if (out_stream == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }

    RLEListResult result;
    char* string = RLEListExportToString(list, &result);

    if (result != RLE_LIST_SUCCESS){
        return result;
    }

    if (fprintf(out_stream, string) < 0){ // -- ISSUE --
        return RLE_LIST_ERROR; // -- ISSUE --
    }
    return RLE_LIST_SUCCESS;
}