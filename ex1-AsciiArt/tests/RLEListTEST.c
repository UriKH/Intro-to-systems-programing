#include "RLEList.h"
#include <assert.h>
#include <stdio.h>

RLEList init_list(){
    RLEList list = RLEListCreate();
    for (int i = 0; i < 5; i++)
    	RLEListAppend(list, 'a');
    for (int i = 0; i < 12; i++)
    	RLEListAppend(list, 'b');
    for (int i = 0; i < 5; i++)
    	RLEListAppend(list, ' ');
    for (int i = 0; i < 5; i++)
    	RLEListAppend(list, '@');
    for (int i = 0; i < 1; i++)
    	RLEListAppend(list, 'c');
    return list;
}

void test_create_destroy(){
    RLEList list = init_list();
    assert<list != NULL>;
   	RLEListDestroy(list);
    assert<list == NULL>;
}


int main(){
    test_create();
    test_delete();
    test_remove();
    test_append();
    test_empty_list();
    
}