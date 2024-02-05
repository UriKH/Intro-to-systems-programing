#include <stdio.h>
#include <stdbool.h>
#include "RLEList.h"

RLEList asciiArtRead(FILE* in_stream){
    FILE* file = fopen(in_stream, "r");

    if(file == NULL){
        return NULL; // Need to check on piazza what are we supposed to return
    }

    int character;
    RLEList fileData = RLEListCreate();
    
    while((character = fgetc(file) != EOF)){
        RLEListAppend(fileData, (char)character);
    }
    
    RLEListDestroy(fileData);
    fclose(file);
    return fileData;
}

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream){
    FILE* file = fopen(out_stream, "w");

    if(file == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }

    char character;

    for (int i = 0; i < RLEListSize(list); i++) {
        character = RLEListGet(list, i, RLE_LIST_SUCCESS); // not sure what the function should get
        if (fputc(character, file) == EOF) {
            fclose(file);
            return RLE_LIST_NULL_ARGUMENT;
        }
    }

    fclose(file);
    return RLE_LIST_SUCCESS;
}