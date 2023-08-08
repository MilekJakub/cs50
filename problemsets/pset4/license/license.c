#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int LICENSE_PLATE_LENGTH = 6;
const int NUMBER_OF_LICENSE_PLATES = 8;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./read infile\n");
        return 1;
    }

    FILE *infile = fopen(argv[1], "r");

    if (infile == NULL)
    {
        printf("Cannot open the file: '%s'\n", argv[1]);
        return 2;
    }

    char *buffer = malloc(sizeof(char) * (LICENSE_PLATE_LENGTH + 1));
    char **plates = malloc(sizeof(char*) * NUMBER_OF_LICENSE_PLATES);
    for (int i = 0; i < NUMBER_OF_LICENSE_PLATES; i++)
    {
        plates[i] = malloc(sizeof(char) * (LICENSE_PLATE_LENGTH + 1));
    }

    int index = 0;
    size_t length = 0;

    while (getline(&buffer, &length, infile) != -1)
    {
        buffer[LICENSE_PLATE_LENGTH] = '\0';
        strcpy(plates[index], buffer);
        index++;
    }

    for (int i = 0; i < NUMBER_OF_LICENSE_PLATES; i++)
    {
        printf("%s\n", plates[i]);
    }

    for (int i = 0; i < NUMBER_OF_LICENSE_PLATES; i++)
    {
        free(plates[i]);
    }
    free(buffer);
    fclose(infile);
    free(plates);

    return 0;
}

