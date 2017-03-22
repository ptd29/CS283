all: hello.o buggy.o hello-hw.o dotpr-hw.o

csapp.o: 
	gcc -c csapp.c csapp.h
hello.o: csapp.o
	gcc hello.c -o hello -pthread csapp.c csapp.h 
buggy.o: csapp.o
	gcc buggy.c -o buggy -pthread csapp.o
hello-hw.o:
	gcc -o hello-hw hello-hw.c -pthread
dotpr-hw.o: 
	gcc dotpr-hw.c -o dotpr-hw -pthread
clean:
	rm hello csapp.o buggy hello-hw dotpr-hw csapp.h.gch
