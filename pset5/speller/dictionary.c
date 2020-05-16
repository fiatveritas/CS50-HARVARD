// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"

#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];
// Size of dictionary
int total_size = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    int hash_value = hash(word);
    node *temp = table[hash_value];
    while (temp != NULL)
    {
        if (strcasecmp(word, temp->word) == 0)
        {
            return true;
        }
        temp = temp->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    char first_letter = tolower(word[0]);
    for (char i = 'a'; i <= 'z'; i++)
    {
        //97 is the acii value of 'a'
        if (i == first_letter)
        {
            return first_letter - 97;
        }
    }
    return 0;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *words = fopen(dictionary, "r");

    if (words == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }
    else
    {
        char word[LENGTH + 1];
        int index = 0; //this keeps track of the length of a word
        int counter = 0; //this counts the number of words
        unsigned int hash_value = 0;
        int c = getc(words);
        while (c != EOF)
        {
            if (isspace(c) == 0)
            {
                word[index] = c;
                index++;
                c = getc(words);
            }
            else
            {
                word[index] = '\0';
                node *junk = (node *) malloc(sizeof(node));
                node *temp;
                strcpy(junk->word, word);
                junk->next = NULL;
                hash_value = hash(junk->word);

                if (table[hash_value] == NULL)
                {
                    table[hash_value] = junk;
                }
                else if (table[hash_value]->next == NULL)
                {
                    junk->next = table[hash_value]->next;
                    table[hash_value]->next = junk;
                }
                else
                {
                    temp = table[hash_value]->next;
                    junk->next = temp;
                    table[hash_value]->next = junk;
                }

                index = 0;
                counter++;
                c = getc(words);
            }
        }

        total_size = counter;
        fclose(words);
        return true;
    }
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return total_size;
}

void erase(node *passed)
{
    if (passed != NULL)
    {
        erase(passed->next);
        passed->next = NULL;
        free(passed);
    }
    else
    {
        return;
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    int index = 0;
    node *cursor;
    for (int i = 0; i < N; i++)
    {
        cursor = table[i];
        erase(cursor);

        if (i == N - 1)
        {
            return true;
        }
    }

    return false;
}


/*
./speller texts/lalaland.txt
*/

/*
valgrind ./speller texts/cat.txt
*/

/*
check50 cs50/problems/2020/x/speller
*/