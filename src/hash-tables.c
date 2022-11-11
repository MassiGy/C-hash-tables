#include "../headers/hash-tables.h"

ghash_table_t *create_hash_table(int keys_store_size)
{
    ghash_table_t *hash_table = malloc(sizeof(ghash_table_t));
    assert(hash_table != NULL);

    hash_table->keys_store_length = keys_store_size;

    hash_table->keys_store = malloc(keys_store_size * sizeof(glist_t *));

    return hash_table;
}

void print_hash_table(ghash_table_t **phash_table)
{
    assert(phash_table != NULL);
    assert(*phash_table != NULL);

    printf("CONSIDER REDIRECTING THE OUTPUT TO A TXT FILE");

    for (int i = 0; i < (*phash_table)->keys_store_length; ++i)
    {
        printf("\n[--------------------------------------------------------]\n");
        printf("When hash = %i, values are as follows : \n", i);
        print_glist(&(*phash_table)->keys_store[i], &print_str);
    }
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
        if ((int)data[i] >= (int)'a' && (int)data[i] <= (int)'z')
        {
            char_ords_sum += (int)data[i];
            char_ords_sum -= ORD_OFFSET;
        }
    }

    assert(char_ords_sum <= KEYS_STORE_LENGTH);
    return char_ords_sum;
}

void insertTo_hash_table(ghash_table_t **phash_table, char *data)
{
    assert(phash_table != NULL);
    assert(*phash_table != NULL);
    assert(data != NULL);

    int hash = get_hash_key(data);

    // This will be the error correction, since the data is structred as follows : str+space+new_line
    // so, to get the comparaison resault correct, we need to remove the space+new_line

    // start with a length equal to the data length, which is a maximum since it contains space+new_line
    char temp[strlen(data)];

    int i = 0;
    while (i < strlen(data))
    {
        //  insert till hitting a non alphabatical character
        if (!((int)data[i] >= 'a' && (int)data[i] <= 'z'))
            break;

        temp[i] = data[i];
        i++;
    }
    temp[i] = '\0';

    push_glist(&((*phash_table)->keys_store[hash]), temp, strlen(temp) + 1);
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

    while (!feof(file))
    {
        fgets(buffer, 32, file);
        insertTo_hash_table(phash_table, buffer);
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
