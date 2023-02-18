/*Archivo con las funciones de la estructura HTable
    Contenido:
        node_init: función de inicializacion de la estructura Node.
        node_destroy: función para eliminar un nodo en especifico.*/

#include "node.h"

/*node_init: reserva espacio de memoria correspondiente al tamano de un Node. De ser NULL, se devuelve un error.
Finalmente, se inicializan los atributos del Node.*/

Node *node_init()
{
    Node *node = (Node*) malloc(sizeof(Node));
    if (node == NULL)
    {
        printf("Node: Malloc error\n");
        return NULL;
    }

    node->next = NULL;
    node->user = NULL;
    return node;

}

 /*node_destroy: hace llamado a la funcion user_destroy, para eliminar el contenido del Node. Finalmente, libera el espacio del Node en cuestion.*/

void node_destroy(Node* node)
{
    user_destroy(node->user);
    free(node);
}