// Implement a program that recovers JPEGs from a forensic image
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])

{
    // Make sure your program accepts only the name of a forensic image
    if (argc != 2)
    
    {
        return 1;
    }

    // Render an error if file couldn't get loaded
    FILE *initial = fopen(argv[1], "r");

    if (!initial)
    
    {
        printf("The file can't be opened for reading.\n");
        return 2;
    }

    // Declare a variable that stores the number of units in a buffer
    unsigned char buffer[512];

    // Initialize image counter
    int image_counter = 0;

    // Initialize an output variable
    FILE *new_image = NULL;

    // Make sure that generated files amount to the following format: ###.jpg
    char *filename = malloc(8 * sizeof(char));

    // Read 512 bytes into a buffer
    while (fread(buffer, sizeof(char), 512, initial) != 0)
    
    {
    
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        
        {
            // Make a new JPEG
            sprintf(filename, "%03i.jpg", image_counter);

            // Open up a new file
            new_image = fopen(filename, "w");

            // Count the images if found
            image_counter++;
        }

        // Make sure the input data has been used as intended
        if (new_image != NULL)
        
        {
            fwrite(buffer, sizeof(char), 512, new_image);
        }
    }

    // Make sure that there are no memory leaks
    free(filename);

    // Make sure all the streams get closed
    fclose(new_image);
    fclose(initial);

    // In closing return a false value
    return 0;
}