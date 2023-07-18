#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Max number of candidates
#define MAX 9

typedef struct
{
    char *name;
    int votes;
}
candidate;

candidate candidates[MAX];

int candidate_count;

bool vote(char *name);
void print_winner(void);

int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    candidate_count = argc - 1;

    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    char *line;
    char *end;
    size_t buffersize = 0;
    int nread;

    printf("Number of voters: ");
    nread = getline(&line, &buffersize, stdin);

    if(nread == -1)
    {
        printf("ERROR! An error occured while getting number of voters.\n");
        return 1;
    }
    
    long converted = strtol(line, &end, 10);

    if(line == end || converted < 1 || converted > __INT_MAX__)
    {
        printf("ERROR! Invalid number of voters.\n");
        return 1;
    }

    int voter_count = converted;

    line = NULL;
    buffersize = 0;
    nread = -1;
    for (int i = 0; i < voter_count; i++)
    {
        printf("Vote: ");
        nread = getline(&line, &buffersize, stdin);

        if(nread == -1)
        {
            printf("ERROR! An error occured while getting the vote.\n");
            continue;
        }

        char *name = line;

        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    print_winner();
}

// Update vote totals given a new vote
bool vote(char *name)
{
    name[strlen(name) - 1] = '\0';

    for(int i = 0; i < candidate_count; i++)
    {
        if(strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }

    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int max = candidates[0].votes;
    int winners = 0;

    for(int i = 1; i < candidate_count; i++)
    {
        if(candidates[i].votes > max)
            max = candidates[i].votes;
    }

    for(int i = 0; i < candidate_count; i++)
    {
        if(candidates[i].votes == max)
        {
            printf("%s\n", candidates[i].name);
        }
    }

    return;
}
