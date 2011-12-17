all: Level.o main.o
	gcc -Wall -o cwing.exe main.o Level.o -lmingw32 -lSDLmain -lSDL

main.o:
	gcc -Wall -c main.c

Level.o:
	gcc -Wall -c Level.c

clean:
	rm *.o cwing.exe

