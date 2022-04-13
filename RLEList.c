#include "RLEList.h"
#include <stdlib.h>
#include <string.h>

#define INDEX_OFFSET 1
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

int RLEListSize(RLEList list) {
    if (!list)
    {
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
    while (list) {
        currentIndex += list->letterAppearances - INDEX_OFFSET;
        if (currentIndex <= index) {
            if (list->letterAppearances == SINGLE_APPEARANCE) {
                previousNode->next = list->next;
                list->next = NULL;
                free(list);
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

char RLEListGet(RLEList list, int index, RLEListResult* result) {
    if (!list) {
        *result = RLE_LIST_NULL_ARGUMENT;
    }
    int currentIndex = 0;
    while (list) {
        if (index <= currentIndex - INDEX_OFFSET) {
            *result = RLE_LIST_SUCCESS;
            return list->letter;
        }
        list = list->next;
    }
    *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
    return 0;
}

RLEListMap(RLEList list, MapFunction map_function) {
    RLEList tmp = list;
    while (tmp)
    {
        tmp->letter = map_function(tmp->letter);
        tmp = tmp->next;
    }
}

static int GetListLength(RLEList list) {
    int length = 0;
    RLEList tmp = list;
    while (tmp)
    {
        length++;
        tmp = tmp->next;
    }
    return length;
}

int const charactersCountPerLine = NODE_DATA_STRING_LENGTH + ENTER_CHAR_LENGTH;
RLEListExportToEncodedString(RLEList list, RLEListResult* result) {
    if (!list)
    {
        *result = RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }
    char* str = malloc(GetListLength(list) * charactersCountPerLine * sizeof(char) + 1);
    if (!str)
    {
        *result = RLE_LIST_OUT_OF_MEMORY;
        free(str);
        return NULL;
    }

    RLEList tmp = list;
    int i = 0;
    while (tmp)
    {
        str[i] = tmp->letter;
        str[++i] = CONVERT_INT_TO_CHAR(tmp->letterAppearances);
        if (tmp->next)
        {
            str[++i] = '\n';
        }
        i++;
        tmp = tmp->next;
    }

    str[i] = NULL;
    *result = RLE_LIST_SUCCESS;
    return str;
}
