all: filefun.c
	gcc -o filefun filefun.c ./lib/* -g -pthread
prep_test: a b
	./test_files/prep_test
run:
	./filefun ./a ./b
