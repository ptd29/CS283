#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{

    int i;

    for(i=0; i<2; i++)
        fork();
    printf("hello\n");

    exit(0);
}