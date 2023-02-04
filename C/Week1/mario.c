// Implement a program that prints out a half-pyramid of a specified height
#include <stdio.h>

int main(void)

{
    // Declare variable representing height, row, column, space
    int h, r, c, s;
    do

    {
        // Prompt user with input
        printf("What height should a pyramid have?: \n");

        // Get and save the input the user has typed
        scanf("%d", &h);
    }

    // Make sure the pyramid is no taller than 8 blocks, while being at least 1 block in height
    while (h < 1 || h > 8);

    // For each row of the pyramid
    for (r = 0; r <= h - 1; r++)
    
    {
        // For each space block on the left side of the pyramid
        for (s = 1; s <= h - r - 1; s++)
       
        {
            // Print a space block
            printf(" ");
        }

        // For each column of the pyramid
        for (c = 0; c <= r; c++)
       
        {
            // Print a building block
            printf("#");
        }
        
        // Move to the next row
        {
            printf("\n");
        }
    }
}