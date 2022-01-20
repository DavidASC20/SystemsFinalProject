all: ncursesdemo.o
	 gcc -o output ncursesdemo.o -lncurses

ncursesdemo.o: ncursesdemo.c
	gcc -c ncursesdemo.c -lncurses

run:
	./output

clean:
	-rm output
	-rm *.o
