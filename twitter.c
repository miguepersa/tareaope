#include "twitter.h"

void twitter_init(Twitter *twitter)
{
    twitter->users = htable_init();
    twitter->tweets = tqueue_init();
    twitter->loggedUser = NULL;
    char userName[USERNAME_LIMIT];
    char action[32];
    char password[256];

    twitter->loggedUser = NULL;

    int run = 1;

    do
    {
        if (twitter->loggedUser != NULL)
        {
            twitter_feed(twitter);
        }
        printf("DON'T MISS WHAT'S HAPPENING! LOGIN, SIGNUP OR LEAVE\n");

        scanf("%s", action);

        if (strcmp(action, "login") == 0)
        {
            while (1)
            {
                printf("userName: ");
                scanf("%s", userName);
                printf("PASSWORD: ");
                scanf("%s", password);
                if (twitter_login(twitter, userName, password))
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
            twitter_signup(twitter);
        } else if (strcmp(action, "leave") == 0)
        {
            run = 0;
            twitter_destroy(twitter);
        }
        
    }while (run);
            
}

int twitter_login(Twitter *twitter, char* userName, char* password)
{
    User * currentUser = htable_get_user(twitter->users, userName);
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
        printf("%d\n",follow);
        scanf("%s", input);

        if (input[0] == '+' && strlen(input) == 1)
        {
            Tweet * tweet = tweet_init();

            time_t inittime;
            struct tm *info;
            time( &inittime );
            info = localtime( &inittime );

            tweet->day = info->tm_mday;
            tweet->month = info->tm_mon;
            tweet->hour = info->tm_hour;
            tweet->minute = info->tm_min;


            printf("Input the tweet (max 280 chars): ");
            fgets(tweet->content, MAX_TWEET, stdin);
            tweet->content[280] = '\0';
            printf("%s", tweet->content);
            scanf(" ");
            tqueue_add(twitter->loggedUser->tweets, tweet);


        } else if (input[0] == '@' && strlen(input) == 1)
        {
            char userName[USERNAME_LIMIT];
            printf("Give me an userName: ");
            scanf("%s", userName);

            toFollow = htable_get_user(twitter->users, userName);

            if (toFollow == NULL){
                printf("There's no user with that name\n");

            }else{
                printf("@%s\n", toFollow->userName);
                tqueue_print(toFollow->tweets);
                follow = 1;

            }
            
            

        } else if (strcmp(input, "logout") == 0)
        {
            twitter->loggedUser = NULL;
            break;
        }else if(strcmp(input, "follow") == 0 && follow == 1){
            if (htable_get_user(twitter->loggedUser->following, toFollow->userName) != NULL)
            {
                printf("Already following user @%s\n", toFollow->userName);
            } else
            {
                htable_add(twitter->loggedUser->following, toFollow);
                twitter->loggedUser->followed++;
                printf("Now you follow @%s!\n",toFollow->userName);
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
    int i;

    for(i =0; i< user->following->size ; i++){
        Tnode* currentFollowingTweet = user->following->table[i]->user->tweets->head;
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
                    Tweet* queueTweet = queueNode->tweet;
                    if(queueTweet->month < currentFollowingTweet->tweet->month || (queueTweet->month > currentFollowingTweet->tweet->month && 
                        queueTweet->day < currentFollowingTweet->tweet->day) || (queueTweet->month > currentFollowingTweet->tweet->month && 
                        queueTweet->day > currentFollowingTweet->tweet->day && queueTweet->hour < currentFollowingTweet->tweet->hour) ||
                        (queueTweet->month > currentFollowingTweet->tweet->month && queueTweet->day > currentFollowingTweet->tweet->day 
                        && queueTweet->hour > currentFollowingTweet->tweet->hour && queueTweet->minute < currentFollowingTweet->tweet->minute))
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

void twitter_destroy(Twitter* twitter)
{
    htable_destroy(twitter->users);
}