#include "htable.h"

Htable *htable_init()
{
    Htable *newTable = (Htable *)malloc(sizeof(Htable));
    if (newTable == NULL)
    {
        printf("Htable: Malloc error");
        return NULL;
    }
    newTable->size = 0;
    return newTable;
}

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
    } else {
        return NULL;
    }
    
}

void htable_destroy(Htable *currentTable)
{
    Node *aux;
    int i; 
    
    for (i = 0; i < HTABLE_LIMIT; i++)
    {
        aux = currentTable->table[i];
        while (aux != NULL)
        {
            node_destroy(aux);
            aux = currentTable->table[i];
            currentTable->table[i] = currentTable->table[i]->next;
        }

    }

    free(currentTable);
    
}


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