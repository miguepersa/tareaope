/*Archivo con las funciones de las estructuras Tqueue y Tnode
Contenido:
    tnode_init: función de inicializacion del nodo Tnode
    tnode_destroy: función para eliminar al nodo Tnode.
    tqueue_init: función de inicializacion de la cola Tqueue.
    tqueue_add: función que agrega un tweet a la cola Tqueue.
    tqueue_destroy: función que elimina a la cola Tqueue y su contenido.
    tqueue_print: funcion que imprime el contenido de los tweets almacenados en la cola Tqueue.*/

#include "tqueue.h"

/*tnode_init: reserva el espacio de memoria correspondiente para el Tnode.
Si es NULL, devuelve mensaje de error. En caso contrario, asignan e inicializan los atributos correspondientes.*/

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

/*tnode_destroy: libera espacio del contenido del nodo y finalmente, libera el espacio del nodo en cuestion.*/

void tnode_destroy(Tnode* tnode)
{
    free(tnode->tweet);
    free(tnode);
}

/*tqueue_init: reserva el espacio correspondiente para la cola Tqueue.
Si es NULL, devuelve mensaje de error. En caso contrario, se asignan e inicializan los atributos correspondientes a la cola Tqueue. */

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

/*tqueue_add: se crea un nuevo nodo que sera el recipiente del tweet que se desea agregar a la cola Tqueue. Si Tqueue esta vacia, su nueva cola y cabeza seran el nuevo nodo.
En caso contrario, el nuevo tweet se ubicara en la cola de la Tqueue, al final.*/

void tqueue_add(Tqueue* queue, Tweet* tweet)
{
    Tnode *newNode = tnode_init();
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

/*tqueue_destroy: recorre la cola Tqueue desde la cabeza, destruyendo sus nodo uno a uno, a traves de sus sucesores.*/

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

/*tqueue_print: recorre la cola Tqueue desde la cabeza, imprimiendo el contenido de los tweets que almacena y desplazandose a traves de sus sucesores.
Esto permite facilmente la impresion desde tweet mas antiguo a mas reciente. */

void tqueue_print(Tqueue* queue)
{
    Tnode* current = queue->head;
    while(current != NULL){
        tweet_print(current->tweet);
        printf("\n");
        current = current->next;
    }
}