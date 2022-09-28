#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // get key
    string key = argv[1];

    //printf("%i\n", argc);
    //printf("%s\n", key);

    // validate key
    // check if key populated

    if (argc > 2)
    {
        printf("Usage: ./substitution KEY\n");
        return 1;
    }

    if (key == NULL)
    {
        printf("Usage: ./substitution KEY\n");
        return 1;
    }

    // check key length
    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // check non alpha characters
    char x;
    for (int i = 0; i < 26; i++)
    {
        x = key[i];
        if (isalpha(x) == 0)
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
    }

    // check no repeat characters - e.g. check all characters are present
    int check;
    // loop through ascii characters, and check they are present in the key
    for (int i = 65; i < 90; i++)
    {
        check = 0;
        for (int j = 0; j < 26; j++)
        {
            // if key matches the ascii character, mark as 1 and exit loop
            if (toupper(key[j]) == i)
            {
                check = 1;
                j = 25;
            }
        }
        if (check == 0)
        {
            printf("Key must not contain repeat characters.\n");
            return 1;
        }
    }

    // get plaintext
    string plaintext = get_string("plaintext: ");
    //printf("%s\n", plaintext);

    // encipher text
    // set ciphertext as plaintext, and then encipher
    string ciphertext = plaintext;
    //printf("%s\n", ciphertext);

    // cycle through characters and convert
    int y;
    for (int i = 0; i < strlen(plaintext); i++)
    {
        //printf("%c\n", plaintext[i]);

        // only look at alpha characters
        if (isalpha(plaintext[i]))
        {
            // convert plaintext character to integer between 0 and 25
            y = toupper(plaintext[i]) - 65;

            if (islower(plaintext[i]))
            {
                //printf("%c\n", ciphertext[i]);
                ciphertext[i] = tolower(key[y]);
                //printf("%c\n", ciphertext[i]);
            }
            else if (isupper(plaintext[i]))
            {
                ciphertext[i] = toupper(key[y]);
            }

        }

    }

    // print ciphertext
    printf("ciphertext: %s\n", ciphertext);

}
