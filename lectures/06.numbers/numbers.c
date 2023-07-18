#include <stdio.h>

int main(int argc, char* argv[])
{
    int numbers[] = { 4, 6, 8, 2, 7, 5, 0 };
    int length = sizeof(numbers) / sizeof(numbers[0]);
    int match = 0;

    for (int i = 0; i < length; i++)
    {
        if(numbers[i] == match)
        {
            printf("true");
            return 0;
        }
    }

    printf("false");
    return 0;
}
