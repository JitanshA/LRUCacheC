#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "lru_cache.h"
#include <time.h>
#include <stdlib.h>

// Function prototypes for all tests
void test_insert_and_retrieve_single_key_value();
void test_overwrite_existing_key();
void test_insert_beyond_capacity();
void test_retrieve_non_existent_key();
void test_eviction_order();
void test_empty_cache();
void test_single_item_cache();
void test_collision_handling();
void test_large_keys_and_values();
void test_insert_with_empty_key_or_value();
void test_retrieve_most_recently_used();
void test_eviction_with_collision();
void test_large_key_small_cache();
void test_repeated_access_pattern();
void test_multiple_identical_values();
void test_cache_free_behavior();
void test_insert_after_free();
void test_access_after_eviction();
void test_cache_with_small_capacity();
void test_key_to_index_behavior();
void test_resize_cache_up();
void test_resize_cache_down();
void test_resize_cache_same_size();

// Main function to execute all tests
void run_test_lru_cache_basics()
{
    printf("Running LRU Cache Basic Tests...\n");

    test_insert_and_retrieve_single_key_value();
    test_overwrite_existing_key();
    test_insert_beyond_capacity();
    test_retrieve_non_existent_key();
    test_eviction_order();
    test_empty_cache();
    test_single_item_cache();
    test_collision_handling();
    test_large_keys_and_values();
    test_insert_with_empty_key_or_value();
    test_retrieve_most_recently_used();
    test_eviction_with_collision();
    test_large_key_small_cache();
    test_repeated_access_pattern();
    test_multiple_identical_values();
    test_cache_free_behavior();
    test_insert_after_free();
    test_access_after_eviction();
    test_cache_with_small_capacity();
    test_key_to_index_behavior();
    test_resize_cache_up();
    test_resize_cache_down();
    test_resize_cache_same_size();

    printf("Basic tests passed!\n");
}

// Test: Insert and retrieve a single key-value pair
void test_insert_and_retrieve_single_key_value()
{
    LRUCache *cache = lru_cache_create(3);
    assert(cache);

    lru_cache_set(cache, "key1", "value1");
    char *value = lru_cache_get(cache, "key1");
    assert(value && strcmp(value, "value1") == 0);

    lru_cache_free(cache);
    printf("Test Passed: Insert and Retrieve Single Key-Value\n");
}

// Test: Overwrite an existing key with a new value
void test_overwrite_existing_key()
{
    LRUCache *cache = lru_cache_create(3);
    assert(cache);

    lru_cache_set(cache, "key1", "value1");
    lru_cache_set(cache, "key1", "new_value");
    char *value = lru_cache_get(cache, "key1");
    assert(value && strcmp(value, "new_value") == 0);

    lru_cache_free(cache);
    printf("Test Passed: Overwrite Existing Key\n");
}

// Test: Insert keys beyond cache capacity and ensure eviction
void test_insert_beyond_capacity()
{
    LRUCache *cache = lru_cache_create(2);
    assert(cache);

    lru_cache_set(cache, "key1", "value1");
    lru_cache_set(cache, "key2", "value2");
    lru_cache_set(cache, "key3", "value3"); // Evicts "key1"

    assert(lru_cache_get(cache, "key1") == NULL); // "key1" evicted
    assert(strcmp(lru_cache_get(cache, "key2"), "value2") == 0);
    assert(strcmp(lru_cache_get(cache, "key3"), "value3") == 0);

    lru_cache_free(cache);
    printf("Test Passed: Insert Beyond Capacity\n");
}

// Test: Retrieve a non-existent key from the cache
void test_retrieve_non_existent_key()
{
    LRUCache *cache = lru_cache_create(2);
    assert(cache);

    assert(lru_cache_get(cache, "key1") == NULL);

    lru_cache_free(cache);
    printf("Test Passed: Retrieve Non-Existent Key\n");
}

