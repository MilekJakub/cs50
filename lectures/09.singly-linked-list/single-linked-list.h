#ifndef STRING_UTILS_H
#define STRING_UTILS_H
#include <stdbool.h>

typedef struct single_linked_list_node
{
    int value;
    struct single_linked_list_node *next;
} sllnode;

sllnode* create(int value);
bool find(sllnode* head, int value);
sllnode* insert(sllnode* head, int value);
void destroy(sllnode* head);
#endif
