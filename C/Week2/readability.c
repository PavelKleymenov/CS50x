/*Implement a program that calculates the approximate grade level
                needed to comprehend a given text */
#include <ctype.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

// Set the maximum number of characters a program can handle
#define max_limit 400

// Add the prototypes for functions implemented below
int count_letters(char *text);
int count_words(char *text);
int count_sentenses(char *text);

/* Implement a function that computes the grade level needed to comprehend
                        the text provided  by the user */
int main(void)

{
    // Prompt users with input
    char input[max_limit];
    printf("Text: ");
    fgets(input, max_limit, stdin);

    /* Initialize three counter variables that track how many
        letters, words and sentences there are in the text */
    int letters = count_letters(input);
    int words = count_words(input);
    int sentenses = count_sentenses(input);

    // Initialize coefficients that are used in The Coleman-Liau test
    float L = (float) letters / (float) words * 100;
    float S = (float) sentenses / (float) words * 100;

    // Estimate an approximate grade level via the Coleman-Liau readability test equation
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    // Print out a grade level based upon the Coleman-Liau readability test' results
    {
        if (index < 1)

        {
            printf("Before Grade 1");
        }

        else if (index > 16)

        {
            printf("Grade 16+");
        }

        else

        {
            printf("Grade %i", index);
        }

        // Move the output to the next row
        printf("\n");
    }
}



// Implement a function that calculates how many letters there are in a given text
int count_letters(char *text)

{
    /* Make sure no letters have been added to the counter before users provide input */
    int letters = 0;

    //  Loop through the entirety of a given text
    for (int j = 0, i = strlen(text); j < i; j++)

    {
        /* If there's nothing except alphabetical characters in the text
                increment the total value of letters in that text */
        if (isalpha(text[j]))

        {
            letters ++;
        }
    }

    // Return the total number of letters in a given text
    return letters;
}

// Implement a function that calculates how many words there are in a given text
int count_words(char *text)

{
        /* Set the initial value of words to one,
    because the first one is the prompt for input itself */
    int words = 1;

    // Iterate over the text
    for (int j = 0, i = strlen(text); j < i; j++)

        /* Identify all whitespaces so you can count the total value of words
    in a given text, incrementing the it every time such instance is detected */

        if (text[j] == ' ')

        {
            words++;
        }

    // Return the total number of words in a given text
    return words;
}

// Implement a function that calculates how many sentenses there are in a given text
int count_sentenses(char *text)

{
    /* Make sure no letters have been added to the counter before users provide input */
    int sentenses = 0;

    // Iterate over the text
    for (int j = 0, i = strlen(text); j < i; j++)
   
    {
        /* Increment the value of sentences every time one of the
        punctuation marks outlined below is detected*/
        if (text[j] == '.' || text[j] == '!' || text[j] == '?')

        {
            sentenses++;
        }
    }

    // Return the total number of sentences in a given text
    return sentenses;
}