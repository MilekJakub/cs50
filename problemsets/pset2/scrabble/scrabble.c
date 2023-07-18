#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
int POINTS_LENGTH = 26;

int compute_score(char* word);

int main(void)
{
    // Get input words from both players
    char *word1 = NULL;
    char *word2 = NULL;

    int read;
    size_t length;

    do
    {
        printf("Player 1: ");
        read = getline(&word1, &length, stdin);
    }
    while(read == -1);

    do
    {
        printf("Player 2: ");
        read = getline(&word2, &length, stdin);
    }
    while(read == -1);

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    if(score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if(score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(char* word)
{
    size_t length = strlen(word);
    int score = 0;

    for (int i = 0; i < length; i++)
    {
        int index = toupper(word[i]);
        if(index > 64 && index < 91)
        {
            score += POINTS[index - 65];
        }
    }

    return score;
}

