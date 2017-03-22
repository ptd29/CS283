all: pipet.o

csapp.o: ../lib/csapp.c ../lib/csapp.c
	gcc -Wall -c ../lib/csapp.c ../lib/csapp.h

pipet.o: pipet.c csapp.o
	gcc -c pipet.c 
	gcc -pthread -o pipet pipet.o csapp.o  
