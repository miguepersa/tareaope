/*Archivo con las funciones de la estructura Twitter
Contenido:
    twitter_init: función de inicializacion de la estructura Twitter.
    twitter_login: función para ingresar en la cuenta correspondiente de Twitter.
    twitter_feed: función para iniciar el feed de Twitter.
    twitter_signup: función de registro de Twitter.
    twitter_print_timeline: funcion de impresion del timeline del usuario.
    twitter_destroy: funcion para eliminar Twitter.
    clean_stdin: funcion de limpieza de buffer*/

#include "twitter.h"

/*twitter_init: se inicializan las estructuras necesarias a traves de htable_init y tqueue_init, asi como colocamos las restricciones necesarias.
Se reciben los siguientes input como acciones disponibles:
    Login: se obtienen las credenciales del usuario y se accede a twitter a traves de twitter_login.
    Signup: se registra al usuario a traves de twitter_signup.
    Leave: eliminamos Twittera a traves de twitter_destroy.*/

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
        fflush(stdin);

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

/*twitter_login: buscamos al usuario deseado a traves de htable_get_user. Si la busqueda es exitosa, verificamos que la contrasena dada sea la correspondiente con
la otorgada a traves de la funcion de Hash. De ser asi, accedemos a Twitter*/

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

/*twitter_feed: se encarga de recibir los comandos de accion del usuario. Compara la entrada dada con las acciones disponibles (Agregar tweet +, buscar perfil @, logout y follow).
Follow solo estara disponible si el usuario se encuentra dentro del perfil de otro usuario. Si no lo sigue y el usuario toma la accion de follow, se agregara a la tabla
de seguidos. En caso contrario, aparecera un mensaje de advertencia de que el usuario ya se sigue. Luego de cualquiera de estas acciones, se vuelve al feed inicial y la accion
de follow deja de estar disponible.
Se compara siempre el input del usuario con alguna de las acciones, antes de proceder. De igual manera, se imprime el timeline correspondiente del usuario al acceder al feed,
del cual dependera de los seguidos en cuestion.
    Agregar tweet +: se guarda el contenido del tweet y se almacena su fecha de publicacion. Luego, se agrega a la lista de Tweets de Twitter.
    Buscar perfil @: a traves de htable_get_user, se busca al usuario en cuestion, se accede a su perfil, sus tweets son impresos y de abre la opcion de follow.
    Logout: el usuario conectado actual de Twitter pasa a ser NULL. Finalmente, volvemos a la pantalla inicial de Twitter.
    Follow: se agrega a la tabla de seguidos del usuario conectado, al usuario en cuestion*/

void twitter_feed(Twitter* twitter)
{
    char input[8];

    twitter_print_timeline(twitter, twitter->loggedUser);
    int follow = 0;
    User* toFollow = NULL;

    while(1){

        printf("WHAT'S HAPPENING?\n");
        scanf("%s", input);

        if (input[0] == '+' && strlen(input) == 1)
        {
            clean_stdin();
            Tweet * tweet = tweet_init();

            time_t inittime;
            struct tm *info;
            time( &inittime );
            info = localtime( &inittime );

            tweet->day = info->tm_mday;
            tweet->month = info->tm_mon;
            tweet->hour = info->tm_hour;
            tweet->minute = info->tm_min;
            tweet->u = twitter->loggedUser;

            printf("Input the tweet (max 280 chars): ");
            scanf("%[^\n]", tweet->content);
            
            tqueue_add(twitter->loggedUser->tweets, tweet);
            tqueue_add(twitter->tweets,tweet);


        } else if (input[0] == '@' && strlen(input) == 1)
        {
            clean_stdin();
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
            clean_stdin();
            twitter->loggedUser = NULL;
            break;
        }else if(strcmp(input, "follow") == 0 && follow == 1){
            clean_stdin();
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


    clean_stdin();

    }
    
}

/*twitter_signup: pide al usuario las credenciales correspondientes. Luego, ubica al usuario en su bucket correspondiente, a traves de la funcion de hash y htable_add*/

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

/*twitter_print_timeline: se recorre la cola de Tweets de Twitter, imprimiendo los tweets de los usuarios seguidos, en orden cronologico*/

void twitter_print_timeline(Twitter *t, User* user)
{
    Tnode *aux = t->tweets->head;

    while (aux != NULL)
    {
        if (htable_get_user(user->following, aux->tweet->u->userName))
        {
            tweet_print(aux->tweet);
        }
        aux = aux->next;
    }
    
}

/*twitter_destroy: elimina todos los usuarios contenidos en la tabla de Twitter a traves de htable_destroy y finalmente, elimina los tweets almacenados en la cola
de tweets, llamando a tqueue_destroy*/

void twitter_destroy(Twitter* twitter)
{
    htable_destroy(twitter->users);
    tqueue_destroy(twitter->tweets);
}

/*clean_stdin: limpieza de buffer*/

void clean_stdin(void)
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}