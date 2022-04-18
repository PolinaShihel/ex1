#include "RLEList.h"
#include <stdlib.h>

#define SINGLE_APPEARANCE 1
#define NODE_DATA_STRING_LENGTH 2
#define ENTER_CHAR_LENGTH 1

#define CONVERT_INT_TO_CHAR(x) x + '0'

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
    list->letter = '\0';
    list->letterAppearances = 0;
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

static bool IsListEmpty(RLEList list) {
    return !(list->letter && list->letterAppearances);
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
        free(newLetter);
        return RLE_LIST_OUT_OF_MEMORY;
    }
    newLetter->letter = value;
    newLetter->letterAppearances = 1;
    newLetter->next = NULL;

    if (!IsListEmpty(list)) {
        list->next = newLetter;
    }
    else {
        list->letter = newLetter->letter;
        list->letterAppearances = newLetter->letterAppearances;
    }
    free(newLetter)
    return RLE_LIST_SUCCESS;
}

int RLEListSize(RLEList list) {
    if (!list) {
        return -1;
    }
    int totalCharacters = 0;
    while (list) {
        totalCharacters += list->letterAppearances;
        list = list->next;
    }
    return totalCharacters;
}

RLEListResult RLEListRemove(RLEList list, int index) {
    if (!list) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList previousNode = list;
    if (index == 0) {
        if (list->letterAppearances == SINGLE_APPEARANCE) {
            list = list->next;
            previousNode->next = NULL;
            free(previousNode);
            return RLE_LIST_SUCCESS;
        }
    }
    int currentIndex = 0;
    //check if after removal the letter before and letter after are the same (merging them)
    while (list) {
        if (currentIndex >= index) {
            if (list->letterAppearances == SINGLE_APPEARANCE) {
                RLEList tempNode =list;
                previousNode->next = tempNode->next;
                tempNode->next = NULL;
                free(tempNode);
            }
            else {
                list->letterAppearances--;
            }
            return RLE_LIST_SUCCESS;
        }
        previousNode = list;
        currentIndex += list->letterAppearances;
        list = list->next;
    }
    return RLE_LIST_INDEX_OUT_OF_BOUNDS;
}

char RLEListGet(RLEList list, int index, RLEListResult* result) {
    if (!list) {
        if (result) {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
    }
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

RLEListResult RLEListMap(RLEList list, MapFunction map_function) {
    if (!list) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList temp = list;
    RLEList previousNode = NULL;
    while (temp) {
        char newLetter = map_function(temp->letter);
        if (previousNode->letter && previousNode->letter == newLetter) {
            RLEList nodeToDelete = temp;
            previousNode->letterAppearances += nodeToDelete->letterAppearances;
            previousNode->next = nodeToDelete->next;
            temp = nodeToDelete->next;
            free(nodeToDelete);
        }
        else {
            temp->letter = newLetter;
            previousNode = temp;
            temp = temp->next;
        }
    }
    return RLE_LIST_SUCCESS;
}

static int GetListActualLength(RLEList list) {
    int actualLength = 0;
    RLEList temp = list;
    while (temp) {
        actualLength++;
        temp = temp->next;
    }
    return actualLength;
}

char* RLEListExportToString(RLEList list, RLEListResult* result) {
    if (!list) {
        if (result) {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return NULL;
    }

    char* str = malloc((NODE_DATA_STRING_LENGTH + ENTER_CHAR_LENGTH) * GetListActualLength(list) * sizeof(char) + 1);
    if (!str) {
        *result = RLE_LIST_OUT_OF_MEMORY;
        free(str);
        return NULL;
    }

    RLEList temp = list;
    int i = 0;
    while (temp) {
        str[i] = temp->letter;
        str[++i] = CONVERT_INT_TO_CHAR(temp->letterAppearances);
        if (temp->next) {
            str[++i] = '\n';
        }
        i++;
        temp = temp->next;
    }

    str[i] = '\0';
    if (result) {
        *result = RLE_LIST_SUCCESS;
    }
    return str;
}
