#include "htable.h"

Htable *htable_init()
{
    Htable* t = (Htable*) malloc(sizeof(Htable));
    if (t == NULL)
    {
        printf("Htable: Malloc error");
        return NULL;
    }
    t->size = 0;
    return t;
}

void htable_add(Htable* t, User* u)
{
    int pos = hash(u->username);
    Node* n = node_init();
    n->u = u;
    
    if (t->tabla[pos] == NULL)
    {
        t->tabla[pos] = n;
    }
    else
    {
        Node* aux = t->tabla[pos];
        while (aux->next != NULL)
        {
            aux = aux->next;
        }
        aux->next = n;
    }

    t->size++;
}

void htable_destroy(Htable* t)
{
    int i;
    Node* aux;

    for (i = 0; i < HTABLE_LIMIT; i++)
    {
        aux = t->tabla[i];
        while (t->tabla[i] != NULL)
        {
            node_destroy(aux);
            aux = t->tabla[i];
            t->tabla[i] = t->tabla[i]->next;
        }
        
    }
    free(t);
    
}

int hash(char* s)
{
    int i;
    int n = strlen(s);
    int h = 0;

    for (i = 0; i < n; i++)
    {
        h = h + (int) s[i];
    }

    h = h%HTABLE_LIMIT;

    return h;
}