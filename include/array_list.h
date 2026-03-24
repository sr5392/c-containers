#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H
#include <stddef.h>

typedef struct Array_List {
    void** data;
    size_t capacity;
    size_t size;
} Array_List;

Array_List* array_list_init();
void array_list_reserve(Array_List* list, size_t capacity);
void array_list_set_item_at(Array_List* list, size_t index, void* item);
void array_list_add_item(Array_List* list, void* item);
void* array_list_get_item_at(Array_List* list, size_t index);
void array_list_remove_item_at(Array_List* list, size_t index);
void array_list_remove_item(Array_List list, void* item, bool (*cmp_function)(void* a, void* b));
void array_list_remove_all_items(Array_List list, void* item, bool (*cmp_function)(void* a, void* b));
void array_list_remove_all(Array_List list);
void array_list_destroy(Array_List* list);
void array_list_sort(Array_List* list, bool (*sort_function)(void* a, void* b));
void array_list_shrink_to_fit(Array_List* list);

#endif
