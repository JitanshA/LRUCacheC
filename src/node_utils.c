#include "node_utils.h"
#include "lru_cache.h" // Include full definition of LRUCache
#include <stdlib.h>
#include <time.h>

// Moves a node to the front of the doubly linked list in the cache
void move_node_to_front(struct LRUCache *cache, Node *node)
{
    if (!cache || !node || cache->head == node)
    {
        return;
    }

    // Update the next pointer of the previous node
    if (node->next)
    {
        node->next->prev = node->prev;
    }
    // Update the prev pointer of the next node
    if (node->prev)
    {
        node->prev->next = node->next;
    }

    // Update the tail pointer if the node is the tail
    if (cache->tail == node)
    {
        cache->tail = node->prev;
    }

    // Set the node as the new head
    node->next = cache->head;
    node->prev = NULL;

    if (cache->head)
    {
        cache->head->prev = node;
    }

    cache->head = node;

    // If the cache was empty, update the tail pointer
    if (!cache->tail)
    {
        cache->tail = node;
    }
}

// Frees the memory associated with a node
void free_node(Node *node)
{
    if (node)
    {
        free(node);
    }
}
