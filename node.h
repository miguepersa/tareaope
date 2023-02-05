#ifndef NODE_H
#define NODE_H

#include "user.h"

typedef struct node
{
    struct node* next;
    User* u;
}Node;


#endif