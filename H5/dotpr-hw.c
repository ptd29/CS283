#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#define NUMTHRDS 4
#define VECLEN 100000

typedef struct {
    double sum;
    int start;
    int stop;
} pt_args;

pthread_t callThd[NUMTHRDS];
double *array_a;
double *array_b;
double big_sum;
int veclen;
void *dotprod(void *arg)
{
    pt_args* args = (pt_args*) arg;
    /* declare variables and initialize from args */
    int start,end,i;
    double mysum,*x,*y;
    start = args->start;
    end = args->stop;

    x = array_a;
    y = array_b;
    /* calculate sum */
    mysum = 0;
    for (i=start; i<end ; i++)
    {
        mysum += (x[i] * y[i]);
    }
    /* store partial sum */
    args->sum = mysum;
    /* clean exit */
    pthread_exit(NULL);
}
int main (int argc, char *argv[])
{
    long i;
    double *a, *b;
    void *status;
    a = (double*) malloc (NUMTHRDS*VECLEN*sizeof(double));
    b = (double*) malloc (NUMTHRDS*VECLEN*sizeof(double));
    for (i=0; i<VECLEN*NUMTHRDS; i++)
    {
        a[i]=1;
        b[i]=a[i];
    }
    veclen = VECLEN;
    array_a = a;
    array_b = b;
    big_sum = 0;
    /* Declare arguments */
    pt_args args[NUMTHRDS];
    /* create threads */
    for(i=0;i<NUMTHRDS;i++)
    {
        /* Each thread works on a different set of data.
           The offset is specified by 'i'. The size of
           the data for each thread is indicated by VECLEN.
         */
        /* Initialize args */
        args[i].start = i*VECLEN;
        args[i].stop = args[i].start + VECLEN;
        args[i].sum = 0;
         pthread_create(&callThd[i],NULL,dotprod,&args[i]);
    }
    /* Wait on the other threads */
    for(i=0;i<NUMTHRDS;i++)
    {
        pthread_join(callThd[i],NULL);
        big_sum+=args[i].sum;   // Combine partial sums
    }

    /* print sum and free vectors */
    printf ("Sum = %f \n", big_sum);
    free (a);
    free (b);
    /* Exit */
    pthread_exit(NULL);
}
