// Implement a program that runs a plurality election,
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Set the maximul number of candidates to run for a position
#define MAX 9

// Set the maximul length of a candidate name to 15
#define max_limit 15

/* Create a structure that has the candidate' name and the number
    of votes it receives in an election tour as its members*/
typedef struct

{
    char *name;
    int votes;
}

// Declare a variable representing candidate
candidate;

// Initialize an array that represents the maximum number of candidates
candidate candidates[MAX];

    /* Declare a counter variable that tracks
how many candidates have tried to enter an election */
int candidate_count;

    /*Make sure to include the prototypes
    for the functions implemented below*/
bool vote(char *name);
void print_winner(void);

// Implement a function that determines a winner of election
int main(int argc, char *argv[])

{
    /* Render an error message if the user provides more CLA
    than the program requires such that it can work as intended*/
    if (argc < 2)

    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;

    /*Render an error message if the number of candidates trying
    to get into election exceeds the one set by the rulebook */
    if (candidate_count > MAX)

    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    for (int i = 0; i < candidate_count; i++)
    
    {
        candidates[i].name = argv[i];
        candidates[i].votes = 0;
    }

    /* Make sure to set the number of voters such that candidates may catch one */
    int voter_count;
    printf("Number of voters: ");

    // Get and save the input the user has provided
    scanf("%d", &voter_count);


    /* Keep adding votes to the total for as long as
    someone has given one to a particular candidate */
    for (int i = 0; i < voter_count; i++)

    {
        // Make sure voters provide the name of their favourite candidate
        char name[max_limit];
        printf("Vote: ");

        /* Read a line from the user' input and store it
            into the string pointed to by the provided word */
        fgets(name, max_limit, stdin);

        // Display provided input
        printf("%s", name);

        /* Render an error message if one of the voters
        has tried to vote for a non existing candidate*/
        if (!vote(name))

        {
            printf("Invalid vote.\n");
        }

    }

    // Display winner of election
    print_winner();

}

/* Implement a function that updates the total number of votes
                once a new one is received*/
bool vote(char *name)

{
    // Identify candidate' name
    for (int i = 0; i < candidate_count; i++)

    {
        /*Compare two strings character by character so you can find out
        if the candidate you are looking for can be voter for */
        if (!strcmp(candidates[i].name, name))

        {
            candidates[i].votes++;
            return true;
        }
    }

    // If no such candidate has been found, then throw an error
    return false;
}

// Implement a function that prints out the name(s) of the election winner(s)
void print_winner(void)

{
    /* Make sure no votes have been added to the counter before the election*/
    int max_vote = 0;

    // Run the function for as long as there are ballots to be checked
    for (int i = 0; i < candidate_count; i++)

    {
        /* If the number of votes of a given candidate
        exceeds the maximum number of votes knows thus far,
            promptly update the value thereof*/
        if (candidates[i].votes > max_vote)

        {
            max_vote = candidates[i].votes;
        }

    }

    // Run the function up until the point where there are no more ballots to examine
    for (int i = 0; i < candidate_count; i++)

    {
        /* Once all the ballots have been counted,
        identify the election winner printing out their name */
        if (candidates[i].votes == max_vote)

        {
            printf("%s\n", candidates[i].name);
        }

    }
    
    return;
}