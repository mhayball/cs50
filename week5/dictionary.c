// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26 * 26 * 26;

// Hash table
node *table[N];

// word count
int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // case insensitive

    // hash word
    int hash_index = hash(word);

    // set pointer to index
    node *cursor = table[hash_index];

    // traverse list looking for a str match
    while (cursor != NULL)
    {
        // check if string matches current cursor location
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        // move cursor to next list location
        cursor = cursor->next;
    }
    // if not found in list, return false (e.g. spelling mistake)
    return false;

}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // new function - use first three letters
    int result = 0;

    // calculate length of word
    int length = strlen(word);

    // check length of word and calculate index accordingly
    if (length > 2)
    {
        result = ((toupper(word[0]) - 'A') * 26 * 26) + ((toupper(word[1]) - 'A') * 26) + toupper(word[2]) - 'A';
    }
    else if (length == 1)
    {
        result = ((toupper(word[0]) - 'A') * 26) + toupper(word[1]) - 'A';
    }
    else
    {
        result = toupper(word[0]) - 'A';
    }

    // cap result at N - 1, just in case of error in calculation above
    if (result > N)
    {
        result = N - 1;
    }

    return result;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO

    // open dictionary file
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    // read strings one at a time
    char new_word[LENGTH + 1];

    while (fscanf(dict, "%s", new_word) != EOF)
    {
        //printf("%s\n", new_word);

        // create new node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            free(n);
            fclose(dict);
            return false;
        }

        // copy word into new node
        strcpy(n->word, new_word);
        n->next = NULL;

        // use hash function - function takes a string and returns an index - to get index
        int hash_index = hash(new_word);

        // insert node into hash table at that location
        // BUT first set new node pointer to old/existing node
        // then set head pointer to new node
        n->next = table[hash_index];
        table[hash_index] = n;

        // increase word count
        word_count += 1;

    }

    // close dictionary file
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // iterate over hash table, calling free on each node - use tmp variable to keep moving down the list
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
    }

    return true;
}
