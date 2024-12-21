#ifndef HASH_UTILS_H
#define HASH_UTILS_H

// Function to calculate a djb2 hash for a string
unsigned long djb2_hash(const char *key);

// Map a string key to an index within a given capacity
int key_to_index(char *key, int capacity);

#endif // HASH_UTILS_H
