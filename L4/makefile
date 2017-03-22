all: client server
    
client: client.o
	gcc -o client client.c ./lib/* -g -pthread
server: server.o
	gcc -o server server.c ./lib/* -g -pthread
clean:
	rm server client client.o server.o 
