#include "twitter.h"

void twitter_init(Twitter *twitter)
{
    char userName[userName_LIMIT];
    char action[32];
    char password[256];

    twitter->loggedUser = NULL;

    int run = 1;

    do
    {
        if (twitter->loggedUser != NULL)
        {
            twitter_feed(t);
        }
        printf("DON'T MISS WHAT'S HAPPENING! LOGIN, SIGNUP OR LEAVE\n");

        scanf("%s\n", action);

        if (strcmp(action, "login") == 0)
        {
            while (1)
            {
                printf("userName: ");
                scanf("%s\n", userName);
                printf("PASSWORD: ");
                scanf("%s\n", password);
                if (twitter_login(t, userName, password))
                {
                    break;
                }
                else
                {
                    printf("Invalid credentials, try again\n");
                }
            }
            
            
        } else if (strcmp(action, "signup") == 0)
        {
            twitter_signup(t);
        } else if (strcmp(action, "leave") == 0)
        {
            run = 0;
            twitter_destroy(t);
        }
        
    }while (run);
            
}

int twitter_login(Twitter *twitter, char* userName, char* password)
{
    User * currentUser = htable_get_user(t->users, userName);
    if (currentUser != NULL)
    {
        if (currentUser->password == hash(password))
        {
            twitter->loggedUser = currentUser;
            return 1;
        }
    }

    return 0;
}

void twitter_feed(Twitter* twitter)
{
    char input[8];

    twitter_print_timeline(twitter->loggedUser);
    int follow = 0;
    User* toFollow = NULL;

    while(1){

        printf("WHAT'S HAPPENING?\n");
        scanf("%s", input);

        if (input[0] == '+' && strlen(input) == 1)
        {
            Tweet * tweet = tweet_init();
            tweet->user = twitter->loggedUser;

            time_t inittime;
            struct tm *info;
            time( &inittime );
            info = localtime( &inittime );

            tweet->day = info->tm_mday;
            tweet->month = info->tm_mon;
            tweet->hour = info->tm_hour;
            tweet->minute = info->tm_min;


            printf("Input the tweet (max 280 chars): ");
            scanf("%s", tweet->content);
            tweet->content[280] = '\0';


        } else if (input[0] == '@' && strlen(input) == 1)
        {
            char userName[userName_LIMIT];
            printf("Give me an userName: ");
            scanf("%s", userName);

            toFollow = htable_get_user(t->users, userName);

            if (toFollow == NULL){
                printf("There's no user with that name\n");

            }else{
                tqueue_print(toFollow->tweets);
                follow = 1;

            }
            
        } else if (strcmp(input, "logout") == 0)
        {
            twitter->loggedUser = NULL;
            break;
        }else if(strcmp(input, "follow") == 0 && follow == 1){
            while(twitter->loggedUser->following[i] != NULL && strcmp(twitter->loggedUser->following[i]->userName , toFollow->userName) == 1){
                 i++;
            }

            if(strcmp(twitter->loggedUser->following[i]->userName , toFollow->userName) == 0){
                printf("You already follow this user\n");
            }else if(twitter->loggedUser->following[i] == NULL){
                user_add_following(twitter->loggedUser, toFollow );
            }

            follow = 0;

        }

    }
    
}

void twitter_signup(Twitter* twitter)
{
    User *user = user_init();
    char buff[256];

    printf("userName: ");
    scanf("%s", user->userName);
    printf("password: ");
    scanf("%s", buff);

    user->password = hash(buff);

    htable_add(twitter->users, user);
}

void twitter_print_timeline(User* user)
{
    Tqueue *printQueue = tqueue_init();

    for(int i =0; i< sizeof(user->following)/sizeof(user->following[0]); i++){
        Tnode* currentFollowingTweet = user->following[i]->tweets->head;
        while(currentFollowingTweet != NULL){
            if(printQueue->size == 0){
                printQueue->head = currentFollowingTweet;
                printQueue->tail = currentFollowingTweet;
                printQueue->size++;
            }
            else{
                Tnode* queueNode = printQueue->head;
                Tnode* oldQueueNode= NULL;
                while(queueNode!= NULL){
                    if(queueNode-> next == NULL)
                    {
                        printQueue->tail->next = queueNode;
                        printQueue->tail = queueNode;
                        queueNode = queueNode->next;
                        continue;
                    }
                    Tweet* queueTweet = queueNode->t;
                    if(queueTweet->month < currentFollowingTweet->t->month || (queueTweet->month > currentFollowingTweet->t->month && queueTweet->day < currentFollowingTweet->t->day) || 
                        (queueTweet->month > currentFollowingTweet->t->month && queueTweet->day > currentFollowingTweet->t->day && queueTweet->hour < currentFollowingTweet->t->hour) ||
                        (queueTweet->month > currentFollowingTweet->t->month && queueTweet->day > currentFollowingTweet->t->day && queueTweet->hour > currentFollowingTweet->t->hour && 
                        queueTweet->minute < currentFollowingTweet->t->minute))
                    {
                        if(oldQueueNode != NULL){
                            oldQueueNode->next = currentFollowingTweet;
                        }
                        currentFollowingTweet->next = queueNode;
                    }
                    oldQueueNode = queueNode;
                    queueNode = queueNode->next;
                }
            }
            currentFollowingTweet = currentFollowingTweet->next;
            
        }
    }
    tqueue_print(printQueue);
}