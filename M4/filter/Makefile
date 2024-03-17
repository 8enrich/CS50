all: verification.o image.o filters.o main.o
	gcc -o ./bin/filter ./obj/*.o -lm
main.o:
	gcc -o ./obj/main.o  -c ./src/main.c
verification.o:
	gcc -o ./obj/verification.o -c ./src/verification.c
image.o:
	gcc -o ./obj/image.o -c ./src/image.c
filters.o:
	gcc -o ./obj/filters.o -c ./src/filters.c -lm
clear:
	rm ./bin/filter ./obj/*.o
