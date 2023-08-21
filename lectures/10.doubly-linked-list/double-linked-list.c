#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "double-linked-list.h"

dllnode* create(int value)
{
    dllnode* node = malloc(sizeof(dllnode));

    if (node == NULL)
    {
        fprintf(stderr, "Cannot create new dllnode.");
        return NULL;
    }

    node->value = value;
    node->prev = NULL;
    node->next = NULL;

    return node;
}

bool find(dllnode* head, int value)
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

dllnode* insert(dllnode* head, int value)
{
    dllnode *new_node = malloc(sizeof(dllnode));
    
    if (new_node == NULL)
    {
        fprintf(stderr, "Cannot create new dllnode.");
        return NULL;
    }

    head->prev = new_node;

    new_node->value = value;
    new_node->prev = NULL;
    new_node->next = head;
    
    return new_node;
}

void delete(dllnode* node)
{
    dllnode* previous = node->prev;
    dllnode* next = node->next;

    if (previous != NULL)
    {
        previous->next = next;
    }

    if (next != NULL)
    {
        next->prev = previous;
    }

    free(node);
}

void destroy(dllnode* head)
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

