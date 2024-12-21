#ifndef KEY_VALUE_PAIR_H
#define KEY_VALUE_PAIR_H

typedef struct kv_pair
{
    char *key;
    char *value;
} kv_pair_t;

// Create a new key-value pair
extern kv_pair_t *new_kv_pair(char *key, char *value);

// Get the value associated with a key from a key-value pair
extern char *kv_pair_get_value(kv_pair_t *kv_pair);

// Update the value in a key-value pair
extern void kv_pair_set_value(kv_pair_t *kv_pair, char *new_value);

// Get the key from a key-value pair
extern char *kv_pair_get_key(kv_pair_t *kv_pair);

// Free a key-value pair
extern void free_kv_pair(kv_pair_t *kv_pair);

// Compare a key with the key in a key-value pair, return 1 if matches
extern int kv_pair_matches_key(kv_pair_t *kv_pair, char *key);

// Print a key-value pair
extern void print_kv_pair(kv_pair_t *kv_pair);

#endif