// Test: Eviction order when cache is full
void test_eviction_order()
{
    LRUCache *cache = lru_cache_create(3);
    assert(cache);

    lru_cache_set(cache, "key1", "value1");
    lru_cache_set(cache, "key2", "value2");
    lru_cache_set(cache, "key3", "value3");

    lru_cache_get(cache, "key1");           // Access "key1" to make it MRU
    lru_cache_set(cache, "key4", "value4"); // Evicts "key2"

    assert(lru_cache_get(cache, "key2") == NULL);
    assert(strcmp(lru_cache_get(cache, "key1"), "value1") == 0);
    assert(strcmp(lru_cache_get(cache, "key3"), "value3") == 0);
    assert(strcmp(lru_cache_get(cache, "key4"), "value4") == 0);

    lru_cache_free(cache);
    printf("Test Passed: Eviction Order\n");
}

// Test: Empty cache behavior
void test_empty_cache()
{
    LRUCache *cache = lru_cache_create(2);
    assert(cache);

    assert(lru_cache_get(cache, "key1") == NULL);

    lru_cache_free(cache);
    printf("Test Passed: Empty Cache\n");
}

// Test: Single item cache behavior
void test_single_item_cache()
{
    LRUCache *cache = lru_cache_create(1);
    assert(cache);

    lru_cache_set(cache, "key1", "value1");
    assert(strcmp(lru_cache_get(cache, "key1"), "value1") == 0);

    lru_cache_set(cache, "key2", "value2"); // Evicts "key1"
    assert(lru_cache_get(cache, "key1") == NULL);
    assert(strcmp(lru_cache_get(cache, "key2"), "value2") == 0);

    lru_cache_free(cache);
    printf("Test Passed: Single Item Cache\n");
}

// Test: Collision handling in the cache
void test_collision_handling()
{
    LRUCache *cache = lru_cache_create(3);
    assert(cache);

    lru_cache_set(cache, "key1", "value1");
    lru_cache_set(cache, "keyA", "valueA"); // Assume "key1" and "keyA" collide
    lru_cache_set(cache, "keyB", "valueB");

    assert(strcmp(lru_cache_get(cache, "key1"), "value1") == 0);
    assert(strcmp(lru_cache_get(cache, "keyA"), "valueA") == 0);
    assert(strcmp(lru_cache_get(cache, "keyB"), "valueB") == 0);

    lru_cache_free(cache);
    printf("Test Passed: Collision Handling\n");
}

// Test: Large keys and values
void test_large_keys_and_values()
{
    LRUCache *cache = lru_cache_create(2);
    assert(cache);

    char large_key[1024], large_value[2048];
    memset(large_key, 'a', sizeof(large_key) - 1);
    large_key[sizeof(large_key) - 1] = '\0';

    memset(large_value, 'b', sizeof(large_value) - 1);
    large_value[sizeof(large_value) - 1] = '\0';

    lru_cache_set(cache, large_key, large_value);
    assert(strcmp(lru_cache_get(cache, large_key), large_value) == 0);

    lru_cache_free(cache);
    printf("Test Passed: Large Keys and Values\n");
}

// Test: Insert with empty key or value
void test_insert_with_empty_key_or_value()
{
    LRUCache *cache = lru_cache_create(2);
    assert(cache);

    lru_cache_set(cache, "", "value_empty_key");
    assert(strcmp(lru_cache_get(cache, ""), "value_empty_key") == 0);

    lru_cache_set(cache, "key_empty_value", "");
    assert(strcmp(lru_cache_get(cache, "key_empty_value"), "") == 0);

    lru_cache_free(cache);
    printf("Test Passed: Insert with Empty Key or Value\n");
}

