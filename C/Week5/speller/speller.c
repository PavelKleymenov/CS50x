// Implement a program that spell-checks provided input

#include <ctype.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>

#include "dictionary.h"

// Undefine any definitions
#undef calculate
#undef getrusage

// Set default dictionary
#define DICTIONARY "dictionaries/large"

// Include the prototype for the function implemented below
double calculate(const struct rusage *b, const struct rusage *a);

int main(int argc, char *argv[])
{
    // Render an error if users provide more than one CLA
    if (argc != 2 && argc != 3)

    {
        printf("Usage: ./speller [DICTIONARY] text\n");
        return 1;
    }

    // Create a structure that is used for timing data
    struct rusage before, after;

    // Declare the benchmarks against which the operations' timing can be compared
    double time_load = 0.0, time_check = 0.0, time_size = 0.0, time_unload = 0.0;

    // Set the dictionary up for usage
    char *dictionary = (argc == 3) ? argv[1] : DICTIONARY;

    // Load the dictionary
    getrusage(RUSAGE_SELF, &before);
    bool loaded = load(dictionary);
    getrusage(RUSAGE_SELF, &after);

    // ARender an error if dictionary couldn't get loaded
    if (!loaded)

    {
        printf("Could not load %s.\n", dictionary);
        return 1;
    }

    // Calculate the time that is required to load the dictionary
    time_load = calculate(&before, &after);

    // Try to open the text for reading
    char *text = (argc == 3) ? argv[2] : argv[1];
    FILE *file = fopen(text, "r");

    /* Render an error if the textfile couldn't get opened,
            promplty unloading the dictionary */
    if (file == NULL)

    {
        printf("Could not open %s.\n", text);
        unload();
        return 1;
    }

    // Print misspelled words
    printf("\nMISSPELLED WORDS\n\n");

    // Prepare to spell-check
    int index = 0, misspellings = 0, words = 0;
    char word[LENGTH + 1];

    // Spell-check every word in text
    char c;

    while (fread(&c, sizeof(char), 1, file))
   
    {
        // Allow only alphabetical characters and apostrophes
        if (isalpha(c) || (c == '\'' && index > 0))
   
        {
            // Append character to word
            word[index] = c;
            index++;

            // Ignore alphabetical strings that are too long to be words
            if (index > LENGTH)
   
            {
                // Consume remainder of alphabetical string
                while (fread(&c, sizeof(char), 1, file) && isalpha(c));

                // Prepare for the new word
                index = 0;
            }
        }

        // Ignore words with numbers (like MS Word can)
        else if (isdigit(c))
   
        {
            // Consume remainder of alphanumeric string
            while (fread(&c, sizeof(char), 1, file) && isalnum(c));

            // Prepare for the new word
            index = 0;
        }

        // Terminate the word, once founded
        else if (index > 0)
   
        {
            // Terminate current word
            word[index] = '\0';

            // Update counter
            words++;

            // Check given word' spelling
            getrusage(RUSAGE_SELF, &before);
            bool misspelled = !check(word);
            getrusage(RUSAGE_SELF, &after);

            // Update the benchmark initialized above
            time_check += calculate(&before, &after);

            // Print the word in case it's misspelled
            if (misspelled)
   
            {
                printf("%s\n", word);
                misspellings++;
            }

            // Prepare for the next word
            index = 0;
        }
    }

    // Make sure no errors were omitted
    if (ferror(file))
   
    {
        fclose(file);
        printf("Error reading %s.\n", text);
        unload();
        return 1;
    }

    // Close provided text
    fclose(file);

    // Determine dictionary's size
    getrusage(RUSAGE_SELF, &before);
    unsigned int n = size();
    getrusage(RUSAGE_SELF, &after);

    // Calculate how long it takes to determine dictionary's size
    time_size = calculate(&before, &after);

    // Unload the dictionary
    getrusage(RUSAGE_SELF, &before);
    bool unloaded = unload();
    getrusage(RUSAGE_SELF, &after);

    // Render an error if the dictionary couldn't get unloaded
    if (!unloaded)
    {
        printf("Could not unload %s.\n", dictionary);
        return 1;
    }

    // Calculate how long it takes to unload the dictionary
    time_unload = calculate(&before, &after);

    // Having gone through entirity of the text, load all the benchmarks
    printf("\nWORDS MISSPELLED:     %d\n", misspellings);
    printf("WORDS IN DICTIONARY:  %d\n", n);
    printf("WORDS IN TEXT:        %d\n", words);
    printf("TIME IN load:         %.2f\n", time_load);
    printf("TIME IN check:        %.2f\n", time_check);
    printf("TIME IN size:         %.2f\n", time_size);
    printf("TIME IN unload:       %.2f\n", time_unload);
    printf("TIME IN TOTAL:        %.2f\n\n",
           time_load + time_check + time_size + time_unload);

    return 0;
}

// Implement a function that returns the number of seconds between b and a
double calculate(const struct rusage *b, const struct rusage *a)

{
    if (b == NULL || a == NULL)

    {
        return 0.0;
    }

    else

    {
        return ((((a->ru_utime.tv_sec * 1000000 + a->ru_utime.tv_usec) -
                  (b->ru_utime.tv_sec * 1000000 + b->ru_utime.tv_usec)) +
                 ((a->ru_stime.tv_sec * 1000000 + a->ru_stime.tv_usec) -
                  (b->ru_stime.tv_sec * 1000000 + b->ru_stime.tv_usec)))
                / 1000000.0);
    }
}