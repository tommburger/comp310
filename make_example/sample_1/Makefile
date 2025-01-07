all: sample

sample:  main.o common.o
	gcc -o sample main.o common.o

main.o: main.c
	gcc -o main.o main.c -Wall -c

common.o: common.c
	gcc -o common.o common.c -Wall -c

# clean removes all object files but leaves the executable
clean:
	rm common.o main.o
