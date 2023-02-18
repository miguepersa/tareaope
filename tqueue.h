/*Archivo con las definiciones de las estructuras Tnode y Tqueue*/

#ifndef TQUEUE_H
#define TQUEUE_H

#include <stdlib.h>
#include <stdio.h>

#include "tweet.h"

typedef struct tnode
{
    struct tnode* next;
    Tweet* tweet;
}Tnode;

Tnode *tnode_init();
void tnode_destroy(Tnode*);


typedef struct tqueue
{
    Tnode *head;
    Tnode *tail;
    int size;
}Tqueue;

Tqueue* tqueue_init();
void tqueue_add(Tqueue*,Tweet*);
void tqueue_print(Tqueue*);
void tqueue_destroy(Tqueue*);

#endif