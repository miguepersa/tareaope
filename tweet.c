#include "tweet.h"

Tweet *tweet_init()
{
    Tweet *tweet = (Tweet*) malloc(sizeof(Tweet));
    if (tweet == NULL)
    {
        printf("Tweet: malloc error\n");
    }
    return tweet;
}

void tweet_print(Tweet* tweet){
    printf("%s:\n",tweet->content);
    printf("%d, %d, %d, %d\n",tweet->month, tweet->day,tweet->hour,tweet->minute);

}
