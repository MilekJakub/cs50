#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define LISTSIZE 1000

#define EXACT 2
#define CLOSE 1
#define WRONG 0

// ANSI color codes
#define GREEN   "\e[38;2;255;255;255;1m\e[48;2;106;170;100;1m"
#define YELLOW  "\e[38;2;255;255;255;1m\e[48;2;201;180;88;1m"
#define RED     "\e[38;2;255;255;255;1m\e[48;2;220;20;60;1m"
#define RESET   "\e[0;39m"

char* get_guess(int wordsize);
int check_word(char* guess, int wordsize, int status[], char* choice);
void print_word(char* guess, int wordsize, int status[]);

int main(int argc, char* argv[])
{
    if(argc <= 1 || argc > 2)
    {
        printf("Usage: ./wordle wordsize\n");
        return 1;
    }

    char *end = NULL;
    long wordsize = strtol(argv[1], &end, 10);

    if(argv[1] == end)
    {
        printf("Usage: ./wordle wordsize\n");
        return 1;
    }

    if(wordsize < 5 || wordsize > 8)
    {
        printf("Error: 'wordsize' must be either 5, 6, 7, or 8\n");
        return 1;
    }

    // eg. '5.txt'
    char wl_filename[6];
    sprintf(wl_filename, "%li.txt", wordsize); // sprintf writes formatted text to an array of char, as opposed to a stream

    FILE *wordlist = fopen(wl_filename, "r");
    if (wordlist == NULL)
    {
        printf("Error opening file %s.\n", wl_filename);
        printf("Check if you have required files: 5.txt -> 8.txt\n");
        return 1;
    }

    // load word file into an array of size LISTSIZE
    // array of strings -> list of words from file
    char options[LISTSIZE][wordsize + 1];
    for (int i = 0; i < LISTSIZE; i++)
    {
        fscanf(wordlist, "%s", options[i]); // reads formatted input from a stream
    }

    srand(time(NULL));
    char* choice = options[rand() % LISTSIZE];

    int guesses = wordsize + 1;
    bool won = false;

    printf(GREEN"This is WORDLE50"RESET"\n");
    printf("You have %i tries to guess the %li-letter word I'm thinking of\n", guesses, wordsize);

    // main game loop
    for (int i = 0; i < guesses; i++)
    {
        char* guess = get_guess(wordsize);
        printf("guess: %s\n", guess);

        // array to hold guess status, initially set to zero
        int status[wordsize];
        for(int j = 0; j < wordsize - 1; j++)
        {
            status[j] = 0;
        }

        int score = check_word(guess, wordsize, status, choice);

        printf("Guess %i: ", i + 1);

        // Print the guess
        print_word(guess, wordsize, status);

        if (score == EXACT * wordsize)
        {
            won = true;
            break;
        }
    }

    if(won)
    {
        printf("You won!\n");
    }
    else
    {
        printf("You lost!\n");
        printf("The word was: %s\n", choice);
    }

    return 0;
}

char* get_guess(int wordsize)
{
    char *guess = NULL;
    size_t length = 0;

    do
    {
        printf("Input a %i-letter word: ", wordsize);
        getline(&guess, &length, stdin);
        length = strlen(guess);
    }
    while(length - 1 > wordsize || length - 1 < wordsize);

    return guess;
}

int check_word(char* guess, int wordsize, int status[], char* choice)
{
    int score = 0;

    for(int i = 0; i < wordsize; i++)
    {
        if(guess[i] == choice[i])
        {
            status[i] = 2;
            score += 2;
        }
        else
        {
            for(int j = 0; j < wordsize; j++)
            {
                if(guess[i] == choice[j])
                {
                    status[i] = 1;
                    score += 1;
                }
            }
        }
    }

    return score;
}

void print_word(char* guess, int wordsize, int status[])
{
    for(int i = 0; i < wordsize; i++)
    {
        if(status[i] == 2)
        {
            printf(GREEN"%c"RESET, guess[i]);
        }
        else if(status[i] == 1)
        {
            printf(YELLOW"%c"RESET, guess[i]);
        }
        else
        {
            printf(RED"%c"RESET, guess[i]);
        }
    }

    printf("\n");
    return;
}
