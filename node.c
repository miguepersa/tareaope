#include "node.h"

Node *node_init()
{
    Node *node = (Node*) malloc(sizeof(Node));
    if (node == NULL)
    {
        printf("Node: Malloc error\n");
        return NULL;
    }

    node->next = NULL;
    node->user = NULL;
    return node;

}

void node_destroy(Node* node)
{
    /*user_destroy(node->user); POR AHORA*/
    free(node);
}