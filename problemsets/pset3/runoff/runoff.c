#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

typedef struct
{
    char *name;
    int votes;
    bool eliminated;
}
candidate;

candidate candidates[MAX_CANDIDATES];

int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, char *name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    candidate_count = argc - 1;

    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
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

    if(line == end || converted < 1 || converted > MAX_VOTERS)
    {
        printf("Invalid number of voters.\n");
        return 1;
    }

    int voter_count = converted;

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {
        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            line = NULL;
            buffersize = 0;
            nread = -1;

            printf("Rank %i: ", j + 1);

            nread = getline(&line, &buffersize, stdin);
            if(nread == -1)
            {
                printf("ERROR! An error occured while getting vote.");
            }

            // Record vote, unless it's invalid
            if (!vote(i, j, line))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }

    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, char *name)
{
    name[strlen(name) - 1] = '\0';
    for(int i = 0; i < candidate_count; i++)
    {
        if(strcmp(candidates[i].name, name) == 0)
        {
            preferences[voter][rank]++;
            return true;
        }
    }

    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for(int i = 0; i < candidate_count; i++)
    {
        if(!candidates[i].eliminated)
            candidates[i].votes = preferences[i][0];
    }

    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // min_votes_to_win > 50%
    int min_votes_to_win = (voter_count / 2) + 1;

    for(int i = 0; i < candidate_count; i++)
    {
        if(candidates[i].votes >= min_votes_to_win)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }

    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min = candidates[0].votes;
    for(int i = 1; i < candidate_count; i++)
    {
        if(candidates[i].votes < min)
        {
            min = candidates[i].votes;
        }
    }

    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    for(int i = 0; i < candidate_count; i++)
    {
        if(candidates[i].votes != min)
        {
            return false;
        }
    }

    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for(int i = 0; i < candidate_count; i++)
    {
        if(candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }

    return;
}
