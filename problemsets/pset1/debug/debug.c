// Become familiar wih C syntax
// Learn to debug buggy code

#include <stdio.h>

int main(void)
{
    char name[50];
    char location[50];

    printf("What is your name?\n");
    scanf("%s", name);

    printf("Where do you live?\n");
    scanf("%s", location);

    printf("Hello, %s, from %s!", name, location);
}
