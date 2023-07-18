#include <stdio.h>
#include <string.h>

char* replace(char *input);

int main(int argc, char *argv[])
{
    if(argc <= 1 || argc > 2)
    {
        printf("Usage: ./no-vovels.c word\n");
        return 1;
    }

    char *output = replace(argv[1]);
    printf("%s\n", output);

    return 0;
}

char* replace(char input[])
{
    int length = strlen(input);
    for (int i = 0; i < length; i++)
    {
        switch(input[i])
        {
            case 'a':
                input[i] = '6';
                break;

            case 'e':
                input[i] = '3';
                break;

            case 'i':
                input[i] = '1';
                break;

            case 'o':
                input[i] = '0';
                break;
        }
    }

    return input;
}
