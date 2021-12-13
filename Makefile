all: dir binary

dir:
	mkdir -p bin/

binary: server client

server:
	gcc -o bin/server server.c

client:
	gcc -o bin/client client.c

test:
	gcc -o bin/test test.c
