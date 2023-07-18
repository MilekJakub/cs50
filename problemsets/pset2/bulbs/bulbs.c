#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const int BITS_IN_BYTE = 8;

char* charToBinary(char character);
void print_bulb(char bit);

int main(void)
{
    char *input;
    int read;
    size_t length;

    do
    {
        printf("Message: ");
        read = getline(&input, &length, stdin);
    }
    while(read == -1);

    length = strlen(input);

    for (int i = 0; i < length - 1; i++)
    {
        char* binary = charToBinary(input[i]);
        for (int j = 0; j < BITS_IN_BYTE; j++)
        {
            print_bulb(binary[j]);
        }
        printf("\n");
    }

}

char* charToBinary(char character)
{
    int charNumber = character;
    char *output = malloc(sizeof(char) * BITS_IN_BYTE);

    for(int i = BITS_IN_BYTE - 1; i >= 0; i--)
    {
        if (charNumber == 0 || charNumber % 2 == 0)
        {
            output[i] = '0';
        }

        else
        {
            output[i] = '1';
        }

        // weird, I divide by 0 and there is no errors ¯\_(ツ)_/¯
       charNumber /= 2;
    }

    return output;
}

void print_bulb(char bit)
{
    if (bit == '0')
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == '1')
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}

