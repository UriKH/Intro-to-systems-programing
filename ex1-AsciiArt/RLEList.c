#include <stdlib.h>
#include <string.h>
#include "RLEList.h"

struct RLEList_t{
    char value;
    int repetitions;
    struct RLEList_t* next;
};

/**
 * Utility function for convertion between the index as used by the user
 * and the actual index in the RLE list.
 * @param list: The RLE list
 * @param index: Index to convert
 * @returns
 * -1 if index is out of boundes.
 * The converted index in case of success.
*/
static int convertToNodeIndex(RLEList list, int index){
    int accumulatedSize = 0, iterator = 0;
    RLEList currentNode = list;
    if (index < 0){
        return -1;
    }

    while (currentNode){
        accumulatedSize += currentNode->repetitions;
        if (accumulatedSize-1 >= index){
            return iterator;
        }
        currentNode = currentNode->next;
        iterator++;
    }
    return -1;
}

/**
 * Utility function that returns a RLE list node at a specified index
 * @param list: The RLE list
 * @param index: Index of the requested node
 * @returns
 * NULL if index is out of boundes.
 * The node in case of success.
*/
static RLEList RLEGetNodeAt(RLEList list, int index){
    int length = 0;
    RLEList temporary = list;
    while (temporary){
        if (index == length){
            return temporary;
        }
        temporary = temporary->next;
        length++;
    }
    return NULL;
}

/**
 * Utility function that calculates the number of digits of an integer
 * @param number: The integer to check
 * @returns
 * The number of digits in the given number
*/
static int calculateSize(int number){
    int size = 0;
    if (number == 0){
        return 1;
    }
    if (number > 0){
        while (number >= 1){
            number /= 10;
            size++;
        }
    }
    else{
        while (number <= -1){
            number /= 10;
            size++;
        }
    }
    return size;
}

RLEList RLEListCreate(){
    RLEList newList = (RLEList)malloc(sizeof(struct RLEList_t));
    if (newList){
        newList->repetitions = 0;
        newList->next = NULL;
    }
    return newList;
}

void RLEListDestroy(RLEList list){
    RLEList temporaryListHead;

    while (list){
        temporaryListHead = list;
        list = list->next;
        free(temporaryListHead);
    }
}

int RLEListSize(RLEList list){
    if (!list){
        return -1;
    }

    int size = 0;
    RLEList temporary = list;
    while (temporary){
        size += temporary->repetitions;
        temporary = temporary->next;
    }
    return size;
}

RLEListResult RLEListAppend(RLEList list, char value){
    if (!list)
        return RLE_LIST_NULL_ARGUMENT;

    RLEList endNode = list;
    while (endNode->next){ // go to end of list
        endNode = endNode->next;
    }

    if (endNode->repetitions == 0){ // first append 
        endNode->value = value;
        endNode->repetitions++;
    }
    else if (value == endNode->value){ // update node
        endNode->repetitions += 1;
    }
    else{ // create new node
        endNode->next = (RLEList)malloc(sizeof(struct RLEList_t));
        if (!endNode->next)
            return RLE_LIST_OUT_OF_MEMORY;
        endNode->next->value = value;
        endNode->next->repetitions = 1;
        endNode->next->next = NULL;
    }
    return RLE_LIST_SUCCESS;
}

RLEListResult RLEListRemove(RLEList list, int index){
    if (!list){
        return RLE_LIST_NULL_ARGUMENT;
    }

    if (index < 0 || index >= RLEListSize(list)){
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }

    index = convertToNodeIndex(list, index);
    RLEList nodeAtIndex = RLEGetNodeAt(list, index);
    nodeAtIndex->repetitions -= 1;

    // delete null node
    if (nodeAtIndex->repetitions == 0){
        if (index == 0){
            RLEList temporary = list;
            list = list->next;
            free(temporary);
        }
        else{
            RLEGetNodeAt(list, index - 1)->next = RLEGetNodeAt(list, index + 1);
            free(nodeAtIndex);
        }
    }
    return RLE_LIST_SUCCESS;
}

char RLEListGet(RLEList list, int index, RLEListResult* result){
    if (!list){
        if (result){
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return 0;
    }

    if (index < 0 || index >= RLEListSize(list)){
        if (result){
            *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }
        return 0;
    }

    index = convertToNodeIndex(list, index);
    if (result){
        *result = RLE_LIST_SUCCESS;
    }
    return RLEGetNodeAt(list, index)->value;
}

char* RLEListExportToString(RLEList list, RLEListResult* result){
    if (!list){
        if (result){
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return NULL;
    }

    RLEList currentNode = list;
    int sumDigits = 0, nodes = 0;
    while (currentNode){
        currentNode = currentNode->next;
        nodes++;
    }

    int* numberOfDigits = (int*)malloc(sizeof(int) * nodes);
    if (!numberOfDigits){
        if (result){
            *result = RLE_LIST_OUT_OF_MEMORY;
        }
        return NULL;
    }

    currentNode = list;
    for (int i = 0; i < nodes; i++){
        numberOfDigits[i] = calculateSize(currentNode->repetitions);
        sumDigits += numberOfDigits[i];
        currentNode = currentNode->next;
    }

    char* string = (char*)malloc(sizeof(char) * (sumDigits + 2 * nodes + 1));
    if (!string){
        if (result){
            *result = RLE_LIST_OUT_OF_MEMORY;
        }
        free(numberOfDigits);
        return NULL;
    }

    int i = 0, j = 0;
    currentNode = list;
    while (currentNode){
        string[i] = currentNode->value;
        sprintf(string + i + 1, "%d", currentNode->repetitions);
        i += 1 + numberOfDigits[j++];
        string[i++] = '\n';
        currentNode = currentNode->next;
    }

    string[i] = '\0';
    if (result){
        *result = RLE_LIST_SUCCESS;
    }
    free(numberOfDigits);
    return string;
}

RLEListResult RLEListMap(RLEList list, MapFunction map_function){
    if (!list){
        return RLE_LIST_NULL_ARGUMENT;
    }

    RLEList currentNode = list;
    while (currentNode){
        currentNode->value = map_function(currentNode->value);
        currentNode = currentNode->next;
    }
    return RLE_LIST_SUCCESS;
}