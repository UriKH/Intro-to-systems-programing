#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "RLEList.h"
#include "AsciiArtTool.h"


/**
 * Swap space -> @ and @ -> space.
 * @param character: The character to invert
 * @returns at. if was space, space if was at., otherwise returns the input
*/
char invertFunction(char character);

/**
 * Encode an ascii art file or inverts the spaces and @ symbols
 * @param flag: e or i for encode or invert.
 * @param source: pointer to the source file
 * @param target: pointer to the target file
*/
void runCommand(char flag, char* sourcePath, char* targetPath);

char invertFunction(char character){
    if (character == ' '){
        return '@';
    }
    if (character == '@'){
        return ' ';
    }
    return character;
}

void runCommand(char flag, char* sourcePath, char* targetPath){
    FILE* source = fopen(sourcePath, "r"), *target = NULL;
    RLEList list = asciiArtRead(source);

    if (RLEListSize(list) > 0){
        target = fopen(targetPath, "w");
    }
    
    switch (flag){
    case 'e':
        asciiArtPrintEncoded(list, target);
        break;
    case 'i':
        if (RLEListMap(list, invertFunction) == RLE_LIST_SUCCESS){
            asciiArtPrint(list, target);
        }
        break;
    }

    RLEListDestroy(list);
    fclose(source);
    fclose(target);
    return;
}

int main(int argc, char* argv[]){
    assert(argc == 4);
    if (argc != 4){
        return 0;
    }

    assert(argv[1][0] == '-');
    if (argv[1][0] != '-'){
        return 0;
    }

    assert(strlen(argv[1]) == 2);
    if (strlen(argv[1]) == 2){
        runCommand(argv[1][1], argv[2], argv[3]);
    }
    return 0;
}