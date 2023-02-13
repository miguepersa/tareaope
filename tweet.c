#include "tweet.h"

Tweet *tweet_init()
{
    Tweet *tweet = (Tweet*) malloc(sizeof(Tweet));
    if (tweet == NULL)
    {
        printf("Tweet: malloc error\n");
    }
    tweet->user = NULL;
    return tweet;
}

void tweet_print(Tweet* tweet){
    printf("%s:\n", tweet->user->userName);
    printf("'%s:\n'",tweet->content);
    printf("%d, %d, %d, %d\n",tweet->month, tweet->day,tweet->hour,tweet->minute);

}
