// Implements a program that makes the dictionary functional
#include <stdio.h>
#include <strings.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

/* Declare a counter variable that tracks the number of words
                    added to the dictionary*/
unsigned int countwords;

// Create a structure that represents a single block in a hash table
typedef struct node

{
    char word[LENGTH + 1];
    struct node *next;
}

// Declare a variable representing the block in the hash table
node;

// Set the number of elements in the hash table
const unsigned int N = 50000;

// Declare the hash table
node *table[N];

/* Implement a function that determines whether or not a given word is in the dictionary */
bool check(const char *word)

{
    // Initialize a variable representing word' length
    int n = strlen(word);

    // Declare an array representing dictionary' length
    char dictword[LENGTH + 1];

    // Iterate over a word character by character, setting it to lowercase
    for (int i = 0; i < n; i++)

    {
        dictword[i] = tolower(word[i]);
    }

    // Determine where a given word ends, using the null terminator
    dictword[n] = '\0';

    /* Hash a word so as to obtain a fixed length value
        that helps users to uniquely identify data*/
    int index = hash(dictword);

    // Make sure the cursor points to the same address as the hashtable index
    node *cursor = table[index];

    /* Execute the code within the curly braces, for
        as long as the loop condition evaluates to TRUE*/
    while (cursor != NULL)

    {
        // Compare the strings case - insensitively
        if (strcasecmp(cursor->word, dictword) == 0)

        {
            // Should the word be found, return true
            return true;
        }

        // Else if the word has not yet been found, keep on looking
        else

        {
            cursor = cursor -> next;
        }
    }

    // Otherwise, no words have been found
    return false;
}

// Implement a function that hashes word to a number
unsigned int hash(const char *word)

{
    // Prompt the user with input representing the word you want to hash
    unsigned int var = 0;

    // Iterate over every character in a given word
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        var = (var << 2) ^ word[i];
    }

    // Make sure the output is no greater than N
    return var % N;
}

// Implement a function that loads the dictionary into memory
bool load(const char *dictionary)

{
    // Open up the dictionary file for reading
    FILE *opdict = fopen(dictionary, "r");

    // Render an error if there's not enough memory to allocate
    if (opdict == NULL)

    {
        return false;
    }

    // Declare an array that stores the number of words found in the dictionary
    char dictword[LENGTH + 1];

    // Run through the dictionary up until the end of file is reached
    while (fscanf(opdict, "%s", dictword) != EOF)

    {
        // Allocate the memory required to store a new word
        node *n = malloc(sizeof(node));

        // Prompt users with an error if memory can't be allocated
        if (n == NULL)

        {
            return false;
        }

        // Copy the word into the dictionary block
        strcpy(n -> word, dictword);

        // Set the next pointer to NULL
        n -> next = NULL;

        // Hash a word to obtain a hash value
        int index = hash(dictword);

        // Make sure you don't lose any elements of the hash table
        if (table[index] == NULL)

        {
            table[index] = n;
        }

        else

        {
            // Take the new node and set its next pointer to be the first element in the hash table
            n -> next = table[index];

            // Insert the new node into the hash table
            table[index] = n;
        }

        // Increment the total value of words in the dictionary
        countwords++;
    }

    // Make sure to close the dictionary file
    fclose(opdict);
    return true;
}

// Implement a function that identifies the number of words in the fully loaded dictionary
unsigned int size(void)

{
    // Return the number of words added to the dictionary representing the size thereof
    return countwords;
}

// Implement a function that unloads the dictionary from memory
bool unload(void)

{
    // iterate over the hash table
    for (int i = 0; i < N; i++)
    
    {
        // Make cursor move through each element of the linked list
        while (table[i] != NULL)

        {
            node *cur = table[i] -> next;
            free(table[i]);
            table[i] = cur;
        }
    }

    return true;
}