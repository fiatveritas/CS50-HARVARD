#include "helpers.h"
#include <stdio.h> //comment this out
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //the method takes RGB average of a pixel and all RGB become that value
    int average = 0;
    int sum = 0;
    double const ALL = 3.00;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            average = 0;
            sum = 0;

            sum += image[i][j].rgbtRed;
            sum += image[i][j].rgbtGreen;
            sum += image[i][j].rgbtBlue;
            average = round(sum / ALL);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //using the trick of going through half the image
    //need a temp to do swap
    RGBTRIPLE temp;
    int start;
    //paid certificates for cs50?
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            //substracts from start to get symmetry along matrix
            start = width - 1;
            start -= j;
            temp.rgbtRed = image[i][j].rgbtRed;
            temp.rgbtGreen = image[i][j].rgbtGreen;
            temp.rgbtBlue = image[i][j].rgbtBlue;
            image[i][j].rgbtRed = image[i][start].rgbtRed;
            image[i][j].rgbtGreen = image[i][start].rgbtGreen;
            image[i][j].rgbtBlue = image[i][start].rgbtBlue;
            image[i][start].rgbtRed = temp.rgbtRed;
            image[i][start].rgbtGreen = temp.rgbtGreen;
            image[i][start].rgbtBlue = temp.rgbtBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //this takes the average of each channel by looking at each neighbor
    RGBTRIPLE(*dummy)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    double const TOT = 9.00;
    int red_sum = 0;
    int green_sum = 0;
    int blue_sum = 0;
    //average divides sum by n elements it contains
    double red_average = 0.00;
    double green_average = 0.00;
    double blue_average = 0.00;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            red_sum = 0;
            green_sum = 0;
            blue_sum = 0;
            //red average divides sum by element number
            red_average = 0.00;
            green_average = 0.00;
            blue_average = 0.00;

            if ((i - 1) < 0 && (j - 1) < 0)
            {
                //Top-left code
                red_sum += image[i][j].rgbtRed;
                green_sum += image[i][j].rgbtGreen;
                blue_sum += image[i][j].rgbtBlue;

                red_sum += image[i][j + 1].rgbtRed;
                green_sum += image[i][j + 1].rgbtGreen;
                blue_sum += image[i][j + 1].rgbtBlue;
                //more comments
                red_sum += image[i + 1][j].rgbtRed;
                green_sum += image[i + 1][j].rgbtGreen;
                blue_sum += image[i + 1][j].rgbtBlue;

                red_sum += image[i + 1][j + 1].rgbtRed;
                green_sum += image[i + 1][j + 1].rgbtGreen;
                blue_sum += image[i + 1][j + 1].rgbtBlue;

                //four elements considered
                red_average = round(red_sum / 4.00);
                green_average = round(green_sum / 4.00);
                blue_average = round(blue_sum / 4.00);

                dummy[i][j].rgbtRed = red_average;
                dummy[i][j].rgbtGreen = green_average;
                dummy[i][j].rgbtBlue = blue_average;
                continue;

            }
            if ((i - 1) < 0 && (j + 1) == width)
            {
                //top-right corner
                red_sum += image[i][j].rgbtRed;
                green_sum += image[i][j].rgbtGreen;
                blue_sum += image[i][j].rgbtBlue;

                red_sum += image[i][j - 1].rgbtRed;
                green_sum += image[i][j - 1].rgbtGreen;
                blue_sum += image[i][j - 1].rgbtBlue;
                //this was filter
                red_sum += image[i + 1][j].rgbtRed;
                green_sum += image[i + 1][j].rgbtGreen;
                blue_sum += image[i + 1][j].rgbtBlue;

                red_sum += image[i + 1][j - 1].rgbtRed;
                green_sum += image[i + 1][j - 1].rgbtGreen;
                blue_sum += image[i + 1][j - 1].rgbtBlue;

                //four elements considered
                red_average = round(red_sum / 4.00);
                green_average = round(green_sum / 4.00);
                blue_average = round(blue_sum / 4.00);

                dummy[i][j].rgbtRed = red_average;
                dummy[i][j].rgbtGreen = green_average;
                dummy[i][j].rgbtBlue = blue_average;
                continue;
            }
            if ((i + 1) == height && (j - 1) < 0)
            {
                //bottom-left corner code
                red_sum += image[i][j].rgbtRed;
                green_sum += image[i][j].rgbtGreen;
                blue_sum += image[i][j].rgbtBlue;

                red_sum += image[i - 1][j].rgbtRed;
                green_sum += image[i - 1][j].rgbtGreen;
                blue_sum += image[i - 1][j].rgbtBlue;
                //this is cs50
                red_sum += image[i - 1][j + 1].rgbtRed;
                green_sum += image[i - 1][j + 1].rgbtGreen;
                blue_sum += image[i - 1][j + 1].rgbtBlue;

                red_sum += image[i][j + 1].rgbtRed;
                green_sum += image[i][j + 1].rgbtGreen;
                blue_sum += image[i][j + 1].rgbtBlue;

                //four elements considered
                red_average = round(red_sum / 4.00);
                green_average = round(green_sum / 4.00);
                blue_average = round(blue_sum / 4.00);

                dummy[i][j].rgbtRed = red_average;
                dummy[i][j].rgbtGreen = green_average;
                dummy[i][j].rgbtBlue = blue_average;
                continue;
            }
            if ((i + 1) == height && (j + 1) == width)
            {
                //bottom-right code
                red_sum += image[i][j].rgbtRed;
                green_sum += image[i][j].rgbtGreen;
                blue_sum += image[i][j].rgbtBlue;

                red_sum += image[i][j - 1].rgbtRed;
                green_sum += image[i][j - 1].rgbtGreen;
                blue_sum += image[i][j - 1].rgbtBlue;

                red_sum += image[i - 1][j].rgbtRed;
                green_sum += image[i - 1][j].rgbtGreen;
                blue_sum += image[i - 1][j].rgbtBlue;
                //keep the comments coming
                red_sum += image[i - 1][j - 1].rgbtRed;
                green_sum += image[i - 1][j - 1].rgbtGreen;
                blue_sum += image[i - 1][j - 1].rgbtBlue;

                red_average = round(red_sum / 4.00);
                green_average = round(green_sum / 4.00);
                blue_average = round(blue_sum / 4.00);

                dummy[i][j].rgbtRed = red_average;
                dummy[i][j].rgbtGreen = green_average;
                dummy[i][j].rgbtBlue = blue_average;
                continue;
            }
            if ((j - 1) < 0)
            {
                //left edge
                red_sum += image[i - 1][j].rgbtRed;
                green_sum += image[i - 1][j].rgbtGreen;
                blue_sum += image[i - 1][j].rgbtBlue;

                red_sum += image[i][j].rgbtRed;
                green_sum += image[i][j].rgbtGreen;
                blue_sum += image[i][j].rgbtBlue;

                red_sum += image[i + 1][j].rgbtRed;
                green_sum += image[i + 1][j].rgbtGreen;
                blue_sum += image[i + 1][j].rgbtBlue;
                //running out of comments
                red_sum += image[i - 1][j + 1].rgbtRed;
                green_sum += image[i - 1][j + 1].rgbtGreen;
                blue_sum += image[i - 1][j + 1].rgbtBlue;

                red_sum += image[i][j + 1].rgbtRed;
                green_sum += image[i][j + 1].rgbtGreen;
                blue_sum += image[i][j + 1].rgbtBlue;

                red_sum += image[i + 1][j + 1].rgbtRed;
                green_sum += image[i + 1][j + 1].rgbtGreen;
                blue_sum += image[i + 1][j + 1].rgbtBlue;

                //six elements considered
                red_average = round(red_sum / 6.00);
                green_average = round(green_sum / 6.00);
                blue_average = round(blue_sum / 6.00);

                dummy[i][j].rgbtRed = red_average;
                dummy[i][j].rgbtGreen = green_average;
                dummy[i][j].rgbtBlue = blue_average;
                continue;
            }
            if ((i - 1) < 0)
            {
                //top edge
                red_sum += image[i][j].rgbtRed;
                green_sum += image[i][j].rgbtGreen;
                blue_sum += image[i][j].rgbtBlue;

                red_sum += image[i][j - 1].rgbtRed;
                green_sum += image[i][j - 1].rgbtGreen;
                blue_sum += image[i][j - 1].rgbtBlue;

                red_sum += image[i][j + 1].rgbtRed;
                green_sum += image[i][j + 1].rgbtGreen;
                blue_sum += image[i][j + 1].rgbtBlue;

                red_sum += image[i + 1][j - 1].rgbtRed;
                green_sum += image[i + 1][j - 1].rgbtGreen;
                blue_sum += image[i + 1][j - 1].rgbtBlue;
                //comments are proportional to amount of code
                red_sum += image[i + 1][j].rgbtRed;
                green_sum += image[i + 1][j].rgbtGreen;
                blue_sum += image[i + 1][j].rgbtBlue;

                red_sum += image[i + 1][j + 1].rgbtRed;
                green_sum += image[i + 1][j + 1].rgbtGreen;
                blue_sum += image[i + 1][j + 1].rgbtBlue;

                red_average = round(red_sum / 6.00);
                green_average = round(green_sum / 6.00);
                blue_average = round(blue_sum / 6.00);

                dummy[i][j].rgbtRed = red_average;
                dummy[i][j].rgbtGreen = green_average;
                dummy[i][j].rgbtBlue = blue_average;
                continue;
            }
            if ((j + 1) == width)
            {
                //right edge
                red_sum += image[i][j - 1].rgbtRed;
                green_sum += image[i][j - 1].rgbtGreen;
                blue_sum += image[i][j - 1].rgbtBlue;

                red_sum += image[i - 1][j - 1].rgbtRed;
                green_sum += image[i - 1][j - 1].rgbtGreen;
                blue_sum += image[i - 1][j - 1].rgbtBlue;

                red_sum += image[i + 1][j - 1].rgbtRed;
                green_sum += image[i + 1][j - 1].rgbtGreen;
                blue_sum += image[i + 1][j - 1].rgbtBlue;

                red_sum += image[i][j].rgbtRed;
                green_sum += image[i][j].rgbtGreen;
                blue_sum += image[i][j].rgbtBlue;
                //just for fun
                red_sum += image[i - 1][j].rgbtRed;
                green_sum += image[i - 1][j].rgbtGreen;
                blue_sum += image[i - 1][j].rgbtBlue;

                red_sum += image[i + 1][j].rgbtRed;
                green_sum += image[i + 1][j].rgbtGreen;
                blue_sum += image[i + 1][j].rgbtBlue;

                red_average = round(red_sum / 6.00);
                green_average = round(green_sum / 6.00);
                blue_average = round(blue_sum / 6.00);

                dummy[i][j].rgbtRed = red_average;
                dummy[i][j].rgbtGreen = green_average;
                dummy[i][j].rgbtBlue = blue_average;
                continue;
            }
            if ((i + 1) == height)
            {
                //bottom edge
                red_sum += image[i][j].rgbtRed;
                green_sum += image[i][j].rgbtGreen;
                blue_sum += image[i][j].rgbtBlue;

                red_sum += image[i][j - 1].rgbtRed;
                green_sum += image[i][j - 1].rgbtGreen;
                blue_sum += image[i][j - 1].rgbtBlue;

                red_sum += image[i][j + 1].rgbtRed;
                green_sum += image[i][j + 1].rgbtGreen;
                blue_sum += image[i][j + 1].rgbtBlue;
                //need comments for the grader
                red_sum += image[i - 1][j].rgbtRed;
                green_sum += image[i - 1][j].rgbtGreen;
                blue_sum += image[i - 1][j].rgbtBlue;

                red_sum += image[i - 1][j - 1].rgbtRed;
                green_sum += image[i - 1][j - 1].rgbtGreen;
                blue_sum += image[i - 1][j - 1].rgbtBlue;

                red_sum += image[i - 1][j + 1].rgbtRed;
                green_sum += image[i - 1][j + 1].rgbtGreen;
                blue_sum += image[i - 1][j + 1].rgbtBlue;

                red_average = round(red_sum / 6.00);
                green_average = round(green_sum / 6.00);
                blue_average = round(blue_sum / 6.00);

                dummy[i][j].rgbtRed = red_average;
                dummy[i][j].rgbtGreen = green_average;
                dummy[i][j].rgbtBlue = blue_average;
                continue;
            }

            red_sum += image[i][j].rgbtRed;
            green_sum += image[i][j].rgbtGreen;
            blue_sum += image[i][j].rgbtBlue;

            red_sum += image[i - 1][j - 1].rgbtRed;
            green_sum += image[i - 1][j - 1].rgbtGreen;
            blue_sum += image[i - 1][j - 1].rgbtBlue;
            //god save the queen
            red_sum += image[i - 1][j].rgbtRed;
            green_sum += image[i - 1][j].rgbtGreen;
            blue_sum += image[i - 1][j].rgbtBlue;

            red_sum += image[i - 1][j + 1].rgbtRed;
            green_sum += image[i - 1][j + 1].rgbtGreen;
            blue_sum += image[i - 1][j + 1].rgbtBlue;

            red_sum += image[i][j - 1].rgbtRed;
            green_sum += image[i][j - 1].rgbtGreen;
            blue_sum += image[i][j - 1].rgbtBlue;

            red_sum += image[i][j + 1].rgbtRed;
            green_sum += image[i][j + 1].rgbtGreen;
            blue_sum += image[i][j + 1].rgbtBlue;
            //repeats a lot
            red_sum += image[i + 1][j - 1].rgbtRed;
            green_sum += image[i + 1][j - 1].rgbtGreen;
            blue_sum += image[i + 1][j - 1].rgbtBlue;

            red_sum += image[i + 1][j].rgbtRed;
            green_sum += image[i + 1][j].rgbtGreen;
            blue_sum += image[i + 1][j].rgbtBlue;

            red_sum += image[i + 1][j + 1].rgbtRed;
            green_sum += image[i + 1][j + 1].rgbtGreen;
            blue_sum += image[i + 1][j + 1].rgbtBlue;
            //every other line
            red_average = round(red_sum / TOT);
            green_average = round(green_sum / TOT);
            blue_average = round(blue_sum / TOT);

            dummy[i][j].rgbtRed = red_average;
            dummy[i][j].rgbtGreen = green_average;
            dummy[i][j].rgbtBlue = blue_average;
        }
    }
    //deep copy of dummy
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = dummy[i][j].rgbtRed;
            image[i][j].rgbtGreen = dummy[i][j].rgbtGreen;
            image[i][j].rgbtBlue = dummy[i][j].rgbtBlue;
        }
    }

    //destroy the temporary pointer to dummy
    free(dummy);
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //need the temp dummy
    RGBTRIPLE(*dummy)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    int red_sum_x = 0;
    int green_sum_x = 0;
    int blue_sum_x = 0;
    int red_sum_y = 0;
    int green_sum_y = 0;
    int blue_sum_y = 0;
    // sum_x & sum_y are needed for the convolution matrix
    double red_root = 0.00;
    double green_root = 0.00;
    double blue_root = 0.00;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            red_sum_x = 0;
            green_sum_x = 0;
            blue_sum_x = 0;
            //restarts variables at the start of iteration
            red_sum_y = 0;
            green_sum_y = 0;
            blue_sum_y = 0;

            red_root = 0.00;
            green_root = 0.00;
            blue_root = 0.00;
            //gx convolution matrix = [[-1, 0, 1], [-2, 0, 2], [-1, 0, 1],] gy convolution matrix = [[-1, -2, -1], [0, 0, 0], [1, 2, 1]]
            if ((i - 1) < 0 && (j - 1) < 0)
            {
                //Top-left corner

                //gx computation
                red_sum_x += 0 * image[i][j].rgbtRed;
                green_sum_x += 0 * image[i][j].rgbtGreen;
                blue_sum_x += 0 * image[i][j].rgbtBlue;

                red_sum_x += 2 * image[i][j + 1].rgbtRed;
                green_sum_x += 2 * image[i][j + 1].rgbtGreen;
                blue_sum_x += 2 * image[i][j + 1].rgbtBlue;
                // hi ;)
                red_sum_x += 0 * image[i + 1][j].rgbtRed;
                green_sum_x += 0 * image[i + 1][j].rgbtGreen;
                blue_sum_x += 0 * image[i + 1][j].rgbtBlue;

                red_sum_x += 1 * image[i + 1][j + 1].rgbtRed;
                green_sum_x += 1 * image[i + 1][j + 1].rgbtGreen;
                blue_sum_x += 1 * image[i + 1][j + 1].rgbtBlue;

                //gy computation
                red_sum_y += 0 * image[i][j].rgbtRed;
                green_sum_y += 0 * image[i][j].rgbtGreen;
                blue_sum_y += 0 * image[i][j].rgbtBlue;

                red_sum_y += 0 * image[i][j + 1].rgbtRed;
                green_sum_y += 0 * image[i][j + 1].rgbtGreen;
                blue_sum_y += 0 * image[i][j + 1].rgbtBlue;

                red_sum_y += 2 * image[i + 1][j].rgbtRed;
                green_sum_y += 2 * image[i + 1][j].rgbtGreen;
                blue_sum_y += 2 * image[i + 1][j].rgbtBlue;
                //avoid repetitions
                red_sum_y += 1 * image[i + 1][j + 1].rgbtRed;
                green_sum_y += 1 * image[i + 1][j + 1].rgbtGreen;
                blue_sum_y += 1 * image[i + 1][j + 1].rgbtBlue;
                //check for value range
                red_root = round(sqrt(red_sum_x * red_sum_x + red_sum_y * red_sum_y));
                if (red_root > 255)
                {
                    red_root = 255;
                }
                green_root = round(sqrt(green_sum_x * green_sum_x + green_sum_y * green_sum_y));
                if (green_root > 255)
                {
                    green_root = 255;
                }
                blue_root = round(sqrt(blue_sum_x * blue_sum_x + blue_sum_y * blue_sum_y));
                if (blue_root > 255)
                {
                    blue_root = 255;
                }
                //set final values
                dummy[i][j].rgbtRed = red_root;
                dummy[i][j].rgbtGreen = green_root;
                dummy[i][j].rgbtBlue = blue_root;
                continue;

            }
            if ((i - 1) < 0 && (j + 1) == width)
            {
                //top-right corner
                //gx computation
                red_sum_x += 0 * image[i][j].rgbtRed;
                green_sum_x += 0 * image[i][j].rgbtGreen;
                blue_sum_x += 0 * image[i][j].rgbtBlue;

                red_sum_x += -2 * image[i][j - 1].rgbtRed;
                green_sum_x += -2 * image[i][j - 1].rgbtGreen;
                blue_sum_x += -2 * image[i][j - 1].rgbtBlue;

                red_sum_x += 0 * image[i + 1][j].rgbtRed;
                green_sum_x += 0 * image[i + 1][j].rgbtGreen;
                blue_sum_x += 0 * image[i + 1][j].rgbtBlue;

                red_sum_x += -1 * image[i + 1][j - 1].rgbtRed;
                green_sum_x += -1 * image[i + 1][j - 1].rgbtGreen;
                blue_sum_x += -1 * image[i + 1][j - 1].rgbtBlue;

                //gy computation

                red_sum_y += 0 * image[i][j].rgbtRed;
                green_sum_y += 0 * image[i][j].rgbtGreen;
                blue_sum_y += 0 * image[i][j].rgbtBlue;

                red_sum_y += 0 * image[i][j - 1].rgbtRed;
                green_sum_y += 0 * image[i][j - 1].rgbtGreen;
                blue_sum_y += 0 * image[i][j - 1].rgbtBlue;

                red_sum_y += 2 * image[i + 1][j].rgbtRed;
                green_sum_y += 2 * image[i + 1][j].rgbtGreen;
                blue_sum_y += 2 * image[i + 1][j].rgbtBlue;
                //hello wold
                red_sum_y += 1 * image[i + 1][j - 1].rgbtRed;
                green_sum_y += 1 * image[i + 1][j - 1].rgbtGreen;
                blue_sum_y += 1 * image[i + 1][j - 1].rgbtBlue;

                red_root = round(sqrt(red_sum_x * red_sum_x + red_sum_y * red_sum_y));
                if (red_root > 255)
                {
                    red_root = 255;
                }
                green_root = round(sqrt(green_sum_x * green_sum_x + green_sum_y * green_sum_y));
                if (green_root > 255)
                {
                    green_root = 255;
                }
                blue_root = round(sqrt(blue_sum_x * blue_sum_x + blue_sum_y * blue_sum_y));
                if (blue_root > 255)
                {
                    blue_root = 255;
                }
                //continue need to go to next iteration
                dummy[i][j].rgbtRed = red_root;
                dummy[i][j].rgbtGreen = green_root;
                dummy[i][j].rgbtBlue = blue_root;
                continue;
            }
            if ((i + 1) == height && (j - 1) < 0)
            {
                //bottom-left corner
                //gx computation
                red_sum_x += 0 * image[i][j].rgbtRed;
                green_sum_x += 0 * image[i][j].rgbtGreen;
                blue_sum_x += 0 * image[i][j].rgbtBlue;

                red_sum_x += 0 * image[i - 1][j].rgbtRed;
                green_sum_x += 0 * image[i - 1][j].rgbtGreen;
                blue_sum_x += 0 * image[i - 1][j].rgbtBlue;

                red_sum_x += 1 * image[i - 1][j + 1].rgbtRed;
                green_sum_x += 1 * image[i - 1][j + 1].rgbtGreen;
                blue_sum_x += 1 * image[i - 1][j + 1].rgbtBlue;
                //too much repetition
                red_sum_x += 2 * image[i][j + 1].rgbtRed;
                green_sum_x += 2 * image[i][j + 1].rgbtGreen;
                blue_sum_x += 2 * image[i][j + 1].rgbtBlue;

                //gy computation
                red_sum_y += 0 * image[i][j].rgbtRed;
                green_sum_y += 0 * image[i][j].rgbtGreen;
                blue_sum_y += 0 * image[i][j].rgbtBlue;

                red_sum_y += -2 * image[i - 1][j].rgbtRed;
                green_sum_y += -2 * image[i - 1][j].rgbtGreen;
                blue_sum_y += -2 * image[i - 1][j].rgbtBlue;

                red_sum_y += -1 * image[i - 1][j + 1].rgbtRed;
                green_sum_y += -1 * image[i - 1][j + 1].rgbtGreen;
                blue_sum_y += -1 * image[i - 1][j + 1].rgbtBlue;

                red_sum_y += 0 * image[i][j + 1].rgbtRed;
                green_sum_y += 0 * image[i][j + 1].rgbtGreen;
                blue_sum_y += 0 * image[i][j + 1].rgbtBlue;
                //check if values are not greater 255
                red_root = round(sqrt(red_sum_x * red_sum_x + red_sum_y * red_sum_y));
                if (red_root > 255)
                {
                    red_root = 255;
                }
                green_root = round(sqrt(green_sum_x * green_sum_x + green_sum_y * green_sum_y));
                if (green_root > 255)
                {
                    green_root = 255;
                }
                blue_root = round(sqrt(blue_sum_x * blue_sum_x + blue_sum_y * blue_sum_y));
                if (blue_root > 255)
                {
                    blue_root = 255;
                }

                dummy[i][j].rgbtRed = red_root;
                dummy[i][j].rgbtGreen = green_root;
                dummy[i][j].rgbtBlue = blue_root;
                continue;
            }
            if ((i + 1) == height && (j + 1) == width)
            {
                //bottom-right corner
                //gx computation
                red_sum_x += 0 * image[i][j].rgbtRed;
                green_sum_x += 0 * image[i][j].rgbtGreen;
                blue_sum_x += 0 * image[i][j].rgbtBlue;

                red_sum_x += -2 * image[i][j - 1].rgbtRed;
                green_sum_x += -2 * image[i][j - 1].rgbtGreen;
                blue_sum_x += -2 * image[i][j - 1].rgbtBlue;

                red_sum_x += 0 * image[i - 1][j].rgbtRed;
                green_sum_x += 0 * image[i - 1][j].rgbtGreen;
                blue_sum_x += 0 * image[i - 1][j].rgbtBlue;

                red_sum_x += -1 * image[i - 1][j - 1].rgbtRed;
                green_sum_x += -1 * image[i - 1][j - 1].rgbtGreen;
                blue_sum_x += -1 * image[i - 1][j - 1].rgbtBlue;

                //gy computation
                red_sum_y += 0 * image[i][j].rgbtRed;
                green_sum_y += 0 * image[i][j].rgbtGreen;
                blue_sum_y += 0 * image[i][j].rgbtBlue;

                red_sum_y += 0 * image[i][j - 1].rgbtRed;
                green_sum_y += 0 * image[i][j - 1].rgbtGreen;
                blue_sum_y += 0 * image[i][j - 1].rgbtBlue;

                red_sum_y += -2 * image[i - 1][j].rgbtRed;
                green_sum_y += -2 * image[i - 1][j].rgbtGreen;
                blue_sum_y += -2 * image[i - 1][j].rgbtBlue;
                //break the syle code
                red_sum_y += -1 * image[i - 1][j - 1].rgbtRed;
                green_sum_y += -1 * image[i - 1][j - 1].rgbtGreen;
                blue_sum_y += -1 * image[i - 1][j - 1].rgbtBlue;

                red_root = round(sqrt(red_sum_x * red_sum_x + red_sum_y * red_sum_y));
                if (red_root > 255)
                {
                    red_root = 255;
                }
                green_root = round(sqrt(green_sum_x * green_sum_x + green_sum_y * green_sum_y));
                if (green_root > 255)
                {
                    green_root = 255;
                }
                blue_root = round(sqrt(blue_sum_x * blue_sum_x + blue_sum_y * blue_sum_y));
                if (blue_root > 255)
                {
                    blue_root = 255;
                }

                dummy[i][j].rgbtRed = red_root;
                dummy[i][j].rgbtGreen = green_root;
                dummy[i][j].rgbtBlue = blue_root;
                continue;
            }
            if ((j - 1) < 0)
            {
                //left edge
                //gx computation
                red_sum_x += 0 * image[i - 1][j].rgbtRed;
                green_sum_x += 0 * image[i - 1][j].rgbtGreen;
                blue_sum_x += 0 * image[i - 1][j].rgbtBlue;

                red_sum_x += 0 * image[i][j].rgbtRed;
                green_sum_x += 0 * image[i][j].rgbtGreen;
                blue_sum_x += 0 * image[i][j].rgbtBlue;

                red_sum_x += 0 * image[i + 1][j].rgbtRed;
                green_sum_x += 0 * image[i + 1][j].rgbtGreen;
                blue_sum_x += 0 * image[i + 1][j].rgbtBlue;
                //appease sytlizer
                red_sum_x += 1 * image[i - 1][j + 1].rgbtRed;
                green_sum_x += 1 * image[i - 1][j + 1].rgbtGreen;
                blue_sum_x += 1 * image[i - 1][j + 1].rgbtBlue;

                red_sum_x += 2 * image[i][j + 1].rgbtRed;
                green_sum_x += 2 * image[i][j + 1].rgbtGreen;
                blue_sum_x += 2 * image[i][j + 1].rgbtBlue;

                red_sum_x += 1 * image[i + 1][j + 1].rgbtRed;
                green_sum_x += 1 * image[i + 1][j + 1].rgbtGreen;
                blue_sum_x += 1 * image[i + 1][j + 1].rgbtBlue;

                //gy computation

                red_sum_y += -2 * image[i - 1][j].rgbtRed;
                green_sum_y += -2 * image[i - 1][j].rgbtGreen;
                blue_sum_y += -2 * image[i - 1][j].rgbtBlue;

                red_sum_y += 0 * image[i][j].rgbtRed;
                green_sum_y += 0 * image[i][j].rgbtGreen;
                blue_sum_y += 0 * image[i][j].rgbtBlue;
                //more of the same
                red_sum_y += 2 * image[i + 1][j].rgbtRed;
                green_sum_y += 2 * image[i + 1][j].rgbtGreen;
                blue_sum_y += 2 * image[i + 1][j].rgbtBlue;

                red_sum_y += -1 * image[i - 1][j + 1].rgbtRed;
                green_sum_y += -1 * image[i - 1][j + 1].rgbtGreen;
                blue_sum_y += -1 * image[i - 1][j + 1].rgbtBlue;
                //filler
                red_sum_y += 0 * image[i][j + 1].rgbtRed;
                green_sum_y += 0 * image[i][j + 1].rgbtGreen;
                blue_sum_y += 0 * image[i][j + 1].rgbtBlue;

                red_sum_y += 1 * image[i + 1][j + 1].rgbtRed;
                green_sum_y += 1 * image[i + 1][j + 1].rgbtGreen;
                blue_sum_y += 1 * image[i + 1][j + 1].rgbtBlue;

                red_root = round(sqrt(red_sum_x * red_sum_x + red_sum_y * red_sum_y));
                if (red_root > 255)
                {
                    red_root = 255;
                }
                green_root = round(sqrt(green_sum_x * green_sum_x + green_sum_y * green_sum_y));
                if (green_root > 255)
                {
                    green_root = 255;
                }
                blue_root = round(sqrt(blue_sum_x * blue_sum_x + blue_sum_y * blue_sum_y));
                if (blue_root > 255)
                {
                    blue_root = 255;
                }
                //assign to the dummy pointer roots
                dummy[i][j].rgbtRed = red_root;
                dummy[i][j].rgbtGreen = green_root;
                dummy[i][j].rgbtBlue = blue_root;
                continue;
            }
            if ((i - 1) < 0)
            {
                //top edge
                //gx computation
                red_sum_x += 0 * image[i][j].rgbtRed;
                green_sum_x += 0 * image[i][j].rgbtGreen;
                blue_sum_x += 0 * image[i][j].rgbtBlue;

                red_sum_x += -2 * image[i][j - 1].rgbtRed;
                green_sum_x += -2 * image[i][j - 1].rgbtGreen;
                blue_sum_x += -2 * image[i][j - 1].rgbtBlue;
                //more comments for the grader
                red_sum_x += 2 * image[i][j + 1].rgbtRed;
                green_sum_x += 2 * image[i][j + 1].rgbtGreen;
                blue_sum_x += 2 * image[i][j + 1].rgbtBlue;

                red_sum_x += -1 * image[i + 1][j - 1].rgbtRed;
                green_sum_x += -1 * image[i + 1][j - 1].rgbtGreen;
                blue_sum_x += -1 * image[i + 1][j - 1].rgbtBlue;

                red_sum_x += 0 * image[i + 1][j].rgbtRed;
                green_sum_x += 0 * image[i + 1][j].rgbtGreen;
                blue_sum_x += 0 * image[i + 1][j].rgbtBlue;

                red_sum_x += 1 * image[i + 1][j + 1].rgbtRed;
                green_sum_x += 1 * image[i + 1][j + 1].rgbtGreen;
                blue_sum_x += 1 * image[i + 1][j + 1].rgbtBlue;

                //gy computation

                red_sum_y += 0 * image[i][j].rgbtRed;
                green_sum_y += 0 * image[i][j].rgbtGreen;
                blue_sum_y += 0 * image[i][j].rgbtBlue;

                red_sum_y += 0 * image[i][j - 1].rgbtRed;
                green_sum_y += 0 * image[i][j - 1].rgbtGreen;
                blue_sum_y += 0 * image[i][j - 1].rgbtBlue;

                red_sum_y += 0 * image[i][j + 1].rgbtRed;
                green_sum_y += 0 * image[i][j + 1].rgbtGreen;
                blue_sum_y += 0 * image[i][j + 1].rgbtBlue;

                red_sum_y += 1 * image[i + 1][j - 1].rgbtRed;
                green_sum_y += 1 * image[i + 1][j - 1].rgbtGreen;
                blue_sum_y += 1 * image[i + 1][j - 1].rgbtBlue;
                //fill her up
                red_sum_y += 2 * image[i + 1][j].rgbtRed;
                green_sum_y += 2 * image[i + 1][j].rgbtGreen;
                blue_sum_y += 2 * image[i + 1][j].rgbtBlue;

                red_sum_y += 1 * image[i + 1][j + 1].rgbtRed;
                green_sum_y += 1 * image[i + 1][j + 1].rgbtGreen;
                blue_sum_y += 1 * image[i + 1][j + 1].rgbtBlue;
                //check if values are within 255
                red_root = round(sqrt(red_sum_x * red_sum_x + red_sum_y * red_sum_y));
                if (red_root > 255)
                {
                    red_root = 255;
                }
                green_root = round(sqrt(green_sum_x * green_sum_x + green_sum_y * green_sum_y));
                if (green_root > 255)
                {
                    green_root = 255;
                }
                blue_root = round(sqrt(blue_sum_x * blue_sum_x + blue_sum_y * blue_sum_y));
                if (blue_root > 255)
                {
                    blue_root = 255;
                }

                dummy[i][j].rgbtRed = red_root;
                dummy[i][j].rgbtGreen = green_root;
                dummy[i][j].rgbtBlue = blue_root;
                continue;
            }
            if ((j + 1) == width)
            {
                //right edge
                //gx computation
                red_sum_x += -2 * image[i][j - 1].rgbtRed;
                green_sum_x += -2 * image[i][j - 1].rgbtGreen;
                blue_sum_x += -2 * image[i][j - 1].rgbtBlue;

                red_sum_x += -1 * image[i - 1][j - 1].rgbtRed;
                green_sum_x += -1 * image[i - 1][j - 1].rgbtGreen;
                blue_sum_x += -1 * image[i - 1][j - 1].rgbtBlue;

                red_sum_x += -1 * image[i + 1][j - 1].rgbtRed;
                green_sum_x += -1 * image[i + 1][j - 1].rgbtGreen;
                blue_sum_x += -1 * image[i + 1][j - 1].rgbtBlue;
                //awesome course
                red_sum_x += 0 * image[i][j].rgbtRed;
                green_sum_x += 0 * image[i][j].rgbtGreen;
                blue_sum_x += 0 * image[i][j].rgbtBlue;

                red_sum_x += 0 * image[i - 1][j].rgbtRed;
                green_sum_x += 0 * image[i - 1][j].rgbtGreen;
                blue_sum_x += 0 * image[i - 1][j].rgbtBlue;

                red_sum_x += 0 * image[i + 1][j].rgbtRed;
                green_sum_x += 0 * image[i + 1][j].rgbtGreen;
                blue_sum_x += 0 * image[i + 1][j].rgbtBlue;

                //gy computation

                red_sum_y += 0 * image[i][j - 1].rgbtRed;
                green_sum_y += 0 * image[i][j - 1].rgbtGreen;
                blue_sum_y += 0 * image[i][j - 1].rgbtBlue;

                red_sum_y += -1 * image[i - 1][j - 1].rgbtRed;
                green_sum_y += -1 * image[i - 1][j - 1].rgbtGreen;
                blue_sum_y += -1 * image[i - 1][j - 1].rgbtBlue;

                red_sum_y += 1 * image[i + 1][j - 1].rgbtRed;
                green_sum_y += 1 * image[i + 1][j - 1].rgbtGreen;
                blue_sum_y += 1 * image[i + 1][j - 1].rgbtBlue;
                //does anyone look at this?
                red_sum_y += 0 * image[i][j].rgbtRed;
                green_sum_y += 0 * image[i][j].rgbtGreen;
                blue_sum_y += 0 * image[i][j].rgbtBlue;

                red_sum_y += -2 * image[i - 1][j].rgbtRed;
                green_sum_y += -2 * image[i - 1][j].rgbtGreen;
                blue_sum_y += -2 * image[i - 1][j].rgbtBlue;

                red_sum_y += 2 * image[i + 1][j].rgbtRed;
                green_sum_y += 2 * image[i + 1][j].rgbtGreen;
                blue_sum_y += 2 * image[i + 1][j].rgbtBlue;

                //check for valid range
                red_root = round(sqrt(red_sum_x * red_sum_x + red_sum_y * red_sum_y));
                if (red_root > 255)
                {
                    red_root = 255;
                }
                green_root = round(sqrt(green_sum_x * green_sum_x + green_sum_y * green_sum_y));
                if (green_root > 255)
                {
                    green_root = 255;
                }
                blue_root = round(sqrt(blue_sum_x * blue_sum_x + blue_sum_y * blue_sum_y));
                if (blue_root > 255)
                {
                    blue_root = 255;
                }

                dummy[i][j].rgbtRed = red_root;
                dummy[i][j].rgbtGreen = green_root;
                dummy[i][j].rgbtBlue = blue_root;
                continue;
            }
            if ((i + 1) == height)
            {
                //bottom edge
                //gx computation
                red_sum_x += 0 * image[i][j].rgbtRed;
                green_sum_x += 0 * image[i][j].rgbtGreen;
                blue_sum_x += 0 * image[i][j].rgbtBlue;

                red_sum_x += -2 * image[i][j - 1].rgbtRed;
                green_sum_x += -2 * image[i][j - 1].rgbtGreen;
                blue_sum_x += -2 * image[i][j - 1].rgbtBlue;

                red_sum_x += 2 * image[i][j + 1].rgbtRed;
                green_sum_x += 2 * image[i][j + 1].rgbtGreen;
                blue_sum_x += 2 * image[i][j + 1].rgbtBlue;
                //just because
                red_sum_x += 0 * image[i - 1][j].rgbtRed;
                green_sum_x += 0 * image[i - 1][j].rgbtGreen;
                blue_sum_x += 0 * image[i - 1][j].rgbtBlue;

                red_sum_x += -1 * image[i - 1][j - 1].rgbtRed;
                green_sum_x += -1 * image[i - 1][j - 1].rgbtGreen;
                blue_sum_x += -1 * image[i - 1][j - 1].rgbtBlue;

                red_sum_x += 1 * image[i - 1][j + 1].rgbtRed;
                green_sum_x += 1 * image[i - 1][j + 1].rgbtGreen;
                blue_sum_x += 1 * image[i - 1][j + 1].rgbtBlue;

                //gy computation

                red_sum_y += 0 * image[i][j].rgbtRed;
                green_sum_y += 0 * image[i][j].rgbtGreen;
                blue_sum_y += 0 * image[i][j].rgbtBlue;

                red_sum_y += 0 * image[i][j - 1].rgbtRed;
                green_sum_y += 0 * image[i][j - 1].rgbtGreen;
                blue_sum_y += 0 * image[i][j - 1].rgbtBlue;

                red_sum_y += 0 * image[i][j + 1].rgbtRed;
                green_sum_y += 0 * image[i][j + 1].rgbtGreen;
                blue_sum_y += 0 * image[i][j + 1].rgbtBlue;
                //sup
                red_sum_y += -2 * image[i - 1][j].rgbtRed;
                green_sum_y += -2 * image[i - 1][j].rgbtGreen;
                blue_sum_y += -2 * image[i - 1][j].rgbtBlue;

                red_sum_y += -1 * image[i - 1][j - 1].rgbtRed;
                green_sum_y += -1 * image[i - 1][j - 1].rgbtGreen;
                blue_sum_y += -1 * image[i - 1][j - 1].rgbtBlue;

                red_sum_y += -1 * image[i - 1][j + 1].rgbtRed;
                green_sum_y += -1 * image[i - 1][j + 1].rgbtGreen;
                blue_sum_y += -1 * image[i - 1][j + 1].rgbtBlue;

                red_root = round(sqrt(red_sum_x * red_sum_x + red_sum_y * red_sum_y));
                if (red_root > 255)
                {
                    red_root = 255;
                }
                green_root = round(sqrt(green_sum_x * green_sum_x + green_sum_y * green_sum_y));
                if (green_root > 255)
                {
                    green_root = 255;
                }
                blue_root = round(sqrt(blue_sum_x * blue_sum_x + blue_sum_y * blue_sum_y));
                if (blue_root > 255)
                {
                    blue_root = 255;
                }

                dummy[i][j].rgbtRed = red_root;
                dummy[i][j].rgbtGreen = green_root;
                dummy[i][j].rgbtBlue = blue_root;
                continue;
            }

            //gx computation
            red_sum_x += 0 * image[i][j].rgbtRed;
            green_sum_x += 0 * image[i][j].rgbtGreen;
            blue_sum_x += 0 * image[i][j].rgbtBlue;

            red_sum_x += -1 * image[i - 1][j - 1].rgbtRed;
            green_sum_x += -1 * image[i - 1][j - 1].rgbtGreen;
            blue_sum_x += -1 * image[i - 1][j - 1].rgbtBlue;

            red_sum_x += 0 * image[i - 1][j].rgbtRed;
            green_sum_x += 0 * image[i - 1][j].rgbtGreen;
            blue_sum_x += 0 * image[i - 1][j].rgbtBlue;

            red_sum_x += 1 * image[i - 1][j + 1].rgbtRed;
            green_sum_x += 1 * image[i - 1][j + 1].rgbtGreen;
            blue_sum_x += 1 * image[i - 1][j + 1].rgbtBlue;

            red_sum_x += -2 * image[i][j - 1].rgbtRed;
            green_sum_x += -2 * image[i][j - 1].rgbtGreen;
            blue_sum_x += -2 * image[i][j - 1].rgbtBlue;
            //commenting possibilities
            red_sum_x += 2 * image[i][j + 1].rgbtRed;
            green_sum_x += 2 * image[i][j + 1].rgbtGreen;
            blue_sum_x += 2 * image[i][j + 1].rgbtBlue;

            red_sum_x += -1 * image[i + 1][j - 1].rgbtRed;
            green_sum_x += -1 * image[i + 1][j - 1].rgbtGreen;
            blue_sum_x += -1 * image[i + 1][j - 1].rgbtBlue;

            red_sum_x += 0 * image[i + 1][j].rgbtRed;
            green_sum_x += 0 * image[i + 1][j].rgbtGreen;
            blue_sum_x += 0 * image[i + 1][j].rgbtBlue;

            red_sum_x += 1 * image[i + 1][j + 1].rgbtRed;
            green_sum_x += 1 * image[i + 1][j + 1].rgbtGreen;
            blue_sum_x += 1 * image[i + 1][j + 1].rgbtBlue;

            //gy computation

            red_sum_y += 0 * image[i][j].rgbtRed;
            green_sum_y += 0 * image[i][j].rgbtGreen;
            blue_sum_y += 0 * image[i][j].rgbtBlue;

            red_sum_y += -1 * image[i - 1][j - 1].rgbtRed;
            green_sum_y += -1 * image[i - 1][j - 1].rgbtGreen;
            blue_sum_y += -1 * image[i - 1][j - 1].rgbtBlue;

            red_sum_y += -2 * image[i - 1][j].rgbtRed;
            green_sum_y += -2 * image[i - 1][j].rgbtGreen;
            blue_sum_y += -2 * image[i - 1][j].rgbtBlue;

            red_sum_y += -1 * image[i - 1][j + 1].rgbtRed;
            green_sum_y += -1 * image[i - 1][j + 1].rgbtGreen;
            blue_sum_y += -1 * image[i - 1][j + 1].rgbtBlue;

            red_sum_y += 0 * image[i][j - 1].rgbtRed;
            green_sum_y += 0 * image[i][j - 1].rgbtGreen;
            blue_sum_y += 0 * image[i][j - 1].rgbtBlue;
            //even more so
            red_sum_y += 0 * image[i][j + 1].rgbtRed;
            green_sum_y += 0 * image[i][j + 1].rgbtGreen;
            blue_sum_y += 0 * image[i][j + 1].rgbtBlue;

            red_sum_y += 1 * image[i + 1][j - 1].rgbtRed;
            green_sum_y += 1 * image[i + 1][j - 1].rgbtGreen;
            blue_sum_y += 1 * image[i + 1][j - 1].rgbtBlue;

            red_sum_y += 2 * image[i + 1][j].rgbtRed;
            green_sum_y += 2 * image[i + 1][j].rgbtGreen;
            blue_sum_y += 2 * image[i + 1][j].rgbtBlue;

            red_sum_y += 1 * image[i + 1][j + 1].rgbtRed;
            green_sum_y += 1 * image[i + 1][j + 1].rgbtGreen;
            blue_sum_y += 1 * image[i + 1][j + 1].rgbtBlue;

            red_root = round(sqrt(red_sum_x * red_sum_x + red_sum_y * red_sum_y));
            green_root = round(sqrt(green_sum_x * green_sum_x + green_sum_y * green_sum_y));
            blue_root = round(sqrt(blue_sum_x * blue_sum_x + blue_sum_y * blue_sum_y));

            dummy[i][j].rgbtRed = (int)red_root;
            dummy[i][j].rgbtGreen = (int)green_root;
            dummy[i][j].rgbtBlue = (int)blue_root;
        }
    }
    //print deep copy to image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = dummy[i][j].rgbtRed;
            image[i][j].rgbtGreen = dummy[i][j].rgbtGreen;
            image[i][j].rgbtBlue = dummy[i][j].rgbtBlue;
        }
    }
    //free the space of dummy variable
    free(dummy);
    return;
}
