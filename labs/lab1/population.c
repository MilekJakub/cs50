#include <stdio.h>

int main(void)
{
    int startSize, endSize;

    do
    {
        printf("Start size: ");
        scanf("%d", &startSize);
    }
    while(startSize < 9);

    do
    {
        printf("End size: ");
        scanf("%d", &endSize);
    }
    while(endSize < startSize);

    int population = startSize;
    int years = 0;

    while(population < endSize)
    {
        int born = population / 3;
        int died = population / 4;

        population = population + born - died;
        years++;
    }

    printf("Years: %i", years);
}

