#include "../include/linked_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Linked_List* linked_list_init() {
    Linked_List* list = malloc(sizeof(Linked_List));
    if (!list) {
        fprintf(stderr, "Error allocating linked list");
        abort();
    }
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

static Linked_List_Entry* linked_list_create_entry(const void* value, size_t size) {
    Linked_List_Entry* entry = malloc(sizeof(Linked_List_Entry));
    if (!entry) {
        fprintf(stderr, "Error allocating list entry");
        abort();
    }
    entry->next = NULL;
    entry->prev = NULL;
    entry->value = malloc(size);
    memcpy(entry->value, value, size);
    return entry;
}

void linked_list_append(Linked_List* list, const void* value, size_t size) {
    Linked_List_Entry* entry = linked_list_create_entry(value, size);
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

void* linked_list_get(const Linked_List* list, size_t index) {
    if (index >= list->size) return NULL;
    const Linked_List_Entry* entry = NULL;
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
    return entry->value;
}

void linked_list_remove(Linked_List* list, size_t index) {
    if (index >= list->size || list->head == NULL) return;
    Linked_List_Entry* entry = NULL;
    if (index == 0) {
        entry = list->head;
        list->head = entry->next;
        if (entry->next)
            entry->next->prev = NULL;
        else
            list->tail = NULL;
        free(entry->value);
        free(entry);
        --list->size;
        return;
    }
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
    if (entry->prev) entry->prev->next = entry->next;
    if (entry->next) entry->next->prev = entry->prev;
    if (index == list->size - 1) list->tail = entry->prev;
    free(entry->value);
    free(entry);
    --list->size;
}

void linked_list_destroy(Linked_List* list) {
    Linked_List_Entry* curr = list->head;
    while (curr) {
        Linked_List_Entry* next = curr->next;
        free(curr->value);
        free(curr);
        curr = next;
    }
    free(list);
}
