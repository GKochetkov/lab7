#ifndef GRAPH_STACK_H_INCLUDED
#define GRAPH_STACK_H_INCLUDED

#define LIST struct list

#include <malloc.h>


LIST {
    int value;
    LIST *next;
};

LIST* Create(int value) {
    LIST *res;

    res = (LIST*)malloc(sizeof(LIST));
    res -> value = value;
    res -> next = NULL;

    return res;
}

void Add(LIST *first, LIST *elem) {
    if (first -> next == NULL)
        first -> next = elem;
    else
        Add(first -> next, elem);
}

//take element from stack
int Take(LIST *first) {
    if (first -> next != NULL) {
        LIST *elem = first -> next;
        int res = elem -> value;
        first -> next = elem -> next;
        free(elem);
        return res;
    } else
        return 0;
}

void Clear(LIST *first) {
    if (first -> next != NULL)
        Clear(first -> next);
    free(first);
}

#endif // GRAPH_STACK_H_INCLUDED