// Test: Retrieve most recently used key
void test_retrieve_most_recently_used()
{
    LRUCache *cache = lru_cache_create(3);
    assert(cache);

    lru_cache_set(cache, "key1", "value1");
    lru_cache_set(cache, "key2", "value2");
    lru_cache_set(cache, "key3", "value3");

    lru_cache_get(cache, "key1");           // Access "key1" to make it MRU
    lru_cache_set(cache, "key4", "value4"); // Evicts "key2"

    assert(lru_cache_get(cache, "key2") == NULL);
    assert(strcmp(lru_cache_get(cache, "key1"), "value1") == 0);

    lru_cache_free(cache);
    printf("Test Passed: Retrieve Most Recently Used Key\n");
}

// Test: Eviction with collision
void test_eviction_with_collision()
{
    LRUCache *cache = lru_cache_create(3);
    assert(cache);

    lru_cache_set(cache, "key1", "value1");
    lru_cache_set(cache, "keyA", "valueA"); // Assume "key1" and "keyA" collide
    lru_cache_set(cache, "keyB", "valueB");

    lru_cache_get(cache, "keyA");           // Access "keyA" to make it MRU
    lru_cache_set(cache, "keyC", "valueC"); // Evicts "key1"

    assert(lru_cache_get(cache, "key1") == NULL);
    assert(strcmp(lru_cache_get(cache, "keyA"), "valueA") == 0);

    lru_cache_free(cache);
    printf("Test Passed: Eviction with Collision\n");
}

// Test: Large key in a small cache
void test_large_key_small_cache()
{
    LRUCache *cache = lru_cache_create(1);
    assert(cache);

    char large_key[512];
    memset(large_key, 'k', sizeof(large_key) - 1);
    large_key[sizeof(large_key) - 1] = '\0';

    lru_cache_set(cache, large_key, "value_large_key");
    assert(strcmp(lru_cache_get(cache, large_key), "value_large_key") == 0);

    lru_cache_free(cache);
    printf("Test Passed: Large Key in Small Cache\n");
}

// Test: Repeated access pattern
void test_repeated_access_pattern()
{
    LRUCache *cache = lru_cache_create(3);
    assert(cache);

    lru_cache_set(cache, "key1", "value1");
    lru_cache_set(cache, "key2", "value2");
    lru_cache_set(cache, "key3", "value3");

    for (int i = 0; i < 100; i++)
    {
        assert(strcmp(lru_cache_get(cache, "key2"), "value2") == 0);
    }

    lru_cache_set(cache, "key4", "value4"); // Evicts "key1"

    assert(lru_cache_get(cache, "key1") == NULL);
    assert(strcmp(lru_cache_get(cache, "key2"), "value2") == 0);

    lru_cache_free(cache);
    printf("Test Passed: Repeated Access Pattern\n");
}

// Test: Multiple identical values
void test_multiple_identical_values()
{
    LRUCache *cache = lru_cache_create(3);
    assert(cache);

    lru_cache_set(cache, "key1", "same_value");
    lru_cache_set(cache, "key2", "same_value");
    lru_cache_set(cache, "key3", "same_value");

    assert(strcmp(lru_cache_get(cache, "key1"), "same_value") == 0);
    assert(strcmp(lru_cache_get(cache, "key2"), "same_value") == 0);
    assert(strcmp(lru_cache_get(cache, "key3"), "same_value") == 0);

    lru_cache_free(cache);
    printf("Test Passed: Multiple Identical Values\n");
}

// Test: Insert after cache is freed
void test_insert_after_free()
{
    LRUCache *cache = lru_cache_create(3);
    assert(cache);

    lru_cache_set(cache, "key1", "value1");
    lru_cache_free(cache);

    // Reinitialize cache
    cache = lru_cache_create(3);
    lru_cache_set(cache, "key2", "value2");

    assert(strcmp(lru_cache_get(cache, "key2"), "value2") == 0);

    lru_cache_free(cache);
    printf("Test Passed: Insert After Free\n");
}

