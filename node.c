#include "node.h"

Node *node_init()
{
    Node *n = (Node*) malloc(sizeof(Node));
    if (n == NULL)
    {
        printf("Node: Malloc error\n");
        return NULL;
    }

    n->next = NULL;
    n->u = NULL;
    return n;

}

void node_destroy(Node* n)
{
    user_destroy(n->u);
    free(n);
}