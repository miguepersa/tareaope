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