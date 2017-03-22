#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int counter = 1;

int main(int argc, char* argv[])
{

    if(fork == 0)
    {
        counter--;
        exit(0);
    }
    else
    {
        wait(NULL);
        printf("counter = %d\n",++counter);
    }
    exit(0);
}
