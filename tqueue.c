#include "tqueue.h"

Tnode *tnode_init()
{
    Tnode* n = (Tnode*) malloc(sizeof(Tnode));
    if (n == NULL)
    {
        printf("Tnode: Malloc error\n");
        return NULL;
    }
    n->next = NULL;
    n->t = NULL;
    return n;
}

void tnode_destroy(Tnode* n)
{
    free(n->t);
    free(n);
}

Tqueue* tqueue_init()
{
    Tqueue* q = (Tqueue*) malloc(sizeof(Tqueue));
    
    if (q == NULL)
    {
        printf("Tqueue: Malloc Error\n");
        return NULL;
    }
    q->size = 0;
    q->head = NULL;
    q->tail = NULL;
    return q;
}

void tqueue_add(Tqueue* queue, Tweet* tweet)
{
    Tnode *newnode = (Tnode*) malloc(sizeof(Tnode));
    newnode->t = tweet;

    if (q->size == 0)
    { 
        q->head = newnode;
        q->tail = newnode;
    }else{
        q->tail->next = newnode;
        q->tail = newnode;
    }

    q->size++;
    
}

void tqueue_destroy(Tqueue* q)
{
    Tnode* aux;
    while (q->size > 0)
    {
        aux = q->head;
        q->head = q->head->next;
        tnode_destroy(aux);
        q->size--;
    }
    free(q);
}

void tqueue_print(Tqueue* q)
{
    Tnode* current = q->head;
    while(current != NULL){
        tweet_print(current->t);
        printf("\n");
        current = current->next;
    }
}