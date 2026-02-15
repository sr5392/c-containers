#include "linked_list.h"
#include <assert.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

Linked_List* linked_list_init(Linked_List_Free_Function free_function) {
    Linked_List* list = malloc(sizeof(Linked_List));
    if (!list) {
        fprintf(stderr, "Error allocating memory for list");
        exit(EXIT_FAILURE);
    }
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
    list->free_function = free_function;
    return list;
}

static Linked_List_Entry* linked_list_create_entry(void* item) {
    assert(item);
    Linked_List_Entry* entry = malloc(sizeof(Linked_List_Entry));
    if (!entry) {
        fprintf(stderr, "Error allocating memory for list entry");
        exit(EXIT_FAILURE);
    }
    entry->next = NULL;
    entry->prev = NULL;
    entry->value = item;
    return entry;
}

void linked_list_append_item(Linked_List* list, void* item) {
    assert(list && item);
    Linked_List_Entry* entry = linked_list_create_entry(item);
    if (list->head) {
        list->tail->next = entry;
        entry->prev = list->tail;
        list->tail = entry;
    } else {
        list->head = entry;
        list->tail = entry;
    }
    ++list->size;
}

static Linked_List_Entry* linked_list_get_entry_at(const Linked_List* list, size_t index) {
    assert(list);
    if (index >= list->size) {
        fprintf(stderr, "Index out of bounds");
        exit(EXIT_FAILURE);
    }
    Linked_List_Entry* entry = NULL;
    if (index <= list->size / 2) {
        entry = list->head;
        for (size_t i = 0; i < index; ++i) {
            entry = entry->next;
        }
    } else {
        entry = list->tail;
        for (size_t i = 0; i < list->size - 1 - index; ++i) {
            entry = entry->prev;
        }
    }
    return entry;
}

void* linked_list_get_item_at(const Linked_List* list, size_t index) {
    return linked_list_get_entry_at(list, index)->value;
}

void linked_list_set_item_at(Linked_List* list, size_t index, void* item) {
    assert(list);
    assert(item);
    Linked_List_Entry* entry = linked_list_get_entry_at(list, index);
    if (list->free_function && entry->value) list->free_function(entry->value);
    entry->value = item;
}

void linked_list_remove_item_at(Linked_List* list, size_t index) {
    assert(list);
    Linked_List_Entry* entry = linked_list_get_entry_at(list, index);
    if (entry->prev)
        entry->prev->next = entry->next;
    else
        list->head = entry->next;
    if (entry->next) entry->next->prev = entry->prev;
    if (!entry->next) list->tail = entry->prev;
    if (list->free_function && entry->value) list->free_function(entry->value);
    free(entry);
    --list->size;
}

void linked_list_destroy(Linked_List* list) {
    assert(list);
    Linked_List_Entry* curr = list->head;
    while (curr) {
        Linked_List_Entry* next = curr->next;
        if (list->free_function && curr->value) list->free_function(curr->value);
        free(curr);
        curr = next;
    }
    free(list);
}

Linked_List_Iterator linked_list_begin(const Linked_List* list) {
    assert(list);
    return list->head;
}

Linked_List_Iterator linked_list_end(const Linked_List* list) {
    assert(list);
    return NULL;
}

Linked_List_Iterator linked_list_next(Linked_List_Const_Iterator iterator) {
    return iterator ? iterator->next : NULL;
}

void* linked_list_iterator_get_item(Linked_List_Const_Iterator iterator) {
    return iterator ? iterator->value : NULL;
}
