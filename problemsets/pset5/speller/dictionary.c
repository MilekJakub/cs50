// Implements a dictionary's functionality
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents an item in a hashtable
typedef struct hashtable_item
{
    char word[LENGTH + 1];
    struct hashtable_item *next;
}
hashtable_item;

// Number of buckets in hash table
// a-z + aa-zz + aaa-zzz
// 26 + (26 * 26) + (26 * 26 * 26)
const unsigned int N = 18278;

// Represents whole hashtable
typedef struct hashtable
{
    hashtable_item *items[N];
    size_t count;
}
hashtable;


// Global hashtable
hashtable *table = NULL;

hashtable* create_hashtable()
{
    hashtable *new_table = malloc(sizeof(hashtable));

    if (new_table == NULL)
    {
        printf("ERROR: Cannot create hashtable!\n");
        return NULL;
    }

    new_table->count = 0;

    for (int i = 0; i < N; i++)
    {
        new_table->items[i] = NULL;
    }

    return new_table;
}

hashtable_item* hashtable_item_create(char *word)
{
    hashtable_item *item = malloc(sizeof(hashtable_item));
    strcpy(item->word, word);
    item->next = NULL;
    return item;
}

bool hashtable_insert(hashtable *hashtable, hashtable_item *item)
{
    if (hashtable == NULL || item == NULL)
    {
        return false;
    }

    unsigned int key = hash(item->word);
    item->next = hashtable->items[key];
    hashtable->items[key] = item;
    hashtable->count++;
    return true;
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int key = hash(word);
    hashtable_item* search = table->items[key];

    if (search == NULL)
    {
        return false;
    }

    if (strcasecmp(search->word, word) == 0)
    {
        return true;
    }

    while (search->next != NULL)
    {
        search = search->next;
        if (strcasecmp(search->word, word) == 0)
        {
            return true;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // a .. z
    // 0 .. 25
    
    // aa .. zz
    // 26 .. 727
    
    // aaa .. zzz
    // 728 .. 18277

    // a -> 0
    // aa -> 26
    // aaa -> 728

    size_t length = strlen(word);
    unsigned int key = 0;

    if (length == 1)
    {
        key += tolower(word[0]) - 'a';
    }

    if (length == 2)
    {
        key += (tolower(word[0]) - 'a') * 26 + 26;
        key += (tolower(word[1]) - 'a');
    }

    if (length >= 3)
    {
        key += (tolower(word[0]) - 'a') * 26 * 26 + 676;
        key += (tolower(word[1]) - 'a') * 26 + 26;
        key += (tolower(word[2]) - 'a');
    }

    return key;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    printf("Creating hashtable..\n");
    table = create_hashtable();

    if (table == NULL)
    {
        printf("ERROR: Cannot create hashtable..\n");
        return false;
    }

    printf("Openning file..\n");
    FILE *file = fopen(dictionary, "r");

    if (file == NULL)
    {
        printf("ERROR: Cannot open the file..\n");
        return false;
    }
    
    char *buffer = NULL;
    size_t len = 0;
    ssize_t nread = 0;

    printf("looping through lines..\n");
    while ((nread = getline(&buffer, &len, file)) != -1)
    {
        size_t length = strlen(buffer);
        buffer[length - 1] = '\0';
        unsigned int key = hash(buffer);
        hashtable_item *item = hashtable_item_create(buffer);

        if(!hashtable_insert(table, item))
        {
            printf("ERROR: Cannot insert item to hashtable..\n");
            unload();
            return false;
        }
    }

    printf("closing file..\n");
    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (table == NULL)
    {
        return 0;
    }

    return table->count;
}

void unload_item(hashtable_item *item)
{
    if (item->next != NULL)
    {
        unload_item(item->next);
    }

    free(item);
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    printf("unloading all hashtable items..\n");
    for (int i = 0; i < N; i++)
    {
        if (table->items[i] != NULL)
        {
            unload_item(table->items[i]);
        }
    }

    printf("unloading hashtable..\n");
    free(table);
    
    return true;
}