// Test: Access after eviction
void test_access_after_eviction()
{
    LRUCache *cache = lru_cache_create(2);
    assert(cache);

    lru_cache_set(cache, "key1", "value1");
    lru_cache_set(cache, "key2", "value2");
    lru_cache_set(cache, "key3", "value3"); // Evicts "key1"

    assert(lru_cache_get(cache, "key1") == NULL);

    lru_cache_free(cache);
    printf("Test Passed: Access After Eviction\n");
}

// Test: Cache with small capacity
void test_cache_with_small_capacity()
{
    LRUCache *cache = lru_cache_create(1);
    assert(cache);

    lru_cache_set(cache, "key1", "value1");
    assert(strcmp(lru_cache_get(cache, "key1"), "value1") == 0);

    lru_cache_set(cache, "key2", "value2"); // Evicts "key1"
    assert(lru_cache_get(cache, "key1") == NULL);

    lru_cache_free(cache);
    printf("Test Passed: Cache with Small Capacity\n");
}

void test_key_to_index_behavior()
{
    LRUCache *cache = lru_cache_create(10);
    lru_cache_set(cache, "key1", "value1");
    assert(strcmp(lru_cache_get(cache, "key1"), "value1") == 0);

    lru_cache_set(cache, "key2", "value2");
    assert(strcmp(lru_cache_get(cache, "key2"), "value2") == 0);

    lru_cache_free(cache);
}

void test_cache_free_behavior()
{
    LRUCache *cache = lru_cache_create(5);

    lru_cache_set(cache, "key1", "value1");
    lru_cache_set(cache, "key2", "value2");

    assert(lru_cache_get(cache, "key1") != NULL);
    assert(lru_cache_get(cache, "key2") != NULL);

    lru_cache_free(cache);
}

void test_resize_cache_up()
{
    LRUCache *cache = lru_cache_create(2);

    lru_cache_set(cache, "key1", "value1");
    lru_cache_set(cache, "key2", "value2");

    // Resize the cache to a larger capacity
    lru_cache_resize_cache(cache, 4);

    // Ensure all current elements remain
    assert(strcmp(lru_cache_get(cache, "key1"), "value1") == 0);
    assert(strcmp(lru_cache_get(cache, "key2"), "value2") == 0);

    // Add new elements and ensure they fit in the cache
    lru_cache_set(cache, "key3", "value3");
    lru_cache_set(cache, "key4", "value4");

    assert(strcmp(lru_cache_get(cache, "key3"), "value3") == 0);
    assert(strcmp(lru_cache_get(cache, "key4"), "value4") == 0);

    lru_cache_free(cache);
}

void test_resize_cache_down()
{
    LRUCache *cache = lru_cache_create(4);

    lru_cache_set(cache, "key1", "value1");
    lru_cache_set(cache, "key2", "value2");
    lru_cache_set(cache, "key3", "value3");
    lru_cache_set(cache, "key4", "value4");

    // Resize the cache to a smaller capacity
    lru_cache_resize_cache(cache, 2);

    // Ensure the cache evicts the least recently used items
    assert(lru_cache_get(cache, "key1") == NULL); // Evicted
    assert(lru_cache_get(cache, "key2") == NULL); // Evicted
    assert(strcmp(lru_cache_get(cache, "key3"), "value3") == 0);
    assert(strcmp(lru_cache_get(cache, "key4"), "value4") == 0);

    lru_cache_free(cache);
}

void test_resize_cache_same_size()
{
    LRUCache *cache = lru_cache_create(2);

    lru_cache_set(cache, "key1", "value1");
    lru_cache_set(cache, "key2", "value2");

    // Resize the cache to the same capacity
    lru_cache_resize_cache(cache, 2);

    // Ensure all current elements remain
    assert(strcmp(lru_cache_get(cache, "key1"), "value1") == 0);
    assert(strcmp(lru_cache_get(cache, "key2"), "value2") == 0);

    lru_cache_free(cache);
}
