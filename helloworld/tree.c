#include <stdio.h>

typedef struct listNode *listPointer;
typedef struct {
    char data[4];
    listPointer link;
} listNode;
listPointer first = NULL;