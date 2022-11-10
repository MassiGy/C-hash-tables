#include "../headers/hash-tables.h"

ghash_table_t *create_hash_table(int keys_store_size)
{
    ghash_table_t *hash_table = malloc(sizeof(ghash_table_t));
    assert(hash_table != NULL);

    hash_table->keys_store_length = keys_store_size;

    hash_table->keys_store = malloc(keys_store_size * sizeof(glist_t *));

    return hash_table;
}

void destroy_hash_table(ghash_table_t **phash_table)
{
    assert(phash_table != NULL);
    assert(*phash_table != NULL);

    // go through the store, and destroy each chain
    for (int i = 0; i < (*phash_table)->keys_store_length; ++i)
    {
        destroy_glist(&((*phash_table)->keys_store[i]));
    }

    // free the chain array
    free((*phash_table)->keys_store);

    // free the hash table
    free((*phash_table));

    // set the hash table refrence equal to null
    // to no derefrence a non existing struct
    phash_table = NULL;
}

// the key will be our array index for the given data
int get_hash_key(char *data)
{
    assert(data != NULL);

    int char_ords_sum = 0;

    for (int i = 0; data[i] != '\0'; ++i)
    {
        char_ords_sum += (int)data[i];
    }

    char_ords_sum -= ORD_OFFSET;

    assert(char_ords_sum <= KEYS_STORE_LENGTH);
    return char_ords_sum;
}

void insertTo_hash_table(ghash_table_t **phash_table, char *data)
{
    assert(phash_table != NULL);
    assert(*phash_table != NULL);
    assert(data != NULL);

    int hash = get_hash_key(data);

    char buffer[strlen(data) + 1];

    strcpy(buffer, data);
    buffer[strlen(data)] = '\0';

    push_glist(&((*phash_table)->keys_store[hash]), data, strlen(data) + 1);
}

// the file will contains our words
void loadTo_hash_table(ghash_table_t **phash_table, const char *filename)
{
    assert(phash_table != NULL);
    assert(*phash_table != NULL);
    assert(filename != NULL);

    FILE *file = fopen(filename, "rt");
    assert(file != NULL);

    char buffer[34];
    char *data;

    while (!feof(file))
    {
        fgets(buffer, 32, file);

        data = malloc((strlen(buffer) + 1) * sizeof(char));

        data[strlen(buffer)] = '\0';

        insertTo_hash_table(phash_table, data);

        free(data);
    }

    fclose(file);
}

bool searchIn_hash_table(ghash_table_t **phash_table, char *data)
{
    assert(phash_table != NULL);
    assert(*phash_table != NULL);
    assert(data != NULL);

    // first get the hash (index of the chain that contains the data)
    int hash = get_hash_key(data);

    return searchIn_glist(&((*phash_table)->keys_store[hash]), data, &strcmp);
}
