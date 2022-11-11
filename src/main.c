#include "../headers/main.h"

int main(void)
{

    ghash_table_t *hash_table = create_hash_table(KEYS_STORE_LENGTH);

    loadTo_hash_table(&hash_table, "./ressources/words.txt");

    print_hash_table(&hash_table);

    bool search_resault = searchIn_hash_table(&hash_table, "car");

    printf("%s\n", search_resault ? "found" : "not found");

    destroy_hash_table(&hash_table);

    return 0;
}
