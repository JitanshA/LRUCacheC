#include "hash_utils.h"

unsigned long djb2_hash(const char *key)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *key++))
    {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    return hash;
}

int key_to_index(char *key, int capacity)
{
    if (!key || capacity <= 0)
    {
        return -1;
    }

    unsigned long hash = djb2_hash(key);
    return hash % capacity;
}
