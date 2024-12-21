#include "hash_utils.h"

// Implements the djb2 hashing algorithm for strings
unsigned long djb2_hash(const char *key)
{
    unsigned long hash = 5381;
    int c;

    // Iterate through each character in the string and update the hash
    while ((c = *key++))
    {
        // Multiply the current hash by 33 and add the current character
        hash = ((hash << 5) + hash) + c;
    }

    // Return the resulting hash value
    return hash;
}

// Maps a key to an index within the cache's hash table based on its capacity
int key_to_index(char *key, int capacity)
{
    // Return -1 if the key is NULL or capacity is invalid
    if (!key || capacity <= 0)
    {
        return -1;
    }

    // Compute the hash value for the given key
    unsigned long hash = djb2_hash(key);

    // Return the index by taking the hash modulo the capacity
    return hash % capacity;
}
