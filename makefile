main.out: types.o main.o
	gcc dev.o main.o -o main.out -lm
types.o:
	gcc -c include/dev.c -o dev.o -std=c99
main.o:
	gcc -c main.c -o main.o -std=c99
clean:
	rm *.o main.out
