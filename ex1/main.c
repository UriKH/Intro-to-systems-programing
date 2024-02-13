#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
void runCommand(char flag, FILE* sourcePath, FILE* targetPath);

char invertFunction(char character){
    if (character == ' '){
        return '@';
    }
    if (character == '@'){
        return ' ';
    }
    return character;
}

void runCommand(char flag, FILE* source, FILE* target){
    if (!source || !target){
        return;
    }

    RLEList list = asciiArtRead(source);

    if (RLEListSize(list) <= 0){
        RLEListDestroy(list);
        return;
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
    return;
}

int main(int argc, char* argv[]){
    if (argc != 4){
        return 0;
    }

    if (argv[1][0] != '-'){
        return 0;
    }

    if (strlen(argv[1]) == 2){
        FILE* source = fopen(argv[2], "r");
        FILE* target = fopen(argv[3], "w");
        runCommand(argv[1][1], source, target);
        if (source){
            fclose(source);
        }
        if (target){
            fclose(target);
        }
    }
    return 0;
}