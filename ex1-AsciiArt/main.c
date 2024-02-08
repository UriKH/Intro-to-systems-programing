#include <stdio.h>
#include <stdlib.h>
#include "RLEList.h"
#include "AsciiArtTool.h"


RLEListResult runCommand(char flag, FILE* source, FILE* target);

char invertCharacter(char character){
    if (character == ' '){
        return '@';
    }
    if (character == '@'){
        return ' ';
    }
    return character;
}

RLEListResult runCommand(char flag, FILE* source, FILE* target){
    if (!source || !target){
        return RLE_LIST_NULL_ARGUMENT;
    }

    RLEList list = asciiArtRead(source);
    if (!list){
        return RLE_LIST_ERROR; // maybe?
    }

    RLEListResult result;
    switch (flag){
    case 'e':
        result = asciiArtPrintEncoded(list, target);
        break;
    case 'i':
        result = RLEListMap(list, invertCharacter);
        if (result != RLE_LIST_SUCCESS){
            break;
        }
        result = asciiArtPrint(list, target);
        break;
    }
    RLEListDestroy(list);
    return result;
}

int main(int argc, char* argv[]){
    if (argc != 4){
        fprintf(stderr, "number of arguments must be 4\n");
        return 0;
    }

    char flag = argv[1][0];
    if (flag != 'e' && flag != 'i'){
        fprintf(stderr, "flags can be only i [inverted] or e [endocded]\n");
        return 0;
    }

    FILE* source = fopen(argv[2], "rt");
    FILE* target = fopen(argv[3], "w"); 

    RLEListResult result = runCommand(flag, source, target);
    if (result != RLE_LIST_SUCCESS){
        fprintf(stderr, "command didn't finish successfully - exit code: %d\n", result);
    }
    return 0;
}