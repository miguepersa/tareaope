/*Archivo con las funciones de la estructura Tweet
Contenido:
    tweet_init: función de inicializacion del tweet.
    tweet_print: función para imprimir el contenido del Tweet correspondiente.
    Lista de meses.*/

#include "tweet.h"

char * MONTHS[] = {"JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC"};

/*tweet_init: reserva el espacio de memoria correspondiente para el tamano del Tweet.
En caso de ser NULL, devuelve mensaje de error. En caso contrario, asigna e inicializa los atributos correspondientes*/

Tweet *tweet_init()
{
    Tweet *tweet = (Tweet*) malloc(sizeof(Tweet));
    if (tweet == NULL)
    {
        printf("Tweet: malloc error\n");
    }
    tweet->u = NULL;
    return tweet;
}

/*tweet_print: a traves del Tweet dado, esta funcion se encarga de imprimir el nombre del usuario del Tweet, seguido de su contenido y finalmente, la fecha de
la publicacion.*/

void tweet_print(Tweet* tweet){
    printf("@%s:\"%s\"\n",tweet->u->userName, tweet->content);
    printf("%s %d, %d:%d\n",MONTHS[tweet->month-1], tweet->day,tweet->hour,tweet->minute);
    printf("______________________________\n");
}
