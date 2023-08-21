#include <stdio.h>
#include "single-linked-list.h"

int main()
{
    sllnode *head = create(1);
    head = insert(head, 2);
    printf("%i\n", head->value);

    bool result = find(head, 1);
    printf("%i\n", result);

    result = find(head, 0);
    printf("%i\n", result);
}
