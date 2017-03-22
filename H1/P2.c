#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        return -1;
    }
    // Read command line argument as unsigned int
    uint32_t input = (uint32_t) atoi(argv[1]);
    
    int power;
    // Iterate through all powers of 2 from 31 downto 0
    for(power = 31; power >= 0; power--)
    {
        // Calculate power
        uint32_t bin_val = (uint32_t) pow(2.0,power);

        // print 1 if power is less then remainder else print 0 
        if(input >= bin_val)
        {
            printf("1");
            input-= bin_val;
        }
        else
        {
            printf("0");
        }
            

    }
    
    return 0;
}


