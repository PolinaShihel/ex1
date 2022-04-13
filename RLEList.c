#include "RLEList.h"
#include <stdlib.h>

#define INDEX_OFFSET 1
#define SINGLE_APPEARANCE 1

struct RLEList_t {
    char letter;
    int letterAppearances;
    struct RLEList_t* next;
};

RLEList RLEListCreate() {
    RLEList list = malloc(sizeof(*list));
    if (!list) {
        free(list);
        return NULL;
    }
    list->letter = '';
    list->letterApearances = 0;
    list->next = NULL;
    return list;
}

void RLEListDestroy(RLEList list) {
    while (list) {
        RLEList toDelete = list;
        list = list->next;
        free(toDelete);
    }
}

RLEListResult RLEListAppend(RLEList list, char value) {
    if ((!list) || (!value)) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    while (list->next) {
        list = list->next;
    }
    if (list->letter == value) {
        list->letterAppearances++;
        return RLE_LIST_SUCCESS;
    }
    RLEList newLetter = malloc(sizeof(*newLetter));
    if (!newLetter) {
        return RLE_LIST_OUT_OF_MEMORY;
    }
    newLetter->letter = value;
    newLetter->letterAppearances = 1;
    newLetter->next = NULL;
    list->next = newLetter;
    return RLE_LIST_SUCCESS;
}

int RLEListSize(RLEList list){
    if(!list)
    {
        return -1;
    }
    int totalCharacters = 0;
    while(list){
        totalCharacters += list->letterAppearances;
        list = list->next;
    }
    return totalCharacters;
}

RLEListResult RLEListRemove(RLEList list, int index){
    if(!list){
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList previousNode = list;
    if(index == 0){
        if(list->letterAppearances == SINGLE_APPEARANCE){
            list = list->next;
            previousNode->next = NULL;
            free(previousNode);
            return RLE_LIST_SUCCESS;
        }
    }
    int currentIndex = 0;
    while(list){
        currentIndex += list->letterAppearances  - INDEX_OFFSET;
        if(currentIndex <= index) {
            if (list->letterAppearances == SINGLE_APPEARANCE) {
                previousNode->next = list->next;
                list->next = NULL;
                free(list);
            }
            else{
                list->letterAppearances--;
            }
            return RLE_LIST_SUCCESS;
        }
        previousNode = list;
        list = list->next;
    }
    return RLE_LIST_INDEX_OUT_OF_BOUNDS;
}

char RLEListGet(RLEList list, int index, RLEListResult *result){
    if(!list){
        *result = RLE_LIST_NULL_ARGUMENT;
    }
    int currentIndex = 0;
    while(list){
        if(index <= currentIndex - INDEX_OFFSET){
            *result = RLE_LIST_SUCCESS;
            return list->letter;
        }
        list = list->next;
    }
    *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
    return 0;
}



