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

void lru_cache_set(LRUCache *cache, char *key, char *value) {
    if (!cache || !key || !value) {
        return;
    }

    int index = key_to_index(key, cache->capacity);

    Node *node = cache->hash_table[index];

    while (node)
    {
        if (kv_pair_matches_key(key, node->kv_pair))
        {
            kv_pair_set_value(node->kv_pair, value);
            move_node_to_front(cache, node);
            return;
        }

        node = node->next;
    }

    if (cache->size == cache->capacity) {
        evict_least_recently_used_block(cache);
    }

    kv_pair_t *new_pair = kv_new_kv_pair(key, value);
    if (!new_pair) {
        return;
    }

    Node *new_node = calloc(1, sizeof(Node));
    if (!new_node) {
        kv_free_kv_pair(new_pair);
        return;
    }

    new_node->kv_pair = new_pair;

    new_node->next = cache->hash_table[index];
    if (cache->hash_table[index])
    {
        cache->hash_table[index]->prev = new_node;
    }
    cache->hash_table[index] = new_node;

    new_node->next = cache->head;
    new_node->prev = NULL;

    if (cache->head)
    {
        cache->head->prev = new_node;
    }
    cache->head = new_node;

    if (!cache->tail)
    {
        cache->tail = new_node;
    }

    cache->size++;
}

void lru_cache_free(LRUCache *cache)
{
    if (!cache)
    {
        return;
    }

    Node *current = cache->head;
    while (current)
    {
        Node *next = current->next;

        if (current->kv_pair)
        {
            kv_free_kv_pair(current->kv_pair);
        }

        free(current);

        current = next;
    }

    if (cache->hash_table)
    {
        free(cache->hash_table);
    }

    free(cache);
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

unsigned long djb2_hash(const char *key)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *key++))
    {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
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

void evict_least_recently_used_block(LRUCache *cache)
{
    if (!cache || !cache->tail)
    {
        return;
    }

    Node *node_to_evict = cache->tail;

    int index = key_to_index(kv_pair_get_key(node_to_evict->kv_pair), cache->capacity);

    if (cache->hash_table[index] == node_to_evict)
    {
        cache->hash_table[index] = node_to_evict->next;
    }
    else
    {
        if (node_to_evict->prev)
        {
            node_to_evict->prev->next = node_to_evict->next;
        }
        if (node_to_evict->next)
        {
            node_to_evict->next->prev = node_to_evict->prev;
        }
    }

    if (node_to_evict->prev)
    {
        node_to_evict->prev->next = NULL;
    }
    cache->tail = node_to_evict->prev;

    if (cache->tail == NULL)
    {
        cache->head = NULL;
    }

    kv_free_kv_pair(node_to_evict->kv_pair);
    free(node_to_evict);

    cache->size--;
}
