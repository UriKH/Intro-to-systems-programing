#include "RLEList.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    RLEList list = RLEListCreate();

    for (int i = 0; i < 5; i++)
        RLEListAppend(list, 'a');
    for (int i = 0; i < 123; i++)
        RLEListAppend(list, 'b');
    for (int i = 0; i < 12; i++)
        RLEListAppend(list, 'c');
    char* str = RLEListExportToString(list, NULL);
    printf("List:\n%s", str);
    free(str);
}