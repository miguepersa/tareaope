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
    Tqueue* q = tnode_init();
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

void tqueue_add(Tqueue* q, Tweet* t)
{
    Tnode *aux = (Tnode*) malloc(sizeof(Tnode));
    aux->t = t;
    aux->next = q->head;
    q->head = aux;
    if (q->size == 0)
    {
        q->tail = aux;
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