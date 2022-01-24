all: client server output


client: basic_client.o pipe_networking.o
	gcc -o client basic_client.o pipe_networking.o

server: basic_server.o pipe_networking.o
	gcc -o server basic_server.o pipe_networking.o

basic_client.o: basic_client.c pipe_networking.h
	gcc -c basic_client.c

basic_server.o: basic_server.c pipe_networking.h
	gcc -c basic_server.c

pipe_networking.o: pipe_networking.c pipe_networking.h
	gcc -c pipe_networking.c
	
output: ncursesdemo.o
	 gcc -o output ncursesdemo.o -lncurses

ncursesdemo.o: ncursesdemo.c
	gcc -c ncursesdemo.c -lncurses


clean:
	-rm client server output
	-rm *.o
