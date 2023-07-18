#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int charToInt(char character);

int main(int argc, char *argv[])
{
    if(argc <= 1 || argc > 2)
    {
        printf("Usage: ./caesar key");
        return 1;
    }

    char *end;
    long key = strtol(argv[1], &end, 10);

    if (argv[1] == end)
    {
        printf("Usage: ./caesar key");
        return 1;
    }

    key %= 26;
    printf("key: %li\n", key);

    char* input;
    size_t size;

    printf("plaintext: ");
    getline(&input, &size, stdin);

    int length = strlen(input);
    char output[length];

    for(int i = 0; i < length - 1; i++)
    {
        int asciiIndex = input[i];

        if (asciiIndex > 64 && asciiIndex < 91)
        {
            int alphabetIndex = (asciiIndex - 65 + key) % 26;
            output[i] = alphabetIndex + 65;
        }

        else if (asciiIndex > 96 && asciiIndex < 123)
        {
            int alphabetIndex = (asciiIndex - 97 + key) % 26;
            output[i] = alphabetIndex + 97;
        }

        else
        {
            output[i] = input[i];
        }
    }

    printf("ciphertext: ");
    printf("%s\n", output);
}

