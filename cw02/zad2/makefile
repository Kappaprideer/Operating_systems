CC = gcc
FLAGS = -Wall
SOURCE_PROGRAM_NAME = reverse.c
PROGRAM_NAME = reverse
SOURCE_FILENAME = plik1.txt


all:
	make compile
	./$(PROGRAM_NAME) $(SOURCE_FILENAME) > pomiar_zad_2.txt

compile:
	$(CC) $(FLAGS) $(SOURCE_PROGRAM_NAME) -o $(PROGRAM_NAME)

run:
	make compile
	./$(PROGRAM_NAME) $(SOURCE_FILENAME)

clean:
	rm -r $(PROGRAM_NAME)

clean_all:
	rm -r $(PROGRAM_NAME)
	rm reversed_block.txt
	rm reversed_char.txt
	rm pomiar_zad_2.txt
