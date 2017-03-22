#include <stdio.h> 
#include <stdlib.h> 

int main () 
 {
  char * buf;
  u_int num;
  num = 1 << 31;
  buf = (char*) malloc(num) ;
  fgets (buf, 1024, stdin) ;
  printf ("%s\n", buf) ;
  return(1);
 }
