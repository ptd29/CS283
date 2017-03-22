#include "../lib/csapp.h"

int main() {
    int fd[2];
    pipe(fd);
    pid_t pid = fork();
    rio_t rio;
    rio_readinitb(&rio,fd[0]);
    // Child
    if(pid == 0)
    {
        rio_readinitb(&rio,fd[0]);
        close(fd[1]);   // Close write fd
        char buff[50];
        int num_read;
        while((num_read = rio_readlineb(&rio,buff,50)) > 0)
            printf("Child received message: %s",buff);
        
        close(fd[0]);
    }
    else
    {
        // Parent
        rio_readinitb(&rio,STDIN_FILENO);
        close(fd[0]);
        int num_read;
        char buff[50];
        while((num_read = rio_readlineb(&rio,buff,50)) > 1)
        rio_writen(fd[1],buff,num_read);
        
        int status;
        close(fd[1]);
        waitpid(pid,&status,0);
        
    }

    exit(0);
}
