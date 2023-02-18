/*Archivo con las funciones de la estructura User
Contenido:
    user_init: función de inicializacion del usuario.
    user_add_tweet: función para agregar un tweet del usuario correspondiente.
    user_destroy: función que elimina al usuario correspondiente.
    user_add_following: función para agregar un usuario a la tabla de seguidores correspondiente.*/

#include "user.h"

/*user_init: reserva el espacio de memoria correspondiente para el tamano del usuario.
En caso de ser NULL, devuelve mensaje de error. En caso contrario, asigna e inicializa los atributos correspondientes*/

User* user_init()
{
    User *user = (User*) malloc(sizeof(User));
    if (user == NULL)
    {
        printf("User: malloc error\n");
        return NULL;
    }
    user->tweets = tqueue_init();
    user->followed = 0;
    user->following = htable_init();


    return user;
}

/*user_add_tweet: a traves de la funcion tqueue_add, se agrega el Tweet correspondiente la cola de tweets*/

void user_add_tweet(User* user, Tweet* tweet)
{
    tqueue_add(user->tweets, tweet);
}

/*user_destroy: se recorre la cola de tweets del usuario, liberando espacio uno a uno. Luego, se libera el espacio de la cola de Tweets, de la tabla de seguidos y finalmente,
el espacio correspondiente al usuario.*/

void user_destroy(User* user)
{
    while (user->tweets->head != NULL)
    {
        Tnode* aux = user->tweets->head;
        user->tweets->head = user->tweets->head->next;
        free(aux);
    }
    free(user->tweets);
    free(user->following);
    free(user);
}

/*user_add_following: se agrega un usuario a seguir en la tabla correspondiente de seguidos del usuario, a traves de la funcion htable_add */

void user_add_following(User* user, User* userToFollow )
{

    htable_add(user->following, userToFollow);
    
}