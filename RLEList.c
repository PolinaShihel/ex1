#include "RLEList.h"
#include <stdlib.h>

typedef struct {
    char letter;
    int letterAppearances;
    struct *RLEList_t next;
} RLEList_t;

RLEList RLEListCreate(){
    RLEList list = malloc(sizeof(*list));
    if()

}