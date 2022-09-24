#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else if (score1 == score2)
    {
        printf("Tie!\n");
    }

}

int compute_score(string word)
{
    //printf("%s\n", word);

    // Compute and return score for string
    int score = 0;

    // Get word length
    int length = strlen(word);

    int code, array;

    // cycle through characters
    for (int i = 0; i < length; i++)
    {
        code = toupper(word[i]);
        array = code - 65;

        //printf("%c, %i, %i\n", code, code, array);

        if (array >= 0 && array < 26)
        {
            score += POINTS[array];
            //printf("%i\n", POINTS[array]);
        }
    }

    //printf("Score: %i\n", score);

    return score;
}
