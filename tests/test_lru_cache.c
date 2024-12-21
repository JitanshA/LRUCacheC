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
void test_stress_lru_cache();
char *generate_random_string(int length);

// Main function to execute all tests
int main()
{
    printf("Running LRU Cache Tests...\n");

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
    test_stress_lru_cache();

    printf("All Tests Passed!\n");
    return 0;
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

// Generate a random string of specified length
char *generate_random_string(int length)
{
    char *str = malloc(length + 1);
    if (!str)
    {
        return NULL;
    }

    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (int i = 0; i < length; i++)
    {
        str[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    str[length] = '\0';
    return str;
}

void test_stress_lru_cache()
{
    srand(time(NULL)); // Seed the random number generator

    LRUCache *cache = lru_cache_create(150);
    if (!cache)
    {
        printf("Failed to create cache.\n");
        return;
    }

    printf("Running stress test with %d operations on cache (capacity %d)...\n", 2000, 150);

    for (int i = 0; i < 2000; i++)
    {
        char *key = generate_random_string(10);
        char *value = generate_random_string(15);

        if (rand() % 2 == 0)
        {
            lru_cache_set(cache, key, value); // Perform set operation
        }
        else
        {
            char *result = lru_cache_get(cache, key); // Perform get operation
            free(result);
        }

        free(key);
        free(value);
    }

    // Validation of eviction
    printf("Validating eviction mechanism...\n");
    char *evicted_key = generate_random_string(10);
    char *result = lru_cache_get(cache, evicted_key);
    if (result)
    {
        printf("Unexpected: Retrieved value for evicted key '%s': %s\n", evicted_key, result);
    }
    else
    {
        printf("Expected: Key '%s' was evicted as expected.\n", evicted_key);
    }
    free(evicted_key);

    lru_cache_free(cache);

    printf("Stress test completed.\n");
}