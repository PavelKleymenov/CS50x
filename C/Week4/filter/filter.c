#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"

int main(int argc, char *argv[])
{
    // Define filters that are allowed
    char *filters = "bgrs";

    /* Parse CLA's, rendering an error message if user has tried
        to utilize a filter he doesn't have access to*/
    char filter = getopt(argc, argv, filters);
    if (filter == '?')

    {
        printf("Invalid filter.\n");
        return 1;
    }

    /* Prompt user with an error if he's tried to apply
            two or more filters at once */
    if (getopt(argc, argv, filters) != -1)

    {
        printf("Only one filter allowed.\n");
        return 2;
    }

    // Further ensure proper usage
    if (argc != optind + 2)

    {
        printf("Usage: ./filter [flag] infile outfile\n");
        return 3;
    }

    // Store the value of the argument vectors in corresponding variables
    char *infile = argv[optind];
    char *outfile = argv[optind + 1];

    // Open the input file for reading
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)

    {
        printf("Could not open %s.\n", infile);
        return 4;
    }

    // Write the data into memory
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)

    {
        fclose(inptr);
        printf("Could not create %s.\n", outfile);
        return 5;
    }

    // Read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // Read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // Ensure infile is a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    
    {
        fclose(outptr);
        fclose(inptr);
        printf("Unsupported file format.\n");
        return 6;
    }

    // Store image' dimensions in corresponding variables
    int height = abs(bi.biHeight);
    int width = bi.biWidth;

    // See if there's memory to be allocated for the image
    RGBTRIPLE(*image)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    // Render an error if no such memory has been found
    if (image == NULL)

    {
        printf("Not enough memory to store image.\n");
        fclose(outptr);
        fclose(inptr);
        return 7;
    }

    // Determine padding for scanlines
    int padding = (4 - (width * sizeof(RGBTRIPLE)) % 4) % 4;

    // Iterate over infile's scanlines
    for (int i = 0; i < height; i++)
    
    {
        // Read row into a pixel array
        fread(image[i], sizeof(RGBTRIPLE), width, inptr);

        // Skip over padding
        fseek(inptr, padding, SEEK_CUR);
    }

    // Apply filters to the image
    switch (filter)
    
    {
        // Blur
        case 'b':
            blur(height, width, image);
            break;

        // Grayscale
        case 'g':
            grayscale(height, width, image);
            break;

        // Reflection
        case 'r':
            reflect(height, width, image);
            break;

        // Sepia
        case 's':
            sepia(height, width, image);
            break;
    }

    // Write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // Write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // Write new pixels to outfile
    for (int i = 0; i < height; i++)

    {
        // Write row to outfile
        fwrite(image[i], sizeof(RGBTRIPLE), width, outptr);

        // Write padding at end of row
        for (int k = 0; k < padding; k++)
 
        {
            fputc(0x00, outptr);
        }
    }

    // Make sure there are no memory leaks
    free(image);

    // Close the files
    fclose(inptr);
    fclose(outptr);
    return 0;
}