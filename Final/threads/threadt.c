#include "../lib/csapp.h"

#define WORDS_PER_THREAD 5

typedef struct {
    int threadId;
    char* words[WORDS_PER_THREAD];
    int fd;
} data;

pthread_mutex_t mutex;
int rdwr = 1;
void * write_sentence(void* args);
void * read_sentences(void * args);

int main(int argc, char* argv[]) {
    
    data write_thread_data[3];
    
    int fd[2];
    pipe(fd);
    int i;
    for(i=1; i<argc; i++)
    {
        
        write_thread_data[i%2].words[(int)(i/3)] = argv[i] + '\n';

    }

    for(int j=0; j<3; j++)
    {
        write_thread_data[(i+j)%2].words[(int)((i+j)/3)] = NULL;
    }

    pthread_t pthread[3];
    write_thread_data[3].fd = fd[0];
    pthread_create(&pthread[3],NULL,(void*) read_sentences,(void*) &write_thread_data[3]);
    for(int i=0; i<3; i++) {
        write_thread_data[i].fd = fd[1];
        write_thread_data[i].threadId = i;
        pthread_create(&pthread[i], NULL,write_sentence,(void*) &write_thread_data[i]);
    }

    for(int i=0; i<3; i++)
        pthread_join(pthread[i],NULL);
    close(fd[0]);
    close(fd[1]);
    pthread_join(pthread[3],NULL);
    return 0;
}

void * write_sentence(void* args)
{
    int myrdwr = 0;
    data* dat = (data*) args;
    for(int i=0; i<5; i++)
    {
    
        if(dat->words == NULL || dat->words[i] == NULL || sizeof(dat->words[i]) == 0)
            break;
        
        while(myrdwr == 0)
        {
        while(!pthread_mutex_trylock(&mutex))
        {

        }
        // If read mode wait
        if((myrdwr = rdwr) != 0)
        {
            rio_writen(dat->fd,dat->words[i],sizeof(dat->words[i]));
            rdwr = 0;
        }
        pthread_mutex_unlock(&mutex);

        }
        myrdwr = 0;
    }
//    pthread_exit(NULL);
}

void * read_sentences(void * args)
{
    data* dat = (data*) args;
    char buff[50];
    rio_t rio;
    rio_readinitb(&rio,dat->fd);
    
    while(rio_readlineb(&rio,buff,50) > 0) {
        //rio_writen(STDOUT_FILENO,buff,sizeof(buff));
        printf("%s\n",buff);
         while(!pthread_mutex_trylock(&mutex)){}
        if(rdwr == 0)
            rdwr = 1;
        pthread_mutex_unlock(&mutex);
    }
    
  //  pthread_exit(NULL);
}
