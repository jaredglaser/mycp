all: mycp

mp3: main.o 
	gcc -g main.o -o mycp

main.o: main.c
	gcc -g -c main.c

clean:
	\rm *.o mycp
