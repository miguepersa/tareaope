#include "user.h"

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

    htable_add(user->following, userToFollow);
    
}