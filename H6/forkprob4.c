#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void doit()
{
    fork();
    fork();
    printf("hello\n");
    return; 

}

int main(int argc, char* argv[])
{

    int i;
    doit();
    printf("hello\n");

    exit(0);
}
