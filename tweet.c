#include "tweet.h"

char * MONTHS[] = {"JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC"};

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

void tweet_print(Tweet* tweet){
    printf("@%s:\"%s\"\n",tweet->u->userName, tweet->content);
    printf("%s %d, %d:%d\n",MONTHS[tweet->month-1], tweet->day,tweet->hour,tweet->minute);
    printf("______________________________\n");
}
