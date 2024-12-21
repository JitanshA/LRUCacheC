#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include "key_value_pair.h"

typedef struct LRUCache LRUCache;

// Create a new LRU cache with a fixed capacity
extern LRUCache *lru_cache_create(int capacity);

// Get the value associated with a key
extern char *lru_cache_get(LRUCache *cache, char *key);

// Set a key-value pair in the cache
extern void lru_cache_set(LRUCache *cache, char *key, char *value);

// Free all resources associated with the LRU cache
extern void lru_cache_free(LRUCache *cache);

#endif // LRU_CACHE_H