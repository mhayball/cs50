#include <stdlib.h>
#include <math.h>

#include "helpers.h"


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // grey = average of rgb values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double average = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;
            int grey = round(average);

            image[i][j].rgbtRed = grey;
            image[i][j].rgbtGreen = grey;
            image[i][j].rgbtBlue = grey;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int mid = 0;

    // if width is even, then go to mid point, if odd, then leave central pixels
    if (width % 2 == 0)
    {
        mid = width / 2;
    }
    else
    {
        mid = (width - 1) / 2;
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < mid; j++)
        {
            int tempRed = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][width - j - 1].rgbtRed = tempRed;

            int tempGreen = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][width - j - 1].rgbtGreen = tempGreen;

            int tempBlue = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][width - j - 1].rgbtBlue = tempBlue;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // average of neighbouring pixels - box blur

    // create copy of image for reference
    RGBTRIPLE(*image2)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image2[i][j].rgbtRed = image[i][j].rgbtRed;
            image2[i][j].rgbtGreen = image[i][j].rgbtGreen;
            image2[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    // loop through, calculate and set for average value of surrounding pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // set bounds of blur
            int xMin, xMax, yMin, yMax;
            double counter = 0.0;

            if (i == 0)
            {
                xMin = 0;
            }
            else
            {
                xMin = i - 1;
            }

            if (i == height - 1)
            {
                xMax = height - 1;
            }
            else
            {
                xMax = i + 1;
            }

            if (j == 0)
            {
                yMin = 0;
            }
            else
            {
                yMin = j - 1;
            }

            if (j == width - 1)
            {
                yMax = width - 1;
            }
            else
            {
                yMax = j + 1;
            }

            int avgRed = 0;
            int avgGreen = 0;
            int avgBlue = 0;

            for (int x = xMin; x <= xMax; x++)
            {
                for (int y = yMin; y <= yMax; y++)
                {
                    avgRed += image2[x][y].rgbtRed;
                    avgGreen += image2[x][y].rgbtGreen;
                    avgBlue += image2[x][y].rgbtBlue;
                    counter += 1.0;
                }
            }

            image[i][j].rgbtRed = round(avgRed / counter);
            image[i][j].rgbtGreen = round(avgGreen / counter);
            image[i][j].rgbtBlue = round(avgBlue / counter);

        }
    }

    free(image2);
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // sobel operator
    int kernelx[3][3] = { {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1} };
    int kernely[3][3] = { {-1, -2, -1}, {0, 0, 0}, {1, 2, 1} };

    // create copy of image for reference
    RGBTRIPLE(*image2)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image2[i][j].rgbtRed = image[i][j].rgbtRed;
            image2[i][j].rgbtGreen = image[i][j].rgbtGreen;
            image2[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    // loop through, calculate and set for average value of surrounding pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // set bounds of edge
            int xMin, xMax, yMin, yMax;

            if (i == 0)
            {
                xMin = 0;
            }
            else
            {
                xMin = i - 1;
            }

            if (i == height - 1)
            {
                xMax = height - 1;
            }
            else
            {
                xMax = i + 1;
            }

            if (j == 0)
            {
                yMin = 0;
            }
            else
            {
                yMin = j - 1;
            }

            if (j == width - 1)
            {
                yMax = width - 1;
            }
            else
            {
                yMax = j + 1;
            }

            // calculate gx and gy values

            int gxRed = 0;
            int gxBlue = 0;
            int gxGreen = 0;

            int gyRed = 0;
            int gyBlue = 0;
            int gyGreen = 0;

            for (int x = - 1; x <= 1; x++)
            {
                for (int y = - 1; y <= 1; y++)
                {
                    // ignore if values are beyond xMin, xMax, yMin or yMax
                    if (i + x < xMin || i + x > xMax || j + y < yMin || j + y > yMax)
                    {
                        continue;
                    }
                    else
                    {
                        // multiply by relevant kernel to calulate g value
                        gxRed += image2[i + x][j + y].rgbtRed * kernelx[x + 1][y + 1];
                        gxGreen += image2[i + x][j + y].rgbtGreen * kernelx[x + 1][y + 1];
                        gxBlue += image2[i + x][j + y].rgbtBlue * kernelx[x + 1][y + 1];

                        gyRed += image2[i + x][j + y].rgbtRed * kernely[x + 1][y + 1];
                        gyGreen += image2[i + x][j + y].rgbtGreen * kernely[x + 1][y + 1];
                        gyBlue += image2[i + x][j + y].rgbtBlue * kernely[x + 1][y + 1];
                    }
                }
            }

            // calculate sobel (G) values
            long gxyRed = round(sqrt(pow(gxRed, 2) + pow(gyRed, 2)));
            long gxyGreen = round(sqrt(pow(gxGreen, 2) + pow(gyGreen, 2)));
            long gxyBlue = round(sqrt(pow(gxBlue, 2) + pow(gyBlue, 2)));

            // cap values at 255
            if (gxyRed > 255)
            {
                gxyRed = 255;
            }
            if (gxyGreen > 255)
            {
                gxyGreen = 255;
            }
            if (gxyBlue > 255)
            {
                gxyBlue = 255;
            }

            // update image
            image[i][j].rgbtRed = gxyRed;
            image[i][j].rgbtGreen = gxyGreen;
            image[i][j].rgbtBlue = gxyBlue;

        }
    }

    free(image2);
    return;
}
