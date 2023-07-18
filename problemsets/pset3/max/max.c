#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int max(int array[], int n);

int main(void)
{
    int n;
    char *line;
    char *end;
    size_t buffersize = 0;
    ssize_t nread;
    long value;

    do
    {
        printf("Number of elements: ");
        nread = getline(&line, &buffersize, stdin);
        value = strtol(line, &end, 10);
    } 
    while (line == end || value < 1 || value > __INT_MAX__);

    n = value;
    int arr[n];

    line = NULL;
    end = NULL;
    buffersize = 0;

    for (int i = 0; i < n; i++)
    {
        do
        {
            printf("Element %i: ", i);
            nread = getline(&line, &buffersize, stdin);
            value = strtol(line, &end, 10);
        }
        while(line == end || value < __INT_MAX__ * -1 || value > __INT_MAX__);
        
        arr[i] = value;
    }

    // int len = sizeof(arr) / sizeof(arr[0]);
    // for(int i = 0; i < len; i++)
    // {
    //     printf("%i\n", arr[i]);
    // }

    printf("The max value is %i.\n", max(arr, n));
    return 0;
}

// TODO: return the max value
int max(int array[], int n)
{
    int max = array[0];
    for(int i = 1; i < n; i++)
    {
        if(array[i] > max)
            max = array[i];
    }

    return max;
}
