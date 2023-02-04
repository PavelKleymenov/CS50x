/*Implement a program that simulates the game of Scrabble
    such that it determines the winner of a scrabble-like game
where two players each enter their word, and the higher scoring player wins.*/
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Set the maximum length of input at 30
#define max_limit 30

// Assign points for every letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

// Add the prototype for the function that calculates the score of each player
int compute_score(char *word);

// Implement a function that simulates the game of Scrabble
int main(void)

{
    // Prompt the first player with input
    char word1[max_limit];
    printf("Player 1: ");

    /* Read a line from the user' input and store it
    into the string pointed to by the provided word */
    fgets(word1, max_limit, stdin);

    // Display first user' input
    printf("%s", word1);

    // Prompt the second player with input
    char word2[max_limit];
    printf("Player 2: ");

    /* Read a line from user' input and store it
    into the string pointed to by the provided word */
    fgets(word2, max_limit, stdin);

     // Display second user' input
     printf("%s", word1);

    // Calculate the number of points each player has received
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    //  Determine the winner of the game
    if (score1 > score2)

    {
        printf("Player 1 Wins.\n");
    }

    else if (score1 < score2)

    {
        printf("Player 2 Wins.\n");
    }

    else

    {
        printf("Tie.\n");
    }
}

/* Implement a function that computes and returns score
        for each string provided by the players */
int compute_score(char *word)

{
    // Make sure users has no points before the game starts
    int i = 0;
    int j;
    int l;

    for (j = 0, l = strlen(word); j < l; j++)
 
    {
        // Make sure uppercase and lowercase letters are given the same point values
        if (islower(word[j]))
 
        {
            i += POINTS[word[j] - 'a'];
        }

        else if (isupper(word[j]))
 
        {
            i += POINTS[word[j] - 'A'];
        }
    }

    // Return the total value that a given word brings in
    return i;
}