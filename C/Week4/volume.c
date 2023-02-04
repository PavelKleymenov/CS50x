// Implement a program that modifies the volume of an audio file.
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* Set the number of bytes in .wav header
       that the program can handle */
const int HEADER_SIZE = 44;


int main(int argc, char *argv[])

{
    // Render an error if users provide more than three CLA's
    if (argc != 4)

    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open the file for reading
    FILE *input = fopen(argv[1], "r");

    /*Render an error if the file doesn't exist*/
    if (input == NULL)
 
    {
        printf("Could not read the file.\n");
        return 1;
    }

    // Write data to the file that has been previously opened
    FILE *output = fopen(argv[2], "w");

    // Render an error if the file couldn't be written into memory
    if (output == NULL)
 
    {
        printf("Could not write the file.\n");
        return 1;
    }

    // Type cast the scaling factor
    float factor = atof(argv[3]);

    // Create an array of bytes so as to store the data from the WAV file header
    uint8_t header[HEADER_SIZE];

    // Read the bytes from the input file
    fread(header, HEADER_SIZE, 1, input);

    // Write the bytes from the input file
    fwrite(header, HEADER_SIZE, 1, output);

    // Create a “buffer” so as to store audio samples that you read from the WAV file
    int16_t buffer;

    // Read the data into the buffer
    while (fread(&buffer, sizeof(int16_t), 1, input))
    
    {
        // Increase/Decrease the volume using the scaling factor
        buffer *= factor;
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }

    // Close the files
    fclose(input);
    fclose(output);
}