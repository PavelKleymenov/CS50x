// Implement a program that encrypts messages using Caesar’s cipher
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Set the maximum length of input that the program can handle
#define max_limit 100

int main(int argc, char *argv[])

{
    /* Render an error if more than one CLA
                has been provided*/
    if (argc != 2)
 
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    /* Iterate over each character comprising the key
        ensuring only digits are in that key*/
    for (int i = 0; i < strlen(argv[1]); i++)

        /*Render an error if the key contains
                other types of symbols*/
        if (isdigit(argv[1][i]) == false)
 
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }

    // Type cast the key into an integer
    int k = atoi(argv[1]);

    // Prompt users with plaintext
    char plaintext[max_limit];
    printf("plaintext: ");

    /* Read a line from the user' input and store it
    into the string pointed to by the provided word */
    fgets(plaintext, max_limit, stdin);

    // Render an encrypted output
    printf("ciphertext: ");

    // Iterate over character of users' input
    for (int j = 0; j < strlen(plaintext); j++)

    {
            /*Make sure user' input contains
        something other than alphabetical characters*/
        if (isalpha(plaintext[j]) == false)

        {
            printf("%c", plaintext[j]);
        }

        /*Make sure the encryption rendering is implemented
        correctly irrespective of the letters' case */
        if (isupper(plaintext[j]))
        
        {
            printf("%c", ((plaintext[j]) - 'A' + k) % 26 + 'A');
        }

        else if (islower(plaintext[j]))
        
        {

            printf("%c", (plaintext[j] - 'a' + k) % 26 + 'a');
        }
    }

    // Move the encrypted output to the next line
    printf("\n");
}