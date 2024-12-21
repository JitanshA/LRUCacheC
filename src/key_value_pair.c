#include "kv_pair.h"
#include <stdlib.h>
#include <string.h>

kv_pair_t *kv_new_kv_pair(char *key, char *value)
{
    kv_pair_t *kv_pair = calloc(1, sizeof(kv_pair_t));
    if (!kv_pair)
    {
        return NULL;
    }

    kv_pair->key = strdup(key);
    if (!kv_pair->key)
    {
        free(kv_pair);
        return NULL;
    }

    kv_pair->value = strdup(value);
    if (!kv_pair->value)
    {
        free(kv_pair->key);
        free(kv_pair);
        return NULL;
    }

    return kv_pair;
}

char *kv_pair_get_value(kv_pair_t *kv_pair)
{
    if (!kv_pair)
    {
        return NULL;
    }
    
    return kv_pair->value;
}

void kv_pair_set_value(kv_pair_t *kv_pair, char *new_value)
{
    if (!kv_pair)
    {
        return;
    }

    char *new_value_dup = strdup(new_value);
    if (!new_value_dup)
    {
        return;
    }

    free(kv_pair->value);
    kv_pair->value = new_value_dup;
}

char *kv_pair_get_key(kv_pair_t *kv_pair)
{
    if (!kv_pair)
    {
        return NULL;
    }

    return kv_pair->key;
}

void kv_free_kv_pair(kv_pair_t *kv_pair)
{
    if (!kv_pair) {
        return;
    }

    free(kv_pair->key);
    free(kv_pair->value);
    free(kv_pair);
}

int kv_pair_matches_key(kv_pair_t *kv_pair, char *key)
{
    if (!kv_pair || !key) {
        return 0;
    }

    return strcmp(kv_pair->key, key) == 0;
}

void kv_print_kv_pair(kv_pair_t *kv_pair)
{
    if (!kv_pair || !kv_pair->key || !kv_pair->value)
    {
        printf("Invalid key-value pair.\n");
        return;
    }

    printf("Key: %s, Value: %s\n", kv_pair->key, kv_pair->value);
}
