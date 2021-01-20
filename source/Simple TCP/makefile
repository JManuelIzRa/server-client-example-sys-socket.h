.PHONY: all

all: server.c client.c
	gcc -g -Wall -o server.out server.c
	gcc -g -Wall -o client.out client.c

.PHONY: server

server: server.c
	gcc -g -Wall -o server.out server.c

.PHONY: client

client: client.c
	gcc -g -Wall -o client.out client.c