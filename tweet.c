#include "tweet.h"

Tweet *tweet_init()
{
    Tweet *t = (Tweet*) malloc(sizeof(Tweet));
    if (t == NULL)
    {
        printf("Tweet: malloc error\n");
    }
    t->u = NULL;
    return t;
}

void tweet_print(Tweet* tweet){
    printf("%s:\n", tweet->u->username);
    printf("'%s:\n'",tweet->contenido);
    printf("%d, %d, %d, %d\n",tweet->month, tweet->day,tweet->hour,tweet->minute);

}
