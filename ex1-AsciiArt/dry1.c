#include <stdlib.h>
#include <string.h>
#include <assert.h> 

char* stringDuplicator(char* string, int times){
    assert(string);
    assert(times > 0);
    int length = strlen(string);
    char* out = malloc(length * times + 1);
    assert(out); // ask
    
    // replace by?
    // if (!out){
    // 		return NULL;
    // }

    for (int i = 0; i < times; i++){
        strcpy(out + i * length, string);
    }

    out[times * length - 1] = '\0';
    return out;
}