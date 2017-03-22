#include "csapp.h"
void *thread(void *vargp);

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Invalid number of parameters\n");
        return -1;
    }

    int num_threads = atoi(argv[1]);
    int i,rv;
    pthread_t tid[num_threads];
    
    printf("Creating threads\n");
    for(i=0; i<num_threads; i++)
    {   
        Pthread_create(&tid[i], NULL, thread, NULL);
        if(rv)
            printf("Error creating threads %d\n",i);
    }

    printf("Joining threads\n");
    for(i=0;i<num_threads; i++)
    {
        Pthread_join(tid[i], NULL);
        if(rv)
            printf("Error joinging threads %d\n",i);
    }
    exit(0);
}

void *thread(void *vargp) /* Thread routine */
{
    printf("Hello, world!\n");
    return NULL;
}
