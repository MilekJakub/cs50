#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int count_letters(char *text, int length);
int count_words(char *text, int length);
int count_sentences(char *text, int length);

int main(void)
{
    char *text = NULL;
    size_t buffersize = 0;
    ssize_t size;
    int length = 0;
    int letters = 0;
    int words = 0;
    int sentences = 0;

    do
    {
        printf("Text: ");
        size = getline(&text, &buffersize, stdin);
        length = size - 1;
        letters = count_letters(text, length);
        words = count_words(text, length);
        sentences = count_sentences(text, length);
    }
    while(letters == 0 || words == 0 || sentences == 0);

    // Coleman-Liau formula
    // index = 0.0588 * L - 0.296 * S - 15.8

    float L = (float)letters / (float)words * 100;
    float S = (float)sentences / (float)words * 100;
    int index = roundf(0.0588 * L - 0.296 * S - 15.8);

    if(index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if(index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int count_letters(char *text, int length)
{
    int letters = 0;

    for(int i = 0; i < length; i++)
    {
        // lowercase
        if(text[i] > 64 && text[i] < 91)
            letters++;

        // uppercase
        if(text[i] > 96 && text[i] < 123)
            letters++;
    }

    return letters;
}

int count_words(char *text, int length)
{
    int words = 0;
    bool space = false;

    for(int i = 0; i < length; i++)
    {
        if(!space && text[i] == ' ')
        {
            space = true;
        }

        if(space && text[i] != ' ')
        {
            words++;
            space = false;
        }
    }

    if(words != 0)
        words++;

    return words;
}

int count_sentences(char *text, int length)
{
    int sentences = 0;

    for(int i = 0; i < length; i++)
    {
        if(text[i] == '.' || text[i] == '?' || text[i] == '!')
            sentences++;
    }

    return sentences;
}

