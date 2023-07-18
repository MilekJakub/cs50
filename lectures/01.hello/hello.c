#include <stdio.h>

int main(void)
{
    char answer[50];
    printf("What is your name? ");
    scanf("%s", answer);
    printf("Hello %s.\n", answer);
}
