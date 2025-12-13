#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <stddef.h>

typedef struct Linked_List_Entry {
    void* value;
    struct Linked_List_Entry* next;
    struct Linked_List_Entry* prev;
} Linked_List_Entry;

typedef struct {
    size_t size;
    Linked_List_Entry* head;
    Linked_List_Entry* tail;
} Linked_List;

Linked_List* linked_list_init(void);
void linked_list_append(Linked_List* list, const void* value, size_t size);
void* linked_list_get(const Linked_List* list, size_t index);
void linked_list_remove(Linked_List* list, size_t index);
void linked_list_destroy(Linked_List* list);

#endif
