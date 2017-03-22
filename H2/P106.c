#include <stdlib.h>
#include <stdio.h>

int main()
{
    int* var = malloc(1);
    printf("\n%d\n",var);
    int* var2 = malloc(5);
    printf("\n%d\n",var2);
    printf("difference: %d",var2-var);
    free(var);
    free(var2);
}
