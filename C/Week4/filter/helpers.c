#include "helpers.h"
#include <math.h>

// Implement a function that converts images to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])

{
    // Prompt the user with the average RGB value
    int aver;

    // Loop throught image's height
    for (int i = 0; i < height; i++)

    {
        // Loop through image's width
        for (int j = 0; j < width; j++)

        {
            /* Initialize a triplet of variables each of which
            has the value of red, green and blue in image' 
                        pixels assigned to it */
            int r = image[i][j].rgbtRed;
            int g = image[i][j].rgbtGreen;
            int b = image[i][j].rgbtBlue;

            // Calculate and round the average pixel value
            aver = round(((float)r + (float)g + (float)b) / 3.0);

            // Image assumes grayscale hue
            image[i][j].rgbtRed = aver;
            image[i][j].rgbtGreen = aver;
            image[i][j].rgbtBlue = aver;
        }
    }

    // Exhibit a newly filtered image
    return;
}

// Implement a function that converts images to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])

{
    /* Declare variables representing color values in a given pixel,
    as well as the average amount of each color needed so as to have
                        a sepia filter working */
    int orRed, orGreen, orBlue;
    int sepiaRed, sepiaGreen, sepiaBlue;

    // Iterate over image's height
    for (int i = 0; i < height; i++)

    {
        // Iterate over image's width
        for (int j = 0; j < width; j++)

        {
            /* Initialize a triplet of variables each of which
            has the value of red, green and blue in image' 
                        pixels assigned to it */
            orRed = image[i][j].rgbtRed;
            orGreen = image[i][j].rgbtGreen;
            orBlue = image[i][j].rgbtBlue;

            // Calculate and round the average value needed to have a sepia effect
            sepiaRed = round(0.393 * orRed + 0.769 * orGreen + 0.189 * orBlue);

            /* If the the average value exceeds the 8 bit range,
                        make a pixel assume red color*/
            if (sepiaRed > 255)

            {
                image[i][j].rgbtRed = 255;
            }

            else

            {
                // Sepia out the red value of the pixel
                image[i][j].rgbtRed = sepiaRed;
            }

            // Calculate and round the average value needed to have a sepia effect
            sepiaGreen = round(0.349 * orRed + 0.686 * orGreen + 0.168 * orBlue);

            /* If the the average value exceeds the 8 bit range,
                        make a pixel assume green color*/
            if (sepiaGreen > 255)

            {
                image[i][j].rgbtGreen = 255;
            }

            else

            {
                // Sepia out the green value of the pixel
                image[i][j].rgbtGreen = sepiaGreen;
            }

            // Calculate and round the average value needed to have a sepia effect
            sepiaBlue = round(0.272 * orRed + 0.534 * orGreen + 0.131 * orBlue);

            /* If the the average value exceeds the 8 bit range,
                        make a pixel assume blue color*/
            if (sepiaBlue > 255)

            {
                image[i][j].rgbtBlue = 255;
            }

            else

            {
                // Sepia out the blue value of the pixel
                image[i][j].rgbtBlue = sepiaBlue;
            }
        }
    }

    // Exhibit a newly filtered image
    return;
}

// Implement a function that reflects images horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])

{
    // Iterate over image's height
    for (int i = 0; i < height; i++)

    {
        // Iterate over half the image's width
        for (int j = 0; j < (width / 2); j++)

        {
            /* Initialize a triplet of variables each of which
            has the value of red, green and blue in image' 
                        pixels assigned to it */
            int outRed = image[i][j].rgbtRed;
            int outGreen = image[i][j].rgbtGreen;
            int outBlue = image[i][j].rgbtBlue;

            // Prompt with the desired outlook of the image
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;

            // Transpose the image horizontally
            image[i][width - j - 1].rgbtRed = outRed;
            image[i][width - j - 1].rgbtGreen = outGreen;
            image[i][width - j - 1].rgbtBlue = outBlue;
        }
    }

    // Exhibit a newly created image
    return;
}

// Implement a function that blurs images
void blur(int height, int width, RGBTRIPLE image[height][width])

{
    // Declare a 'blur' variable
    RGBTRIPLE out[height][width];

    // Iterate over image's height
    for (int i = 0; i < height; i++)

    {
        // Iterate over image's width
        for (int j = 0; j < height; j++)

        {
            /* Declare variables representing color values in a given pixel,
                also initializing an initial value of each pixel' blur */
            int blurRed, blurGreen, blurBlue;
            blurRed = blurGreen = blurBlue = 0;

            // Prompt users with a floating value of the neighboring pixels
            float counter = 0.00;

            // Describe the 'boxing' of a given pixel 
            for (int x = -1; x <= 1; x++)

            {
                for (int y = -1; y <= 1; y++)

                {
                    // Initialize variables describing the 'boxing'
                    int xboxed = i + x;
                    int yboxed = j + y;

                    // Make sure a given pixel can be 'boxed'
                    if (xboxed < 0 || yboxed < 0 || xboxed > (height - 1) || yboxed > (width - 1))

                    {
                        continue;
                    }

                    /* Increment blurred image' corresponding
                                color values */
                    blurRed += image[xboxed][yboxed].rgbtRed;
                    blurGreen += image[xboxed][yboxed].rgbtGreen;
                    blurBlue += image[xboxed][yboxed].rgbtBlue;

                    counter++;
                }

                // Round the neighboring colour values
                out[i][j].rgbtRed = round(blurRed / counter);
                out[i][j].rgbtGreen = round(blurGreen / counter);
                out[i][j].rgbtBlue = round(blurBlue / counter);
            }
        }
    }

    // Set each colour value to that of the average
    for (int i = 0; i < height; i++)

    {
        for (int j = 0; j < width; j++)

        {
            image[i][j].rgbtRed = out[i][j].rgbtRed;
            image[i][j].rgbtGreen = out[i][j].rgbtGreen;
            image[i][j].rgbtBlue = out[i][j].rgbtBlue;
        }
    }

    // Exhibit a newly created image
    return;
}