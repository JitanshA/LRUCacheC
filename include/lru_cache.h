#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include "key_value_pair.h"
#include "node_utils.h"

#define DEFAULT_EXPIRATION_TIME 7200

typedef struct LRUCache
{
    int capacity;
    int size;
    int hits;
    int misses;
    Node *head;
    Node *tail;
    Node **hash_table;
} LRUCache;

// Create a new LRU cache with a fixed capacity
extern LRUCache *lru_cache_create(int capacity);

// Get the value associated with a key
extern char *lru_cache_get(LRUCache *cache, char *key);

// Set a key-value pair in the cache
extern void lru_cache_set(LRUCache *cache, char *key, char *value);

// Free all resources associated with the LRU cache
extern void lru_cache_free(LRUCache *cache);

// Method to print the stats for the cache
extern void lru_cache_print_stats(LRUCache *cache);

extern void lru_cache_resize_cache(LRUCache *cache, int new_capacity);

extern void lru_cache_reset_stats(LRUCache *cache);

extern void lru_cache_set_with_expiration(LRUCache *cache, char *key, char *value, int ttl_seconds);

#endif // LRU_CACHE_H
