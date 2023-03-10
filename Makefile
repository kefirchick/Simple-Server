CFLAGS =-c -Wall -Werror -Wextra

all: server

network.a:
	gcc $(CFLAGS) network.c
	ar rcs network.a network.o

server: network.a
	gcc server.c network.a -o server.out

run: server
	./server.out 8001 127.0.0.1 index.html

.PHONY: all clean rebuild

clean:
	rm -rf *.o *.a *.out

rebuild: clean all