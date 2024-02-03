#include <stdio.h>
#include <stdlib.h>
#include "RLEList.h"



int main(){
    RLEList list = RLEListCreate();
    for (int i = 0; i < 10; i++)
        RLEListAppend(list, 'a');
    for (int i = 0; i < 11; i++)
        RLEListAppend(list, 'b');
    for (int i = 0; i < 1; i++)
        RLEListAppend(list, 'c');
    for (int i = 0; i < 12; i++)
        RLEListAppend(list, 'd');

    char* string = RLEListExportToString(list, NULL);
    printf("list is:\n%s", string);
    free(string);
    RLEListDestroy(list);
}