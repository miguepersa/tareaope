/*Archivo con las funciones de la estructura HTable
Contenido:
    htable_init: función de inicializacion de tabla de hash.
    htable_add: función para agregar usuario en la tabla de hash.
    htable_get_user: función que retorna al usuario buscado.
    htable_destroy: función que destruye una tabla de hash, liberando espacio.
    hash: función de hash que se aplicara a la contraseña y la tabla de usuarios.*/

#include "htable.h"

/*htable_init: esta funcion reserva un espacio de memoria de tamano respectivo, para crear la tabla de hash correspondiente. Luego, se encarga de que
cada bucket de la tabla de hash sea NULL, para inicializar cada uno.*/

Htable *htable_init()
{
    int i;
    Htable *newTable = (Htable *)malloc(sizeof(Htable));
    if (newTable == NULL)
    {
        printf("Htable: Malloc error");
        return NULL;
    }
    newTable->size = 0;

    for (i = 0; i < HTABLE_LIMIT; i++)
    {
        newTable->table[i] = NULL;
    }
    

    return newTable;
}

/*htable_add: a través de una clave de hash que obtendremos a partir del atributo nombre del usuario dado, otorgaremos una posición/bucket para el usuario mencionado.
Cada bucket actúa como una lista enlazada.
Si la posición correspondiente esta vacía, lo colocaremos en tal posición. En caso contrario, el usuario en cuestión será asignado como el siguiente al elemento ya ubicado
en el bucket, colocándolo al final de esa lista.*/

void htable_add(Htable *currentTable, User *user)
{
    int pos = hash(user->userName);
    Node *node = node_init();
    node->user = user;
    
    if (currentTable->table[pos] == NULL)
    {
        currentTable->table[pos] = node;
    }
    else
    {
        Node *aux = currentTable->table[pos];
        while (aux->next != NULL)
        {
            aux = aux->next;
        }
        aux->next = node;
    }

    currentTable->size++;
}

/*htable_get_user: a traves de la clave de hash unica creada por el nombre del usuario que se desea obtener, podemos el bucket correspondiente a tal clave.
Si se obtiene NULL, significa que no existe tal usuario. En caso contrario, procedemos a comparar los nombres de los elementos del bucket, recorriendo a sus sucesores*/

User *htable_get_user(Htable *currentTable, char *name)
{
    
    int i = hash(name);

    Node *aux = currentTable->table[i];

    if (aux == NULL)
    {
        return NULL;
    }

    while (strcmp(name, aux->user->userName) != 0 && aux->next != NULL)
    {
        aux = aux->next;
    }

    if (strcmp(name, aux->user->userName) == 0)
    {
        return aux->user;
    }
    
    return NULL;
    
}

/*htable_destroy: recorre la tabla, lista por lista y luego nodo por nodo, llamando a node_destroy. Finalment, libera el espacio utilizado anteriormente por la tabla de hash */

void htable_destroy(Htable *currentTable)
{
    Node *aux;
    int i; 
    
    for (i = 0; i < HTABLE_LIMIT && currentTable->size > 0; i++)
    {
        while (currentTable->table[i] != NULL)
        {
            aux = currentTable->table[i];
            currentTable->table[i] = currentTable->table[i]->next;
            node_destroy(aux);
            currentTable->size--;
        }
    }

    free(currentTable);
    
}

/*hash: toma el valor ASCII de cada caracter de la contraseña introducida, sumandolos. Finalmente, se obtiene el modulo de la clave con respecto al
numero de buckets deseados y se obtiene la clave de hash*/

int hash(char *s)
{
    int i;
    int n = strlen(s);
    int hashedValue = 0;

    for (i = 0; i < n; i++)
    {
        hashedValue = hashedValue + (int)s[i];
    }

    hashedValue = hashedValue % HTABLE_LIMIT;

    return hashedValue;
}