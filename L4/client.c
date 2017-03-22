#include <stdlib.h>
#include "lib/csapp.h"
#include <sys/socket.h>

#define HEADERLEN 128 

int main(int argc, char* argv[])
{
    /* Check arguments */
    if(argc != 4)
    {
        fprintf(stderr,"Invalid number of arguments\n");
        exit(-1);
    }
   
    /* Get parameters */
    char* host = argv[1];
    int port = atoi(argv[2]);
    char* port_c = argv[2];
    char* file = argv[3];
    struct in_addr address;
    char header[HEADERLEN];
    struct hostent *host_ptr;
    rio_t rio;
    
    sprintf(header,"GET /%s HTTP/1.1\nHost: %s:%d\r\n\r\n\0",file,host,port);
    printf("%s\n",header); 
    
    int fd,connfd;
     
    connfd = Open_clientfd(host, port);
    Rio_readinitb(&rio,connfd);

    if(connfd < 0)
    {
        fprintf(stderr,"Error opening client\n");
        exit(fd);
    }
    Rio_writen(connfd,header,strlen((const char*) header));

    char buff[HEADERLEN];
    int outlen;
    while((outlen = Rio_readlineb(&rio,&buff,HEADERLEN))>0)
    {

        Rio_writen(STDOUT_FILENO,&buff,outlen);
    }

    close(connfd);
    return 0;
}
