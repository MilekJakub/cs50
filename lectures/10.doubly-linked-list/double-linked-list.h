#ifndef STRING_UTILS_H
#define STRING_UTILS_H
#include <stdbool.h>

typedef struct double_linked_list_node
{
    int value;
    struct double_linked_list_node *prev;
    struct double_linked_list_node *next;
} dllnode;

dllnode* create(int value);
bool find(dllnode* head, int value);
dllnode* insert(dllnode* head, int value);
void delete(dllnode* node);
void destroy(dllnode* head);
#endif
