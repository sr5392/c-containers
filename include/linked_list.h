#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <stddef.h>

typedef struct Linked_List_Entry {
    void* value;
    struct Linked_List_Entry* next;
    struct Linked_List_Entry* prev;
} Linked_List_Entry;

typedef void (*Linked_List_Free_Function)(void*);
typedef Linked_List_Entry* Linked_List_Iterator;
typedef const Linked_List_Entry* Linked_List_Const_Iterator;

typedef struct {
    size_t size;
    Linked_List_Entry* head;
    Linked_List_Entry* tail;
    Linked_List_Free_Function free_function;
} Linked_List;

Linked_List* linked_list_init(Linked_List_Free_Function free_function);
void linked_list_append_item(Linked_List* list, void* item);
void* linked_list_get_item_at(const Linked_List* list, size_t index);
void linked_list_set_item_at(Linked_List* list, size_t index, void* item);
void linked_list_remove_item_at(Linked_List* list, size_t index);
void linked_list_destroy(Linked_List* list);
Linked_List_Iterator linked_list_begin(const Linked_List* list);
Linked_List_Iterator linked_list_end(const Linked_List* list);
Linked_List_Iterator linked_list_next(Linked_List_Const_Iterator iterator);
void* linked_list_iterator_get_item(Linked_List_Const_Iterator iterator);

#endif
