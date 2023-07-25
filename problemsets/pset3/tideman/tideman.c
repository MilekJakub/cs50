#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
char *candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, char *name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
bool has_cycle();
void lock_pairs(void);
void print_winner(void);

int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;

    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;

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
        printf("Invalid number of voters.\n");
        return 1;
    }

    int voter_count = converted;

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

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

            if (!vote(j, line, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    for(int i = 0; i < candidate_count; i++)
    {
        for(int j = 0; j < candidate_count; j++)
        {
            printf("%i ", preferences[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, char *name, int ranks[])
{
    name[strlen(name) - 1] = '\0';

    for(int i = 0; i < candidate_count; i++)
    {
        if(strcmp(candidates[i], name) == 0)
        {
            ranks[i] = rank;
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for(int i = 0; i < candidate_count; i++)
    {
        for(int j = 0; j < candidate_count; j++)
        {
            if(i == j) continue;

            // rank 0 is better than rank 1 or rank 2
            if(ranks[i] < ranks[j])
            {
                preferences[i][j]++;
            }
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for(int i = 0; i < candidate_count; i++)
    {
        for(int j = 0; j < candidate_count; j++)
        {
            if(i == j) continue;
            if(preferences[i][j] > preferences[j][i])
            {
                pair p = { i, j };
                pairs[pair_count] = p;
                pair_count++;
            }
        }
    }

    for(int i = 0; i < pair_count; i++)
    {
        printf("Pair %i\n", i);
        printf("winner: %i\nloser: %i\n", pairs[i].winner, pairs[i].loser);
        printf("\n");
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int scores[pair_count];

    for(int i = 0; i < pair_count; i++)
    {
        scores[i] = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
    }

    printf("Scores: \n");
    for(int i = 0; i < pair_count; i++)
    {
        printf("%i ", scores[i]);
    }
    printf("\n");

    // using bubblesort, but could be any implementation of sorting algorithm
    // here sorting two arrays but comparing elements from one
    for(int i = 0; i < pair_count - 1; i++)
    {
        bool swap = false;

        for(int j = 1; j < pair_count - 1; j++)
        {
            if(scores[i] > scores[j])
            {
                int tempScore = scores[i];
                scores[i] = scores[j];
                scores[j] = tempScore;

                pair tempPair = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = tempPair;

                swap = true;
            }
        }

        if(!swap) break;
    }

    printf("Sorted scores: \n");
    for(int i = 0; i < pair_count; i++)
    {
        printf("%i ", scores[i]);
    }
    printf("\n");
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // need one column without 'true' value
    for(int i = 0; i < candidate_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;
        if(has_cycle())
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
    }

    printf("\nLocked:\n");
    for(int i = 0; i < candidate_count; i++)
    {
        for(int j = 0; j < candidate_count; j++)
        {
            printf("%i ", locked[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

bool has_cycle()
{
    bool isWholeColumnFalse = true;

    for(int i = 0; i < candidate_count; i++)
    {
        for(int j = 0; j < candidate_count; j++)
        {
            if(locked[j][i])
            {
                isWholeColumnFalse = false;
            }
        }

        if(isWholeColumnFalse) return false;
        isWholeColumnFalse = true;
    }

    return true;
}

// Print the winner of the election
void print_winner(void)
{
    bool isWholeColumnFalse = true;

    for(int i = 0; i < candidate_count; i++)
    {
        for(int j = 0; j < candidate_count; j++)
        {
            if(locked[j][i])
            {
                isWholeColumnFalse = false;
            }
        }

        if(isWholeColumnFalse)
        {
            printf("%s\n", candidates[i]);
            return;
        }

        isWholeColumnFalse = true;
    }

    printf("Something went wrong...\n");
    return;
}
