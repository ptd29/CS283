ALL: P1.o P2.o P3.o
	make P1 P2 P3
P1: P1.o
	gcc -o P1 P1.c
P2: P2.o
	gcc -o P2 P2.c -lm
P3: P3.o
	gcc -o P3 P3.c
clean: P1.o P2.o
	rm P1 P2 P3 P1.o P2.o P3.o
