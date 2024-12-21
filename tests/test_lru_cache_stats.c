#include <stdio.h>
#include <assert.h>
#include "lru_cache.h"

void test_empty_cache_stats()
{
    LRUCache *cache = lru_cache_create(3);
    assert(lru_cache_get(cache, "key1") == NULL);
    lru_cache_print_stats(cache); // Misses: 1, Hits: 0
    lru_cache_free(cache);
}

void test_cache_hit_and_miss()
{
    LRUCache *cache = lru_cache_create(3);
    lru_cache_set(cache, "key1", "value1");
    lru_cache_set(cache, "key2", "value2");
    assert(lru_cache_get(cache, "key1") != NULL); // Hit
    assert(lru_cache_get(cache, "key3") == NULL); // Miss
    lru_cache_print_stats(cache);                 // Hits: 1, Misses: 1
    lru_cache_free(cache);
}

void test_eviction()
{
    LRUCache *cache = lru_cache_create(2);
    lru_cache_set(cache, "key1", "value1");
    lru_cache_set(cache, "key2", "value2");
    lru_cache_set(cache, "key3", "value3");       // Evicts key1
    assert(lru_cache_get(cache, "key1") == NULL); // Miss
    assert(lru_cache_get(cache, "key2") != NULL); // Hit
    lru_cache_print_stats(cache);                 // Hits: 1, Misses: 1
    lru_cache_free(cache);
}

void test_statistics_output()
{
    LRUCache *cache = lru_cache_create(2);
    lru_cache_set(cache, "key1", "value1");
    lru_cache_set(cache, "key2", "value2");
    lru_cache_get(cache, "key3"); // Miss
    lru_cache_get(cache, "key1"); // Hit
    lru_cache_print_stats(cache); // Hits: 1, Misses: 1
    lru_cache_free(cache);
}

void run_test_lru_cache_stats()
{
    printf("Running Stats tests for LRU Cache...\n");
    test_empty_cache_stats();
    test_cache_hit_and_miss();
    test_eviction();
    test_statistics_output();
    printf("Stats tests passed!\n");
}
