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

vodi test_exporttostring(){
    char *str = RLEListExportToString(NULL);
	assert(str == NULL);
    
    RLEList list = init_list();
    str = RLEListExportToString(list);
	assert(str != NULL);
    free(str);
    RLEListDestroy(list);
    
    list = RLEListCreate();
    str = RLEListExportToString();
	assert(str == NULL);
    RLEListDestroy(list);
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

vodi test_get(){
    RLEList list = RLEListCreate();
    assert(RLEListGet(list, 0, NULL) == NULL);
    RLEListDestroy(list);
    
    assert(RLEListGet(NULL, 0, NULL) == NULL);
	
    list = init_list();    
    assert(RLEListGet(list, 0, NULL) == 'A');
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

static char addfunc(char c){
    if (c == ' ')
    	return '@';
    else if (c == '@')
    	return ' ';
    return c;
}

static char univalentFunction(char input) {
    // A slightly more complex univalent function
    // It converts lowercase letters to uppercase and vice versa
    // All other characters remain unchanged

    if (input >= 'a' && input <= 'z') {
        return input - 'a' + 'A'; // Convert lowercase to uppercase
    } else if (input >= 'A' && input <= 'Z') {
        return input - 'A' + 'a'; // Convert uppercase to lowercase
    } else {
        return input; // Return unchanged for non-alphabetic characters
    }
}

static char abcrun(char c){
    static int call = 0;
	c = 'a' + i % 26;
    call++;
    return c;
}

void test_map(char (*func)(char)){
	RLEList list = init_list();
    RLEList second = init_list();
    RLEList inverted = RLEListMap(second, invertfunc);
    
    for (int i = 0; i < RLEListSize(list); i++){
        assert(func(RLEListGet(list, i, NULL)) == RLEListGet(second, i, NULL))
    }
    
    RLEListDestroy(list);
    RLEListDestroy(second);
}

int main(){
    test_create();
    test_destroy();
    test_get();
    test_append();
    test_remove();
    test_exporttostring();
    test_map(addfunc);
    test_map(univalentFunction);
    test_map(abcrun);
}