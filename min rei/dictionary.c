// Implements a dictionary's functionality
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 150000;

// Hash table
node *table[N];

// Total words in dictionary
int dic_size = 0;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *dic_inptr = fopen(dictionary, "r");

    if (dic_inptr == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }

    // Buffer to copy word from dic_inptr to buffer to dynamically allocated memory saved in hashtable "table[N]"
    char buffer[LENGTH + 1];

    // Hash value from hash function
    unsigned int index;

    while (!feof(dic_inptr))
    {
        // Read the first string separated by a space, ignore the rest of the line
        fscanf(dic_inptr, "%s%*[^\n]", buffer);

        // Create a new node to store word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("ERROR: Could not allocate memory.\n");
            return false;
        }

        // Obtain hash value for given word (saved in buffer)
        index = hash(buffer);

        // Copy buffer into node
        strcpy(buffer, n->word);
        n->next = table[index];
        table[index] = n;

        // Increase dictionary size by one
        dic_size ++;
    }

    fclose(dic_inptr);
    return true;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int index = 5831;

    for (int i = 0, len = strlen(word); i < len; i++)
    {
        index = index * 33 + tolower(word[i]);
    }

    index = index % N;

    return index;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return dic_size - 1; //minus 1 to account for empty lastline
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Hash value from hashing word
    unsigned int index = hash(word);

    // Initialise temporary pointer
    node *tmp_ptr = NULL;

    // Iterate across linked list until NULL is reached
    if (table[index] == NULL)
    {
        return false;
    }

    tmp_ptr = table[index];

    while (tmp_ptr != NULL)
    {
        if (strcasecmp(tmp_ptr->word, word))
        {
            return true;
        }

        else
        {
            tmp_ptr = tmp_ptr->next;
        }
    }

    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Iterate down buckets in hash table, deleting corresponding linked list
    for (int i = 0; i < N; i ++)
    {
        node *fast_ptr = table[i];

        while (fast_ptr != NULL)
        {
            node *slow_ptr = fast_ptr;
            fast_ptr = fast_ptr->next;
            free (slow_ptr);
        }
    }
    return true;
}
