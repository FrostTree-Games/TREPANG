all: Level.o main.o
	gcc -g -Wall -o cwing.exe main.o Level.o -lmingw32 -lSDLmain -lSDL

main.o:
	gcc -g -Wall -c main.c

Level.o:
	gcc -g -Wall -c Level.c

clean:
	rm *.o cwing.exe

