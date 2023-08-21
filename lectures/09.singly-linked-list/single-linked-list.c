#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "single-linked-list.h"

sllnode* create(int value)
{
    sllnode* node = malloc(sizeof(sllnode));

    if (node == NULL)
    {
        fprintf(stderr, "Cannot create new sllnode.");
        return NULL;
    }

    node->value = value;
    node->next = NULL;

    return node;
}

bool find(sllnode* head, int value)
{
    if (head->value == value)
    {
        return true;
    }

    if (head->next == NULL)
    {
        return false;
    }

    return find(head->next, value);
}

sllnode* insert(sllnode* head, int value)
{
    sllnode *new_node = malloc(sizeof(sllnode));
    
    if (new_node == NULL)
    {
        fprintf(stderr, "Cannot create new sllnode.");
        return NULL;
    }

    new_node->value = value;
    new_node->next = head;
    
    return new_node;
}

void destroy(sllnode* head)
{
    if (head == NULL)
    {
        return;
    }

    if (head->next == NULL)
    {
        free(head);
        return;
    }

    destroy(head->next);
}

