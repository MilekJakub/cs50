#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool prime(int number);

int main(void)
{
    int min;
    do
    {
        printf("Minimum: ");
        scanf("%i", &min);
    }
    while (min < 1);

    int max;
    do
    {
        printf("Maximum: ");
        scanf("%i", &max);
    }
    while (min >= max);

    for (int i = min; i <= max; i++)
    {
        if (prime(i))
        {
            printf("%i\n", i);
        }
    }
}

bool prime(int number)
{
    // https://www.geeksforgeeks.org/prime-numbers/

    // Check if n=1 or n=0
    if (number <= 1)
        return false;

    // Check if n=2 or n=3
    if (number == 2 || number == 3)
        return true;

    // Check whether n is divisible by 2 or 3
    if (number % 2 == 0 || number % 3 == 0)
        return false;

    // Check from 5 to square root of n
    for (int i = 5; i * i <= number; i = i + 6)
    {
        if (number % i == 0 || number % (i + 2) == 0)
        {
            return false;
        }
    }

    return true;
}
