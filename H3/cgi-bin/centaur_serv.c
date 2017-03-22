#include <stdio.h>
#include <stdlib.h>
#include "csapp.h"

int main(int argc, char* argv[])
{
    FILE *fp = fopen("centaur_1.mpg","rb");
     fseek(fp,0,SEEK_END);
     int content_len = ftell(fp)+ 5;
     fclose(fp);

    int fd = open("centaur_1.mpg",O_RDONLY);
    

    rio_t rio;
    rio_readinitb(&rio,fd);
    char buff[128];
    int size = 1;

    /*char* html_head = "<html><body><span> serving content </span> <video controls> <source src=\"";
    char * html_end = "centaur_1.mpg\"> </video></body> </html>\r\n\r\n";
    */
    //content_len+= strlen(html_head) + strlen(html_end);

    sprintf(buff,"Content-type: video/mpg\r\nfilename\'centaur_1.mpg'\r\nContent-length: %d\r\n",content_len); 
    Rio_writen(STDOUT_FILENO,&buff,strlen(buff));
//    Rio_writen(STDOUT_FILENO,html_head,strlen(html_head));
    char header_buff[128];
    int index = 0;
    while((size = rio_readnb(&rio,&buff,128)) > 0)
    {
        //sprintf(header_buff,"\r\nHTTP/1.1 206 Partical Content\r\nContent-Range: bytes %d-%d/%d\r\n",index,index+size,content_len); 
        Rio_writen(STDOUT_FILENO,&header_buff,strlen(header_buff));
        //index+= size; 
        Rio_writen(STDOUT_FILENO,&buff, size);
    }
     
    close(fd);
    Rio_writen(STDOUT_FILENO,"\r\n\r\n\0",5);
    return 0;
}
