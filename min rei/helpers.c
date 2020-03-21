#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate down height
    for (int i = 0; i < height; i++)
    {
        // Iterate across width (edits pixel by pixel)
        for (int j = 0; j < width; j++)
        {
            float sum = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed);
            int avg = round(sum / 3);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Create sepia colours
            float sB = .131 * image[i][j].rgbtBlue + .534 * image[i][j].rgbtGreen + .272 * image[i][j].rgbtRed;
            float sG = .168 * image[i][j].rgbtBlue + .686 * image[i][j].rgbtGreen + .349 * image[i][j].rgbtRed;
            float sR = .189 * image[i][j].rgbtBlue + .769 * image[i][j].rgbtGreen + .393 * image[i][j].rgbtRed;

            int sepiaBlue = round(sB);
            int sepiaGreen = round(sG);
            int sepiaRed = round(sR);

            // Ensure < 255
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            // Set output RBG values
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Create temporary image placeholder
    RGBTRIPLE(*image_temp)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    // Write image_temp
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image_temp[i][j] = image[i][width - 1 - j];
        }
    }

    // Write image_temp onto image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = image_temp[i][j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create temporary image placeholder
    RGBTRIPLE(*image_temp)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    // Write image_temp
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Initialise variables
            float sumBlue = 0;
            float sumGreen = 0;
            float sumRed = 0;
            int counter = 0;

            // Iterate over 3x3 grid
            for (int x = i - 1; x < i + 2; x++)
            {
                for (int y = j - 1; y < j + 2; y++)
                {
                    // Condition met --> sum up colour values
                    if (x >= 0 && x < height && y >= 0 && y < width)
                    {
                        sumBlue += image[x][y].rgbtBlue;
                        sumGreen += image[x][y].rgbtGreen;
                        sumRed += image[x][y].rgbtRed;
                        counter++;
                    }
                }
            }

            // Write image temp
            image_temp[i][j].rgbtBlue = round(sumBlue / counter);
            image_temp[i][j].rgbtGreen = round(sumGreen / counter);
            image_temp[i][j].rgbtRed = round(sumRed / counter);
        }
    }

    // Write image_temp onto image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = image_temp[i][j];
        }
    }
    return;
}
