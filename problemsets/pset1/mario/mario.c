#include <stdio.h>

int main(void)
{
    int size;

    do
    {
        printf("Height: ");
        scanf("%i", &size);
    }
    while(size < 1);

    for(int i = 0; i < size; i++)
    {
        for(int j = i; j < size; j++)
        {
            printf(" ");
        }

        for(int k = 0; k <= i; k++)
        {
            printf("#");
        }

        printf("  ");

        for(int k = 0; k <= i; k++)
        {
            printf("#");
        }

        printf("\n");
    }
}
