#include "array_list.h"
#include <stdio.h>
#include <stdlib.h>

Array_List* array_list_init() {
    Array_List* list = malloc(sizeof(Array_List));
    list->data = NULL;
    list->capacity = 0;
    list->size = 0;
    return list;
}

static Array_List* array_list_resize(Array_List* list, size_t capacity) {
    if (capacity <= list->capacity) return list;
    if (!list->data) {
        list->data = malloc(capacity * sizeof(void*));
        list->capacity = capacity;
        return list;
    }
    void** data = realloc(list->data, capacity * sizeof(void*));
    if (!data) {
        fprintf(stderr, "Error reallocating memory for list");
        exit(EXIT_FAILURE);
    }
    list->data = data;
    list->capacity = capacity;
    return list;
}

void array_list_add_item(Array_List* list, void* item) {
    if (list->capacity == 0) array_list_resize(list, 1);
    if (list->size >= list->capacity) array_list_resize(list, 2 * list->capacity);;
    list->data[list->size] = item;
    list->size += 1;
}

void* array_list_get_item_at(Array_List* list, size_t index) {
    if (index >= list->size) {
        fprintf(stderr, "Index out of bounds");
        exit(EXIT_FAILURE);
    }
    return list->data[index];
}

void array_list_destroy(Array_List* list) {
    free(list->data);
}
