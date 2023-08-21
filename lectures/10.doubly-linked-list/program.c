#include <stdio.h>
#include "double-linked-list.h"

int main(void)
{
    printf("Create linked list with head of value 1.\n\n");
    dllnode *head = create(1);

    printf("Add to the list values 2 and 3.\n\n");
    head = insert(head, 2);
    head = insert(head, 3);

    bool result;

    printf("Call find function to search for node with value of 2.\n");
    result = find(head, 2);
    printf("bool result: %i\n\n", result);

    printf("Call delete function to delete node with value of 2.\n\n");
    dllnode *nodeWithValueOfTwo = head->next;
    delete(nodeWithValueOfTwo);

    printf("Call find function to search for node with value of 2.\n");
    result = find(head, 2);
    printf("bool result: %i\n\n", result);

    printf("Head value: %i\n\n", head->value);

    printf("Call destroy function to destroy whole list and free memory.\n");
    destroy(head);
}
