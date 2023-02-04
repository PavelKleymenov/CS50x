#include "bmp.h"

// Implements a function that converts  the image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]);

// Implements a function that converts the image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width]);

// Implements a function that reflects the image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]);

// Implements a function that blurs the image
void blur(int height, int width, RGBTRIPLE image[height][width]);