#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    if (argc <= 1 || argc > 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    char *key = argv[1];
    int keyLength = strlen(key);

    if(keyLength != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    char* input;
    size_t size;

    printf("plaintext: ");
    getline(&input, &size, stdin);

    int inputLength = strlen(input);

    for (int i = 0; i < inputLength - 1; i++)
    {
        int asciiIndex = input[i];
        if (asciiIndex > 64 && asciiIndex < 91)
        {
            int alphabetIndex = (asciiIndex - 65) % 26;
            input[i] = key[alphabetIndex];
        }

        else if (asciiIndex > 96 && asciiIndex < 123)
        {
            int alphabetIndex = (asciiIndex - 97) % 26;
            input[i] = tolower(key[alphabetIndex]);
        }
    }

    printf("Plain text: %s\n", input);

    return 0;
}
