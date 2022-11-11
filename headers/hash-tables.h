/*
@author : Massiles GHERNAOUT
@link   : github.com/MassiGy/hash-tables
@description : Implementation of a Hash table, with a hash fonction that returns a key equal to the sum
of the ordinal value (ascii integer representation) of lowercase caracter based words.

The array that will hold the chains (linked lists) will be of a length equal to the diffrence between the biggest value of
the ordinal representation in the english words and the smallest one.

Since, we will deal only with lowercase caracters, we assume that the lowest ordinal value will be attributed to the word "a"
and we assume that the beggest one will be attributed to this hypotherical word "zzzzzzzzzzzz" ("z" 20 times)

So the lenght will be something like this: ((int) "zx20") - 20 * ((int) 'a') ~ 500

*/

#include "./sys_headers.h"
#include "./generic-linked-lists.h"

// So the lenght will be something like this: ((int) "zx20") - 20 * ((int) 'a') ~ 500
#define KEYS_STORE_LENGTH 500

// define the offset = ord('a');
#define ORD_OFFSET 97

// since our linked lists are generic, our hash tables will inherit this behaviour
struct ghash_table
{
    int keys_store_length;
    glist_t **keys_store;
};

typedef struct ghash_table ghash_table_t;

ghash_table_t *create_hash_table(int keys_store_size);
void destroy_hash_table(ghash_table_t **phash_table);
void print_hash_table(ghash_table_t **phash_table);
void loadTo_hash_table(ghash_table_t **phash_table, const char *filename); // the file will contains our words
int get_hash_key(char *data);                                              // the key will be our array index for the given data
void insertTo_hash_table(ghash_table_t **phash_table, char *data);
bool searchIn_hash_table(ghash_table_t **phash_table, char *data);
