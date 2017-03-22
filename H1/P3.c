// Created by Jason Gallagher
// cs 283 Systems programming

int main(int argc, char* argv[])
{
    // long int array 
    long int find_my_length[2] = {0,0};
    // pointer to array used for getting address
    long int* ptr = find_my_length;

    // starting address of array
    int base_addr = (int) ptr;
    ptr++;  // Increment to next element in array
    // second element address
    int end_addr = (int) ptr;
    // print results 
    printf("%d - %d\n = %d Bytes\n = %d bits\n", end_addr, base_addr,end_addr-base_addr,(end_addr-base_addr)*8);
    return 0;
}
