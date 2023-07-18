#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <sys/types.h>
#include <string.h>

bool hasOnlyNumbers(char *str, ssize_t length);
int atoi(char *str);
int atoi_recursive(char *str);

int main(void)
{
    char *line;
    size_t buffersize;
    ssize_t length;
    bool onlyNumbers;

    // positive numbers only
    do
    {
        printf("Enter a positive integer: ");
        length = getline(&line, &buffersize, stdin);
        onlyNumbers = !hasOnlyNumbers(line, length);
    }
    while(length < 2 || line[0] == '-' || !onlyNumbers);

    int x = atoi(line);
    int y = atoi_recursive(line);

    printf("x: %i\n", x);
    printf("y: %i\n", y);

    return 0;
}

bool hasOnlyNumbers(char *str, ssize_t length)
{
    for(int i = 0; i < length; i++)
    {
        if(str[i] < 48 || str[i] > 57)
        {
            return false;
        }
    }

    return true;
}

// my implementation of atoi
int atoi(char *str)
{
    size_t length = strlen(str);
    int position = length - 2;
    int integer = 0;

    for(int i = 0; i < length - 1; i++)
    {
        integer += (str[i] - 48) * pow(10, position);
        position--;
    }

    return integer;
}

// recursive implementation of above function
int atoi_recursive(char *str)
{
    size_t length = strlen(str);
    if(length == 2) return str[0] - 48;
    return (str[0] - 48) * pow(10, length - 2) + atoi_recursive(str + 1);
}
