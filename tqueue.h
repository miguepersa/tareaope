#ifndef TQUEUE_H
#define TQUEUE_H

#include "tweet.h"

typedef struct tnode
{
    struct tnode* next;
    Tweet* t;
}Tnode;

typedef struct tqueue
{
    Tnode *head;
    Tnode *tail;
}Tqueue;

void tqueue_add(Tweet*);


#endif