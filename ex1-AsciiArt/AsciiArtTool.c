#include <stdio.h>
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

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream){
    if (out_stream == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }

    for (int i = 0; i < RLEListSize(list); i++){
        fputc(RLEListGet(list, i, NULL), out_stream);
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

    fprintf(out_stream, string);
    return RLE_LIST_SUCCESS;
}