#include <stdio.h>
#include <stdlib.h>
#include "lib/csapp.h"
#define BUFFLEN 50

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Invalid # of arguments");
        exit(-1);
    }
    int input_file;
    if(access(argv[1],F_OK) == -1)
    {
        input_file = open(argv[1],O_RDWR|O_CREAT);
        chmod(argv[1],strtol("0777",0,8));
    }
    else
    {
        input_file = open(argv[1],O_RDWR|O_APPEND);
    }
    int read_count = 1;
    char buff[BUFFLEN];
    while((read_count = read(STDIN_FILENO,buff,BUFFLEN)) != 0)
    {
        printf("%s",buff);
        write(input_file,buff, read_count);
    }
    close(input_file);
    return 0;
}
