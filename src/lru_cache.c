#include "key_value_pair.h"
#include "lru_cache.h"
#include "node_utils.h"
#include "hash_utils.h"
#include <stdlib.h>
#include <stdio.h>

// Evicts the least recently used block from the cache
static void evict_least_recently_used_block(LRUCache *cache)
{
    if (!cache || !cache->tail)
    {
        return;
    }

    Node *node_to_evict = cache->tail;

    // Find the hash table index for the node to be evicted
    int index = key_to_index(kv_pair_get_key(node_to_evict->kv_pair), cache->capacity);

    // Remove the node from the hash table
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

    // Update the tail pointer of the doubly linked list
    if (node_to_evict->prev)
    {
        node_to_evict->prev->next = NULL;
    }
    cache->tail = node_to_evict->prev;

    // If the cache is empty, update the head pointer as well
    if (cache->tail == NULL)
    {
        cache->head = NULL;
    }

    kv_free_kv_pair(node_to_evict->kv_pair);
    free(node_to_evict);

    cache->size--;
}

// Creates a new LRU cache with the given capacity
LRUCache *lru_cache_create(int capacity)
{
    if (capacity <= 0)
    {
        return NULL;
    }

    LRUCache *cache = calloc(1, sizeof(LRUCache));
    if (!cache)
    {
        return NULL;
    }

    cache->capacity = capacity;
    cache->size = 0;
    cache->hits = 0;
    cache->misses = 0;
    cache->head = NULL;
    cache->tail = NULL;

    // Allocate memory for the hash table
    cache->hash_table = calloc(capacity, sizeof(Node *));
    if (!cache->hash_table)
    {
        free(cache);
        return NULL;
    }

    return cache;
}

// Retrieves the value associated with the given key from the cache
char *lru_cache_get(LRUCache *cache, char *key)
{
    if (!cache || !key)
    {
        return NULL;
    }

    int index = key_to_index(key, cache->capacity);
    Node *node = cache->hash_table[index];

    // Traverse the linked list at the hash table index
    while (node)
    {
        if (kv_pair_matches_key(node->kv_pair, key))
        {
            move_node_to_front(cache, node);
            cache->hits++;
            return kv_pair_get_value(node->kv_pair);
        }

        node = node->next;
    }

    cache->misses++;

    return NULL;
}

// Inserts or updates a key-value pair in the cache
void lru_cache_set(LRUCache *cache, char *key, char *value)
{
    if (!cache || !key || !value)
    {
        return;
    }

    int index = key_to_index(key, cache->capacity);
    Node *node = cache->hash_table[index];

    // Check if the key already exists in the cache
    while (node)
    {
        if (kv_pair_matches_key(node->kv_pair, key))
        {
            kv_pair_set_value(node->kv_pair, value);
            cache->hits++;
            move_node_to_front(cache, node);
            return;
        }

        node = node->next;
    }

    // Evict the least recently used block if the cache is full
    if (cache->size == cache->capacity)
    {
        evict_least_recently_used_block(cache);
    }

    // Create a new key-value pair and node
    kv_pair_t *new_pair = kv_new_kv_pair(key, value);
    if (!new_pair)
    {
        return;
    }

    Node *new_node = calloc(1, sizeof(Node));
    if (!new_node)
    {
        kv_free_kv_pair(new_pair);
        return;
    }

    new_node->kv_pair = new_pair;

    // Insert the new node into the hash table
    new_node->next = cache->hash_table[index];
    if (cache->hash_table[index])
    {
        cache->hash_table[index]->prev = new_node;
    }
    cache->hash_table[index] = new_node;

    // Add the new node to the front of the doubly linked list
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

    cache->misses++;
    cache->size++;
}

// Frees all resources associated with the cache
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

// Print the stats for the cache
void lru_cache_print_stats(LRUCache *cache)
{
    if (!cache)
    {
        return;
    }

    if (cache->misses + cache->hits == 0)
    {
        printf("No requests processed yet.\n");
        return;
    }

    printf("Hits: %d\nMisses: %d\nMiss Rate: %.2f%%\n",
           cache->hits, cache->misses, 100.0 * (double)cache->misses / (cache->misses + cache->hits));
}

void lru_cache_resize_cache(LRUCache *cache, int new_capacity) {
    if (!cache || new_capacity <= 0 || new_capacity == cache->capacity) {
        return;
    }

    // Evict extra nodes if downsizing
    while (cache->size > new_capacity) {
        evict_least_recently_used_block(cache);
    }

    Node **new_hash_table = calloc(new_capacity, sizeof(Node *));
    if (!new_hash_table)
    {
        return;
    }

    // Rehash existing nodes into the new table
    Node *current = cache->head;
    while (current)
    {
        int new_index = key_to_index(kv_pair_get_key(current->kv_pair), new_capacity);
        Node *next_node = current->next;

        // Insert current node into the new hash table
        current->next = new_hash_table[new_index];
        if (new_hash_table[new_index])
        {
            new_hash_table[new_index]->prev = current;
        }
        new_hash_table[new_index] = current;

        current = next_node;
    }

    free(cache->hash_table);
    cache->hash_table = new_hash_table;
    cache->capacity = new_capacity;
}

void lru_cache_reset_stats(LRUCache *cache)
{
    if (!cache)
    {
        return;
    }

    cache->hits = 0;
    cache->misses = 0;
}
