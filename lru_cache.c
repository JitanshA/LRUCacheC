#include "lru_cache.h"
#include "key_value_pair.h"
#include <stdlib.h>

typedef struct Node {
    struct Node *next;
    struct Node *prev;
    kv_pair_t *kv_pair;
} Node;

typedef struct LRUCache {
    int capacity;
    int size;
    Node *head;
    Node *tail;
    Node **hash_table;
} LRUCache;

LRUCache *lru_cache_create(int capacity) {
    if (capacity <= 0) {
        return NULL;
    }

    LRUCache *cache = calloc(1, sizeof(LRUCache));

    if (!cache) {
        return NULL;
    }

    cache->capacity = capacity;
    cache->size = 0;
    cache->head = NULL;
    cache->tail = NULL;

    cache->hash_table = calloc(capacity, sizeof(Node *));
    if (!cache->hash_table) {
        free(cache);
        return NULL;
    }

    return cache;
}

char *lru_cache_get(LRUCache *cache, char *key);

void lru_cache_set(LRUCache *cache, char *key, char *value);

void lru_cache_free(LRUCache *cache);