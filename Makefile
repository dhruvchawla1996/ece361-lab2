default: server client

server: server.c
	gcc -o server -g server.c

client: client.c
	gcc -o client -g client.c

clean:
	rm -f server.c client.c
