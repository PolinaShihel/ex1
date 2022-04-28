#include "RLEList.h"
#include <stdlib.h>
#include <string.h>

#define SINGLE_APPEARANCE 1
#define NODE_DATA_STRING_LENGTH 2
#define ENTER_CHAR_LENGTH 1

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
        toDelete->next = NULL;
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
        free(newLetter);
        return RLE_LIST_OUT_OF_MEMORY;
    }
    newLetter->letter = value;
    newLetter->letterAppearances = 1;
    newLetter->next = NULL;
    list->next = newLetter;
    return RLE_LIST_SUCCESS;
}

static RLEList GetFirstNode(RLEList list) {
    return list->next;
}

int RLEListSize(RLEList list) {
    if (!list) {
        return -1;
    }
    int totalCharacters = 0;
    list = GetFirstNode(list);
    while (list) {
        totalCharacters += list->letterAppearances;
        list = list->next;
    }
    return totalCharacters;
}

static void mergeNodes(RLEList previous_node, RLEList next_node)
{
    previous_node->letterAppearances += next_node->letterAppearances;
    previous_node->next = next_node->next;
    next_node->next = NULL;
    free(next_node);
}

RLEListResult RLEListRemove(RLEList list, int index) {
    if (!list) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList previousNode = list;
    list = GetFirstNode(list);
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

char RLEListGet(RLEList list, int index, RLEListResult* result) {
    if (!list) {
        if (result) {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return 0;
    }
    list = GetFirstNode(list);
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
    if (!list || !map_function) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList temp = list;
    RLEList previousNode = NULL;
    while (temp) {
        char newLetter = map_function(temp->letter);
        if ((previousNode) && (previousNode->letter == newLetter && temp->letter == newLetter)) {
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

int GetDigitsCount(unsigned int n) {
    int count = 1;
    while (n > 9) {
        n /= 10;
        count++;
    }
    return count;
}

static int GetLengthOfExportedString(RLEList list) {
    int characterLength = 1;
    int enterCharLength = 1;
    int actualLength = 0;
    RLEList temp = list->next;
    while (temp) {
        actualLength++;
        actualLength += GetDigitsCount(temp->letterAppearances);
        actualLength += characterLength + enterCharLength;
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

    char* str = malloc(GetLengthOfExportedString(list) * sizeof(char) + 1);t;
    if(temp){
        str[i++] = '\n';
    }
}

str[i] = '\0';
if (result) {
*result = RLE_LIST_SUCCESS;
}
return str;
}

if (!str) {
        *result = RLE_LIST_OUT_OF_MEMORY;
        free(str);
        return NULL;
    }
    list = GetFirstNode(list);
    RLEList temp = list;
    int i = 0;
    while (temp) {
        str[i] = temp->letter;
        sprintf(str + (++i), "%d", temp->letterAppearances);
        i += GetDigitsCount(temp->letterAppearances);
        temp = temp->nex