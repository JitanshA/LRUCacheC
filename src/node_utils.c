#include "node_utils.h"
#include "lru_cache.h" // Include full definition of LRUCache
#include <stdlib.h>

void move_node_to_front(struct LRUCache *cache, Node *node)
{
    if (!cache || !node || cache->head == node)
    {
        return;
    }

    if (node->next)
    {
        node->next->prev = node->prev;
    }
    if (node->prev)
    {
        node->prev->next = node->next;
    }

    if (cache->tail == node)
    {
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

void free_node(Node *node)
{
    if (node)
    {
        free(node);
    }
}
