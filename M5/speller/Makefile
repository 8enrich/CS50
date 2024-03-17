all: speller.o dictionary.o
	gcc -o speller ./obj/speller.o ./obj/dictionary.o -lm
dictionary.o:
	gcc -o ./obj/dictionary.o -c ./src/dictionary.c
speller.o:
	gcc -o ./obj/speller.o -c ./src/speller.c
clear:
	rm ./obj/*.o ./speller
