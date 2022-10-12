#include <cs50.h>
#include <stdio.h>
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
bool check_parent(int parent_candidate, int target_candidate);

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
    // look for candidate called name
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            // if candidate found, update ranks and return true.
            // ranks[i] is the voters [ith] preference
            ranks[rank] = i;
            return true;
        }
    }

    // if no candidate found, don't update any ranks and return false
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // update the preferences array based on current voters ranks
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // add each pair of candidates to pairs array if one candidate is preferred over the other

    // outer loop to look at rows in preferences
    for (int rows = 0; rows < candidate_count; rows++)
    {
        // inner loop to look at columns in given row of preferences
        for (int cols = rows; cols < candidate_count; cols++)
        {
            // ignore when rows == cols, as these will be zero
            if (rows != cols)
            {
                // check which preference is higher, and add to pairs array if possible
                // update global variable pair_count to be the total number of pairs
                if (preferences[rows][cols] > preferences[cols][rows])
                {
                    pairs[pair_count].winner = rows;
                    pairs[pair_count].loser = cols;
                    pair_count++;
                }
                else if (preferences[cols][rows] > preferences[rows][cols])
                {
                    pairs[pair_count].winner = cols;
                    pairs[pair_count].loser = rows;
                    pair_count++;
                }
            }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO

    // sort pairs in order by decreasing strength of victory
    // use any sort algorithm

    int max_strength;
    int max_pair;
    int strength;

    int temp_winner;
    int temp_loser;

    // outer loop for pairs
    for (int i = 0; i < pair_count; i++)
    {
        max_strength = 0;
        strength = 0;
        int j;

        // find largest strength in remaining pairs
        for (j = i; j < pair_count; j++)
        {
            strength = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner];
            if (strength > max_strength)
            {
                max_strength = strength;
                max_pair = j;
            }
        }

        // swap to start of pairs array
        // set temp variables
        temp_winner = pairs[i].winner;
        temp_loser = pairs[i].loser;
        // set i to max_pair
        pairs[i].winner = pairs[max_pair].winner;
        pairs[i].loser = pairs[max_pair].loser;
        // move first pair to where max_pair was
        pairs[max_pair].winner = temp_winner;
        pairs[max_pair].loser = temp_loser;

    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
// update locked to create the locked graph by adding all edges in decreasing order of victory strength, as long as there is no cycle
void lock_pairs(void)
{
    // cycle through pairs
    for (int i = 0; i < pair_count; i++)
    {
        // check if pairs[i].winner has any parents that ultimately match pairs[i].loser
        if (check_parent(pairs[i].winner, pairs[i].loser) == false)
        {
            // if return is false, e.g. parent(s) don't match proposed loser, then there is no cycle and set locked to true
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// recursive function to keep checking parent_candidate for cycles
bool check_parent(int parent_candidate, int target_candidate)
{
    // get parent_candidate(s)
    for (int i = 0; i < candidate_count; i++)
    {
        // parent_candidates must be already set to true
        if (locked[i][parent_candidate] == true)
        {
            // does it match target_candidate? If yes, return true. If no, check_parent again with new parent_candidate
            if (i == target_candidate)
            {
                return true;
            }
            else
            {
                return check_parent(i, target_candidate);
            }
        }
    }

    // if none, return false
    return false;
}

// Print the winner of the election
// print out the winner of the election, who will be the source of the graph e.g. no locked arrow pointing at them
// you may assume there will not be more than one source
void print_winner(void)
{
    // cycle through candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // check to see if candidate is all false in locked, e.g. no pointing to it, and therefore the source/winner
        int true_flag = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                true_flag = 1;
                j = candidate_count;
            }
        }

        if (true_flag == 0)
        {
            printf("%s\n", candidates[i]);
            i = candidate_count;
        }
    }

    return;
}
