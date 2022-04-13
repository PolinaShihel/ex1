#include "RLEList.h"
#include <stdlib.h>
#include <string.h>

#define NODE_DATA_AS_STRING_LENGTH 2
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

    list->letterAppearances = 0;
    list->next = NULL;
    return list;
}

RLEListMap(RLEList list, MapFunction map_function) {
    RLEList tmp = list;
    while (tmp)
    {
        tmp->letter = map_function(tmp->letter);
        tmp = tmp->next;
    }
}

int GetListLength(RLEList list)
{
    int length = 0;
    RLEList tmp = list;
    while (tmp != NULL)
    {
        length++;
        tmp = tmp->next;
    }
    return length;
}

int const charactersCountPerLine = NODE_DATA_AS_STRING_LENGTH + ENTER_CHAR_LENGTH;
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