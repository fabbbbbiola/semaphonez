all: control.o main.o 
	gcc -o semaphorez.out control.o main.o

control.o: control.c semaphore.h
	gcc -c control.c

main.o: main.c semaphore.h
	gcc -c main.c

run: all 
	./semaphorez.out

clean:
	-rm -rf *~
	-rm -rf *.o
