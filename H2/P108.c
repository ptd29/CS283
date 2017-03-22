#include <stdlib.h>
#include <stdio.h>

static_void *find_fit(size_t asize);


int main()
{ 
    
}

// Finds the best fit for a selected size 
static_void *find_fit(size_t asize)
{
    
    size_t fit_size;
    // maintain alignment if word is not a multiple of 2 bytes
    if(asize%2)
        fit_size = (asize+1) * WSIZE;
    else
        fit_size = asize*WSIZE;

    // Print and return best wordsize
    printf("%ld",fit_size);
    return (void*) fit_size;
}
