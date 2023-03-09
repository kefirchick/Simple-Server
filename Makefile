FLAGS = -Wall -Werror -Wextra

all: server

network.a:
	gcc -c $(FLAGS) network.c
	ar rcs network.a network.o

server: network.a
	gcc $(FLAGS) server.c arg_parse.c network.a -o server.out

.PHONY: all clean rebuild

clean:
	rm -rf *.o *.a *.out

rebuild: clean all
