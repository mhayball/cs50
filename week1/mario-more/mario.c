#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // get height so long as between 1 and 8 inclusive
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    //loop for rows
    int i;
    for (i = 0; i < height; i++)
    {

        //loop for spaces
        int j;
        for (j = i + 1; j < height; j++)
        {
            printf(" ");
        }

        //loop for hashes
        int k;
        for (k = 0; k <= i; k++)
        {
            printf("#");
        }

        //print space in middle
        printf("  ");

        //loop for hashes
        for (k = 0; k <= i; k++)
        {
            printf("#");
        }

        printf("\n");
    }

}
