#include <cs50.h>
#include <stdio.h>

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
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool check_string(string first, string second);
int get_index(int, int []);
bool check_cylces(pair);

int main(int argc, string argv[])
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
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int j = 0; j < candidate_count; j++)
    {
        if (check_string(name, candidates[j]))
        {
            ranks[rank] = j;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    int index_i = 0; //these are the location for rank
    int index_j = 0; //the one with lower value is preferred

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i == j)
            {
                continue;
            }
            else
            {
                index_i = get_index(i, ranks);
                index_j = get_index(j, ranks);
                if (index_i < index_j)
                {
                    preferences[i][j]++;
                }
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i <= candidate_count; i++)
    {
        for (int j = 0; j <= candidate_count; j++)
        {
            pair member;
            if (j <= i)
            {
                continue;
            }
            if (preferences[i][j] > preferences[j][i]) //check across the diagonal (matrix)
            {
                member.winner = i;
                member.loser = j;
                pairs[pair_count] = member;
                pair_count++;
            }
            else if (preferences[j][i] > preferences[i][j])
            {
                member.winner = j;
                member.loser = i;
                pairs[pair_count] = member;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory, bubble sort
void sort_pairs(void)
{
    bool run = false;
    int dummy = 0;
    pair temp;

    for (int i = 0; i < candidate_count; i++)
    {
        dummy = i + 1;
        if (dummy == candidate_count)
        {
            break;
        }
        while (!run)
        {
            run = true;
            if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[dummy].winner][pairs[dummy].loser])
            {
                temp = pairs[i];
                pairs[i] = pairs[dummy];
                pairs[dummy] = temp;
                run = false;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (check_cylces(pairs[i]))
        {
            continue;
        }
        else
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int counter = 0;
    int winner = -1;

    for (int i = 0; i < candidate_count; i++)
    {
        counter = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == false)
            {
                counter++;
            }
        }
        if (counter == candidate_count)
        {
            winner = i;
            printf("%s\n", candidates[winner]);
        }
    }
    return;
}

bool check_string(string first, string second) //this check if two string have identical contents
{
    int length = 0;

    while (first[length] != '\0')
    {
        length++;
    }

    for (int j = 0; j < length; j++) //check if the characters match, I coded this from scratch because of specs
    {
        if (first[j] != second[j])
        {
            return false;
        }
    }
    return true;
}

int get_index(int query, int ranks[]) //this gets the index of an array
{
    for (int j = 0; j < candidate_count; j++)
    {
        if (query == ranks[j])
        {
            return j;
        }
    }

    return -1;
}

bool check_cylces(pair member) //this function checks for cycles
{
    for (int i = 0; i < pair_count; i++) //checks if the lower leads to a row of a winner
    {
        if (locked[member.loser][i] == true)
        {
            return true;
        }

    }
    return false;
}