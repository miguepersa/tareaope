#include "user.h"

User* user_init()
{
    int i;
    User *user = (User*) malloc(sizeof(User));
    if (user == NULL)
    {
        printf("User: malloc error\n");
        return NULL;
    }
    user->tweets = tqueue_init();
    user->followed = 0;

    for (i = 0; i < 256; i++)
    {
        user->following[i] = NULL;
    }
    

    return user;
}

void user_add_tweet(User* user, Tweet* tweet)
{
    tqueue_add(user->tweets, tweet);
}

void user_destroy(User* user)
{
    tqueue_destroy(user->tweets);
    free(user);
}

void user_add_following(User* user, User* userToFollow )
{
    int i = 0;

    while(user->following[i] != NULL && i < 257){
        i++;
    }
    
    if(user->following[i] == NULL){
        user->following[i] =userToFollow;

    }else if (i == 257)
    {
        printf("Reached max capacity\n");

    }
    

}