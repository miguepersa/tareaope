#include "tqueue.h"

Tnode *tnode_init()
{
    Tnode* tnode = (Tnode*) malloc(sizeof(Tnode));
    if (tnode == NULL)
    {
        printf("Tnode: Malloc error\n");
        return NULL;
    }
    tnode->next = NULL;
    tnode->tweet = NULL;
    return tnode;
}

void tnode_destroy(Tnode* tnode)
{
    free(tnode->tweet);
    free(tnode);
}

Tqueue* tqueue_init()
{
    Tqueue* queue = (Tqueue*) malloc(sizeof(Tqueue));
    
    if (queue == NULL)
    {
        printf("Tqueue: Malloc Error\n");
        return NULL;
    }
    queue->size = 0;
    queue->head = NULL;
    queue->tail = NULL;
    return queue;
}

void tqueue_add(Tqueue* queue, Tweet* tweet)
{
    Tnode *newNode = (Tnode*) malloc(sizeof(Tnode));
    newNode->tweet = tweet;

    if (queue->size == 0)
    { 
        queue->head = newNode;
        queue->tail = newNode;
    }else{
        queue->tail->next = newNode;
        queue->tail = newNode;
    }

    queue->size++;
    
}

void tqueue_destroy(Tqueue* queue)
{
    Tnode* aux;
    while (queue->size > 0)
    {
        aux = queue->head;
        queue->head = queue->head->next;
        tnode_destroy(aux);
        queue->size--;
    }
    free(queue);
}

void tqueue_print(Tqueue* queue)
{
    Tnode* current = queue->head;
    while(current != NULL){
        tweet_print(current->tweet);
        printf("\n");
        current = current->next;
    }
}