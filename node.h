#ifndef NODE_H
#define NODE_H

typedef struct user User;

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    struct node* next;
    User* user;
}Node;

Node *node_init();
void node_destroy(Node*);

#endif