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

char *lru_cache_get(LRUCache *cache, char *key) {
    if (!cache || !key) {
        return NULL;
    }

    int index = key_to_index(key, cache->capacity);

    Node *node = cache->hash_table[index];

    while(node) {
        if (kv_pair_matches_key(key, node->kv_pair)) {
            move_node_to_front(cache, node);
            return kv_pair_get_value(node->kv_pair);
        }

        node = node->next;
    }

    return NULL;
}

void lru_cache_set(LRUCache *cache, char *key, char *value);

void lru_cache_free(LRUCache *cache);

// A simple mapping function to get the index of key in cache
// Will replace later with a more complex function, commonly used in a cache
int key_to_index(char *key, int capacity)
{
    if (!key || capacity <= 0) {
        return -1;
    }

    int sum = 0;
    while (*key)
    {
        sum += *key;
        key++;
    }

    return sum % capacity;
}

void move_node_to_front(LRUCache *cache, Node *node) {
    if (!cache || !node || cache->head == node) {
        return;
    }

    if (node->next) {
        node->next->prev = node->prev;
    }
    if (node->prev) {
        node->prev->next = node->next;
    }

    if (cache->tail == node) {
        cache->tail = node->prev;
    }

    node->next = cache->head;
    node->prev = NULL;

    if (cache->head)
    {
        cache->head->prev = node;
    }

    cache->head = node;

    if (!cache->tail)
    {
        cache->tail = node;
    }
}