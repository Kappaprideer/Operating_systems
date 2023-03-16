CC = gcc
FLAGS = -Wall
SOURCE_NAME = main.c
PROGRAM_NAME = main
SOURCE_FILENAME = plik2.txt


all:
	make compile
	./$(PROGRAM_NAME) $(SOURCE_FILENAME) > pomiar_zad_2.txt

compile:
	$(CC) $(FLAGS) $(SOURCE_NAME) -o $(PROGRAM_NAME)

run:
	$(CC) $(FLAGS) $(SOURCE_NAME) -o $(PROGRAM_NAME)
	./$(PROGRAM_NAME) plik2.txt

clean:
	rm -r main

clean_all:
	rm -r main
	rm reversed_block.txt
	rm reversed_char.txt
	rm pomiar_zad_2.txt