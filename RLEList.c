#include "RLEList.h"
#include <stdlib.h>
#include <string.h>

#define SINGLE_APPEARANCE 1
#define ENTER_CHARACTER_LEN 1
#define CHARACTER_LEN 1

struct RLEList_t 
{
    char letter;
    int letterAppearances;
    struct RLEList_t* next;
};

RLEList RLEListCreate() 
{
    RLEList list = malloc(sizeof(*list));
    if (!list) {
        free(list);
        return NULL;
    }
    list->letter = '\0';
    list->letterAppearances = 0;
    list->next = NULL;
    return list;
}

void RLEListDestroy(RLEList list) 
{
    while (list) {
        RLEList toDelete = list;
        list = list->next;
        toDelete->next = NULL;
        free(toDelete);
    }
}

RLEListResult RLEListAppend(RLEList list, char value) 
{
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
        free(newLetter);
        return RLE_LIST_OUT_OF_MEMORY;
    }
    newLetter->letter = value;
    newLetter->letterAppearances = SINGLE_APPEARANCE;
    newLetter->next = NULL;
    list->next = newLetter;
    return RLE_LIST_SUCCESS;
}

//Returns list's first non-empty node - 
//if the current head is a dummy node it'll return the next node. 
//Otherwise, the current node will be returned.
static RLEList head(RLEList list) 
{
    if (list->letter && list->letterAppearances >= SINGLE_APPEARANCE) {
        return list;
    }
    return list->next;
}

int RLEListSize(RLEList list) 
{
    if (!list) {
        return -1;
    }
    int totalCharacters = 0;
    list = head(list);
    while (list) {
        totalCharacters += list->letterAppearances;
        list = list->next;
    }
    return totalCharacters;
}

//Merges the two given nodes into previousNode and deletes nextNode, which is no longer relevant.
static void mergeNodes(RLEList previousNode, RLEList nextNode)
{
    previousNode->letterAppearances += nextNode->letterAppearances;
    previousNode->next = nextNode->next;
    nextNode->next = NULL;
    free(nextNode);
}

RLEListResult RLEListRemove(RLEList list, int index) 
{
    if (!list) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList previousNode = list;
    list = head(list);
    int currentIndex = 0;
    while (list) {
        currentIndex += list->letterAppearances;
        if (currentIndex > index) {
            if (list->letterAppearances == SINGLE_APPEARANCE) {
                RLEList tempNode = list;
                previousNode->next = tempNode->next;
                tempNode->next = NULL;
                free(tempNode);
                if (previousNode && previousNode->next && previousNode->letter == previousNode->next->letter) {
                    mergeNodes(previousNode, previousNode->next);
                }
            }
            else {
                list->letterAppearances--;
            }
            return RLE_LIST_SUCCESS;
        }
        previousNode = list;
        list = list->next;
    }
    return RLE_LIST_INDEX_OUT_OF_BOUNDS;
}

char RLEListGet(RLEList list, int index, RLEListResult* result) 
{
    if (!list) {
        if (result) {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return 0;
    }
    list = head(list);
    int currentIndex = 0;
    while (list) {
        if (currentIndex <= index && index < currentIndex + list->letterAppearances) {
            if (result) {
                *result = RLE_LIST_SUCCESS;
            }
            return list->letter;
        }
        currentIndex = currentIndex + list->letterAppearances;
        list = list->next;
    }
    if (result) {
        *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    return 0;
}

RLEListResult RLEListMap(RLEList list, MapFunction mapFunction) 
{
    if (!list || !mapFunction) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    list = head(list);
    RLEList temp = list;
    RLEList previousNode = NULL;
    while (temp) {
        char newLetter = mapFunction(temp->letter);
        if ((previousNode) && (previousNode->letter == newLetter)){
            mergeNodes(previousNode, temp);
        }
        else {
            temp->letter = newLetter;
            previousNode = temp;
            temp = temp->next;
        }
    }
    return RLE_LIST_SUCCESS;
}

//Returns the given number's digits count
static int getDigitsCount(unsigned int number) 
{
    int count = 1;
    while (number > 9) {
        number /= 10;
        count++;
    }
    return count;
}

//Returns the length of the whole string that's about to be exported for the given list.
static int getLengthOfExportedString(RLEList list) 
{
    int len = 0;
    RLEList temp = list->next;
    while (temp) {
        len++;
        len += CHARACTER_LEN + getDigitsCount(temp->letterAppearances) + ENTER_CHARACTER_LEN;
        temp = temp->next;
    }
    return len;
}

char* RLEListExportToString(RLEList list, RLEListResult* result) 
{
    if (!list) {
        if (result) {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return NULL;
    }

    char* str = malloc(getLengthOfExportedString(list) * sizeof(char) + 1);
    if (!str) {
        *result = RLE_LIST_OUT_OF_MEMORY;
        free(str);
        return NULL;
    }
    list = head(list);
    RLEList temp = list;
    int i = 0;
    while (temp) {
        str[i] = temp->letter;
        sprintf(str + (++i), "%d", temp->letterAppearances);
        i += getDigitsCount(temp->letterAppearances);
        temp = temp->next;
        str[i++] = '\n';
    }

    str[i] = '\0';
    if (result) {
        *result = RLE_LIST_SUCCESS;
    }
    return str;
}
