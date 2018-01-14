all : menace.exe

menace.exe: menace.o mytab.o main.o mytab.h menace.h
	gcc -g -Wall -Wextra menace.o mytab.o main.o -o menace.exe

menace.o: menace.c menace.h
	gcc -g -Wall -Wextra -c menace.c

mytab.o: mytab.c mytab.h
	gcc -g -Wall -Wextra -c mytab.c

main.o: main.c
	gcc -g -Wall -Wextra -c main.c
