#include <pthread.h>
//#include <stdlib.h>
#include <stdio.h>

#define NUM_THREADS 8

typedef struct {
    int t_id;
    int sum;
    char* message;
} pt_args;

char *messages[NUM_THREADS];
void *PrintHello(void *threadarg)
{
    int taskid, sum;
    char *hello_msg;
    /* ... */
    pt_args* args = (pt_args*) threadarg;
    taskid = args->t_id;
    sum = args->sum;
    hello_msg = args->message;
    /* ... */
    printf("Thread %d %s Sum=%d\n", taskid, hello_msg, sum);
    pthread_exit(NULL);
}
int main(int argc, char *argv[])
{
    pthread_t threads[NUM_THREADS];
    int rc, t, sum;
    pt_args args[NUM_THREADS];
    sum=0;
    messages[0] = "Hello-0";
    messages[1] = "Hello-1";
    messages[2] = "Hello-2";
    messages[3] = "Hello-3";
    messages[4] = "Hello-4";
    messages[5] = "Hello-5";
    messages[6] = "Hello-6";
    messages[7] = "Hello-7";
    for(t = 0; t < NUM_THREADS; t++)
    {
        sum = sum + t;
        /* ... */
        args[t].t_id = t;
        args[t].sum = sum;
        args[t].message = messages[t];

        printf("Creating thread %d\n", t);
        /* ... */
        pthread_create(&threads[t],NULL,PrintHello,&args[t]);
    }
    pthread_exit(NULL);
}
