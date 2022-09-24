#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void)
{
    // Get text from user
    string text = get_string("Text: ");
    printf("%s\n", text);

    int letters = 0;
    int words = 1;
    int sentences = 0;

    // cycle through characters
    int length = strlen(text);

    for (int i = 0; i < length; i++)
    {
        // if a letter, add to letters - 65-90 97-122
        if (text[i] <= 90 && text[i] >= 65)
        {
            letters += 1;
        }
        if (text[i] <= 122 && text[i] >= 97)
        {
            letters += 1;
        }

        // if a space, add to words - 32
        if (text[i] == 32)
        {
            words += 1;
        }

        // if a .?! add to sentences - 33, 46, 63
        if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            sentences += 1;
        }
    }

    printf("Letters: %i\n", letters);
    printf("Words: %i\n", words);
    printf("Sentences: %i\n", sentences);

    // L is the average number of letters per 100 words in the text,
    // S is the average number of sentences per 100 words in the text.

    float l = (float) letters / words * 100.0;
    float s = (float) sentences / words * 100.0;

    printf("l: %f\n", l);
    printf("s: %f\n", s);

    float index = 0.0588 * l - 0.296 * s - 15.8;

    printf("Index: %f\n", index);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (round(index) >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.0f\n", round(index));
    }

}
