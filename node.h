#ifndef NODE_H
#define NODE_H

#include "user.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    struct node* next;
    User* u;
}Node;

Node *node_init();
void node_destroy(Node*);

#endif