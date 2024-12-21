#ifndef NODE_UTILS_H
#define NODE_UTILS_H

#include "key_value_pair.h"

struct LRUCache;

typedef struct Node
{
    struct Node *next;
    struct Node *prev;
    kv_pair_t *kv_pair;
} Node;

void move_node_to_front(struct LRUCache *cache, Node *node);
void free_node(Node *node);

#endif // NODE_UTILS_H
