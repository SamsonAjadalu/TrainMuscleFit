// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

int count = 0; // Counter for the number of words in the dictionary

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 10000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    char upper_word[LENGTH + 1];
    int len = strlen(word);
    for (int i = 0; i < len; i++)
    {
        upper_word[i] = toupper(word[i]);
    }
    upper_word[len] = '\0';

    unsigned int index = hash(upper_word);
    node *cursor = table[index];

    while (cursor != NULL)
    {
        if (strcmp(cursor->word, upper_word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}


// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned int hash = 0;
    while (*word)
    {
        hash = (hash << 2) ^ toupper(*word++);
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *dict_file = fopen(dictionary, "r");
    if (dict_file == NULL){
        printf("Can't open file");

        return false;
    }
    char word[LENGTH + 1];
    // Read words from the file
    while (fscanf(dict_file, "%45s", word) != EOF)
    {
        // new node
        node *n = malloc(sizeof(node));
        if (n==NULL)
        {

            printf("Cant assign memory to new node");
            return false;
        }

        // Convert to uppercase
        for(int i=0, word_len = strlen(word); i<word_len; i++)
        {
            word[i] = toupper(word[i]);
        }


        // Copy word into the node
        strcpy(n->word, word);
        unsigned int index = hash(word);
        // Get hash index
        n->next = table[index];
        table[index] = n;

       // printf("Inserted %s at index %u\n", word, index);
        count++;
    }
    fclose(dict_file);
    return true;
}


// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO

    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // Go through hash table
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            printf("Freeing %s\n", temp->word);
            free(temp);
        }
    }
    return true;
}
