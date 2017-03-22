#include "csapp.h"
#define BUFFLEN 1

int main(int argc, char* argv[])
{
    if(argc != 2)
        return -1;
    int fd = open(argv[1],O_RDONLY);
    char n_byte;
    size_t num_read;
    int index = 0;
    int stop,bytes_found;
    rio_t rio;
    rio_readinitb(&rio,fd);
    stop=bytes_found=0;
    while(!stop)
    {
        if((num_read = rio_read(&rio,&n_byte,BUFFLEN)) >0)
        {
            if(n_byte == (char) 0xAC)
                bytes_found++;
            else if(n_byte == (char) 0x2D)
                bytes_found++;
            else
                bytes_found = 0;
            index++;
        }
        else if(num_read == 0)
        {
            printf("EOF Reached\nSequence not found\n");
            stop == 1;
        }
        else if(num_read == -1)
        {
            printf("error");
        }
        
        if(num_read == 2)
        {
            printf("Sequence found at index %d\n",index);
            stop = 1;
        }
    }
}
