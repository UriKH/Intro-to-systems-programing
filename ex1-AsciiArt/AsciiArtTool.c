#include <stdio.h>
#include <stdbool.h>
#include "RLEList.h"

RLEList asciiArtRead(FILE* in_stream){
    if (in_stream == NULL){
        return NULL; // Need to check on piazza what are we supposed to return
    }

    int character;
    RLEList fileData = RLEListCreate();
    RLEListResult result;

    while ((character = fgetc(in_stream)) != EOF){
        result = RLEListAppend(fileData, character);
        if (result){
            RLEListDestroy(fileData);
            return NULL;
        }
        // return error????
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
    if (out_stream == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }

    RLEListResult result;
    char* string = RLEListExportToString(list, &result);

    if (result != RLE_LIST_SUCCESS){
        return result;
    }

    if (fprintf(out_stream, string) < 0){ // fix this
        return RLE_LIST_ERROR; //what to return???
    }
    return RLE_LIST_SUCCESS;
}