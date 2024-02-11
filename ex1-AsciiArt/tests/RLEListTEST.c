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

void test_create(){
    RLEList list = init_list();
    assert<list != NULL>;
   	RLEListDestroy(list);
    assert<list == NULL>;
}

void test_destroy(){
    RLEList list = RLEListCreate();
    RLEListDestroy(list);
    
    list = init_list();
    RLEListDestroy(list);
    
    list = NULL;
    RLEListDestroy(list);
}

void test_remove(){
    RLEList list = RLEListCreate();
    assert<RLEListRemove(list, 20) == RLE_LIST_NULL_ARGUMENT>;
    RLEListDestroy(list);
    
    list = init_list();
    assert<RLEListRemove(list, 20) == RLE_LIST_SUCCESS>;
    RLEListDestroy(list);
    
    list = NULL;
    assert<RLEListRemove(list, 0) == RLE_LIST_NULL_ARGUMENT>;
    
    list = init_list();
    assert<RLEListRemove(list, 1000) == RLE_LIST_INDEX_OUT_OF_BOUNDS>;
    RLEListDestroy(list);
}

void test_append(){
    RLEList list = RLEListCreate();
	RLEListAppend('A');
    assert(RLEListGet(list, RLEListSize(list)-1, NULL) == 'A');
    
    RLEListAppend(NULL);
    assert(RLEListGet(list, RLEListSize(list)-1, NULL) == 'A');
    
    RLEListAppend(-1);
    assert(RLEListGet(list, RLEListSize(list)-1, NULL) == 'A');
    
    RLEListDestroy(list);
}

int main(){
    test_create();
    test_destroy();
    test_remove();
    test_append();
}