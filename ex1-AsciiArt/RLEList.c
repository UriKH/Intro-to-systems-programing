#include <stdlib.h>
#include <string.h>
#include <limits.h> // for using INT_MAX number of digits for buffer size
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

    while (currentNode != NULL){
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
    while (temporary != NULL){
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
    if (newList != NULL){
        newList->repetitions = 0;
        newList->next = NULL;
    }
    return newList;
}

void RLEListDestroy(RLEList list){
    RLEList temporaryListHead;

    while (list != NULL){
        temporaryListHead = list;
        list = list->next;
        free(temporaryListHead);
    }
}

int RLEListSize(RLEList list){
    if (list == NULL){
        return -1;
    }

    int size = 0;
    RLEList temporary = list;
    while (temporary != NULL){
        size += temporary->repetitions;
        temporary = temporary->next;
    }
    return size;
}

RLEListResult RLEListAppend(RLEList list, char value){
    if (list == NULL)
        return RLE_LIST_NULL_ARGUMENT;

    RLEList endNode = list;
    // go to end of list
    while (endNode->next != NULL){
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
        if (endNode->next == NULL)
            return RLE_LIST_OUT_OF_MEMORY;
        endNode->next->value = value;
        endNode->next->repetitions = 1;
        endNode->next->next = NULL;
    }
    return RLE_LIST_SUCCESS;
}

RLEListResult RLEListRemove(RLEList list, int index){
    if (list == NULL){
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
    if (list == NULL){
        if (result != NULL){
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return 0;
    }

    if (index < 0 || index >= RLEListSize(list)){
        if (result != NULL){
            *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }
        return 0;
    }

    index = convertToNodeIndex(list, index);
    if (result != NULL){
        *result = RLE_LIST_SUCCESS;
    }
    return RLEGetNodeAt(list, index)->value;
}

char* RLEListExportToString(RLEList list, RLEListResult* result){
    if (list == NULL){
        if (result != NULL){
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return NULL;
    }

    int size = 1, previousSize = 1;
    char* string = (char*)malloc(sizeof(char) * size); // the return string
    // buffer for itoa usage
    char* repetitionsString = (char*)malloc(calculateSize(INT_MAX) + 1);

    if (repetitionsString == NULL || string == NULL){
        *result = RLE_LIST_OUT_OF_MEMORY;
        return NULL;
    }

    RLEList currentNode = list;
    while (currentNode != NULL){
        string[previousSize - 1] = currentNode->value;
        itoa(currentNode->repetitions, repetitionsString, 10);
        size += strlen(repetitionsString) + 2;

        string = (char*)realloc(string, size * sizeof(char));
        if (string == NULL){
            if (result != NULL){
                *result = RLE_LIST_OUT_OF_MEMORY;
            }
            return NULL;
        }

        strcpy(string + previousSize, repetitionsString);
        previousSize = size;
        string[size - 2] = '\n';
        currentNode = currentNode->next;
    }

    string[size - 1] = '\0';
    if (result != NULL){
        *result = RLE_LIST_SUCCESS;
    }
    return string;
}

RLEListResult RLEListMap(RLEList list, MapFunction map_function){
    if (list == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }

    RLEList currentNode = list;
    while (currentNode != NULL){
        currentNode->value = map_function(currentNode->value);
        currentNode = currentNode->next;
    }
    return RLE_LIST_SUCCESS;
}