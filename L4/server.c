#include "lib/csapp.h"
#include <stdlib.h>
#include <stdio.h>


#define BUFFLEN 256
#define FTLEN 32
#define MAXHEADERLEN 256 
#define STATOK "200 OK"
#define HTTP11 "HTTP/1.1"

char* create_header(char* fname,int file_size)
{
    char file_type[FTLEN];
    
    if(strstr(fname,".html"))
        strcpy(&file_type,"text/html");
    else
        strcpy(&file_type,"text/plain\0");
    printf("File type set\n"); 
    char* header = malloc(MAXHEADERLEN);
    char* skeleton_header = "%s %s\r\nContent-Type: %s; charset=%s\r\nContent-Length: %d\r\n\r\n\r\n";
    
    sprintf(header,skeleton_header,HTTP11,STATOK,file_type,"utf-8",file_size);
    printf("Header created\n");
    return header;
}
void serve(int connfd)
{
    rio_t rio;
    Rio_readinitb(&rio,connfd);
    int num_read;
    char buff[BUFFLEN];
    int to = 0;

    while((num_read = Rio_readlineb(&rio,&buff,BUFFLEN)) == 0)
    {
        if(num_read < 0 || to > 1000000)
        {
            fprintf(stderr,"Error reading request header\n");
            return;
        }
        to++;
    }
    
    char* headerptr = buff;
    int not_done = 1;
    int start = 0;
    char req_page[BUFFLEN];
//    req_page[0] = ' ';
    char* reqptr = req_page;

    while(not_done)
    {
        if(*headerptr == '/')
        {
            printf("Start / found\n");
            start = 1;
            headerptr++;
        }
        if(start)
        {
            if(*headerptr == ' ' || *headerptr == '\0')
                not_done = 0;
            else
            {
                printf("copying char\n");
                memcpy(reqptr,headerptr,1);
                reqptr++;
            }
        }
        headerptr++;
        printf("loop");
    }
    
    *reqptr = '\0';
    printf("Requested page: %s\n",req_page);
    int pagefd;
    struct stat file_stat;
    pagefd = open(req_page,O_RDWR);
    

    if(pagefd < 0)
    {
        fprintf(stderr,"Requested page not found\n");
        return;
    }

    if(fstat(pagefd,&file_stat) < 0)
    {
        fprintf(stderr,"Error with fstat\n");
        return;
    }
    

    Rio_readinitb(&rio,pagefd);
    char* header = create_header(&req_page,file_stat.st_size);
    Rio_writen(connfd,header,strlen(header));
    printf("Header response written: %s\n", header);
    while((num_read = Rio_readnb(&rio,&buff,BUFFLEN)) > 0)
    {
        Rio_writen(connfd,&buff,num_read); 
    }
}

int main(int argc, char* argv[])
{
    /* Check arguments */
    if(argc != 2)
    {
        fprintf(stderr,"Invalid number of arguments\n");
        exit(-1);
    }

    int listenfd,connfd,port,clientlen;
    struct sockaddr_in clientaddr;

    port = atoi(argv[1]);
    listenfd = Open_listenfd(port);
    while(1)
    {
        clientlen = sizeof(clientaddr);
        connfd = Accept(listenfd,(SA*) &clientaddr,&clientlen);
        printf("Connection accepted\n");
        serve(connfd);
        printf("Content served\n");
        Close(connfd);
        printf("Connection closed\n");

    }

}
