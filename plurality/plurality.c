#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);
void bubble_sort(void);


int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }


    // Populate array of candidates
    candidate_count = argc - 1;

    for (int i = 0; i < argc-1; i++)
    {
        if (alpha_names(argv[i]) == false)
        {
            printf("Usage: plurality [candidate ...]\n");
            return 1;
        }
    }

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

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

bool alpha_names(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (!isalpha(s[i]))
        {
            return false;
        }
    }
    return true;

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    for (int i=0; i < candidate_count; i++)
    {
        if(strcmp(candidates[i].name, name)==0)
        {
            candidates[i].votes+= 1;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{

    // Sort votes from high to low
    bubble_sort();

    // Print winner
    for (int i=0; i < candidate_count; i++)
    {
        printf("%s\n", candidates[i].name);
        if (candidates[i].votes > candidates[i+1].votes)
        {
            return;
        }

    }
    return;
}

// Sort votes from high to low
void bubble_sort(void)
{
    for (int i=0; i<candidate_count-1;i++)
    {
        for (int j =0; j < candidate_count-2; j++)
        {
            if (candidates[j].votes < candidates[j+1].votes)
            {
                int store_vote = candidates[j].votes;
                char store_names[MAX];

                // Copy the name to store_names
                strcpy(store_names, candidates[j].name);

                // Swap votes
                candidates[j].votes = candidates[j + 1].votes;
                candidates[j + 1].votes = store_vote;

                // Swap names
                strcpy(candidates[j].name, candidates[j + 1].name);
                strcpy(candidates[j + 1].name, store_names);

            }
        }

    }

}
